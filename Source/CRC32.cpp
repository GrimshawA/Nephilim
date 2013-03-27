#include "Nephilim/CRC32.h"

PARABOLA_NAMESPACE_BEGIN
	CRC32 CRC32::Instance;

	CRC32::CRC32()
	{
		unsigned long Poly = 0x04C11DB7;

		for(unsigned long i = 0; i <= 0xFF; i++)
		{
			unsigned long &Value = LookupTable[i];
			Value = Reflect(i, 8) << 24;

			for(unsigned char j = 0; j < 8; j++)
			{
				Value = (Value << 1) ^ (Value & (1 << 31) ? Poly : 0);
			};

			Value = Reflect(Value, 32);
		};
	};

	unsigned long CRC32::Reflect(unsigned long Reflect, char Char)
	{
		unsigned long Value = 0;

		for(unsigned long i = 1; (char)i < Char + 1; i++)
		{
			if(Reflect & 1)
			{
				Value |= (1 << (Char - i));
			}

			Reflect >>= 1;
		};

		return Value;
	};

	unsigned long CRC32::CRC(const unsigned char *Data, unsigned long DataLength)
	{
		unsigned long OutCRC = 0xFFFFFFFF;

		while(DataLength--)
			OutCRC = (OutCRC >> 8) ^ LookupTable[(OutCRC & 0xFF) ^ *Data++];

		return OutCRC ^ 0xFFFFFFFF;
	};
PARABOLA_NAMESPACE_END
