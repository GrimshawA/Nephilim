#include "Nephilim/Color.h"

NEPHILIM_NS_BEGIN

/// Static Color
Color Color::Red = Color(255,0,0,255);
Color Color::White = Color(255,255,255,255);

Color::Color(){
	r = g = b = 0;
	a = 255;
};

Color::Color(int byteRed, int byteGreen, int byteBlue, int byteAlpha){
	r = byteRed;
	g = byteGreen;
	b = byteBlue;
	a = byteAlpha;
};

NEPHILIM_NS_END