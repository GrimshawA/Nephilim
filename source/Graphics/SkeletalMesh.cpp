#include <Nephilim/Graphics/SkeletalMesh.h>
#include <Nephilim/Graphics/CGL.h>
#include <Nephilim/Foundation/Logging.h>

#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/DataStream.h>

#include <stdint.h>

NEPHILIM_NS_BEGIN

struct AssetFileHeader
{
	uint32_t id;
	uint8_t version;
};

struct GeometryFileHeader
{
	uint32_t num_meshes;
	uint32_t flags;
};

// nothing in the format is mandatory, instead of forcing an order, we use header + data chunks, supporting additional user data easily.
struct DataChunkHeader
{
	char id[20];
	uint32_t DataCount;
	uint32_t DataSize;
};

/// Load the skeletal mesh from disk
bool SkeletalMesh::load(const String& filename)
{
	File file(filename, IODevice::BinaryRead);
	if (file)
	{
		DataStream str(file);

		// Read header
		AssetFileHeader fileHeader;
		str.read(&fileHeader, sizeof(fileHeader));

		// Read secondary header
		GeometryFileHeader geometryFileHeader;
		str.read(&geometryFileHeader, sizeof(geometryFileHeader));

		std::vector<Vector3D> _positions;
		std::vector<Vector3D> _normals;
		std::vector<Vector2D> _texcoord0;
		std::vector<Vector4D> _boneID;
		std::vector<Vector4D> _boneWeight;

		while (!file.atEnd())
		{
			// Read a chunk and extract it until EOF is reached
			DataChunkHeader dataChunkHeader;
			str.read(&dataChunkHeader, sizeof(dataChunkHeader));

			char* buffer = new char[dataChunkHeader.DataCount * dataChunkHeader.DataSize];
			
			Log("CHUNK %s", dataChunkHeader.id);

			if (strcmp(dataChunkHeader.id, "POSITIONS") == 0)
			{
				_positions.resize(dataChunkHeader.DataCount);
				_normals.resize(dataChunkHeader.DataCount);
				_texcoord0.resize(dataChunkHeader.DataCount);
				_boneWeight.resize(dataChunkHeader.DataCount);
				_boneID.resize(dataChunkHeader.DataCount);

				str.read(_positions.data(), dataChunkHeader.DataCount * dataChunkHeader.DataSize);
			}
			else if (strcmp(dataChunkHeader.id, "FACES") == 0)
			{
				_indexArray.indices.resize(dataChunkHeader.DataCount);
				str.read(_indexArray.indices.data(), dataChunkHeader.DataCount * dataChunkHeader.DataSize);
			}
			else if (strcmp(dataChunkHeader.id, "NORMALS") == 0)
			{
				str.read(_normals.data(), dataChunkHeader.DataCount * dataChunkHeader.DataSize);
			}
			else if (strcmp(dataChunkHeader.id, "TEXCOORD0") == 0)
			{
				str.read(_texcoord0.data(), dataChunkHeader.DataCount * dataChunkHeader.DataSize);
			}
			else if (strcmp(dataChunkHeader.id, "BONEINFLUENCES") == 0)
			{
				str.read(_boneID.data(), dataChunkHeader.DataCount * (dataChunkHeader.DataSize / 2));
				str.read(_boneWeight.data(), dataChunkHeader.DataCount * (dataChunkHeader.DataSize / 2));
			}
		}

		// Assemble the vertex array
		_vertexArray.addAttribute(sizeof(float), 3, VertexFormat::Position);
		_vertexArray.addAttribute(sizeof(float), 4, VertexFormat::Color);
		_vertexArray.addAttribute(sizeof(float), 2, VertexFormat::TexCoord);
		_vertexArray.addAttribute(sizeof(float), 3, VertexFormat::Position);
		_vertexArray.addAttribute(sizeof(float), 4, VertexFormat::Position);
		_vertexArray.addAttribute(sizeof(float), 4, VertexFormat::Position);
		_vertexArray.allocateData(_positions.size());

		struct vformat
		{
			Vector3D p;
			Vector4D c;
			Vector2D tex0;
			Vector3D n;
			Vector4D bid;
			Vector4D bweight;
		};

		vformat* varray = reinterpret_cast<vformat*>(&_vertexArray._data[0]);

		for (std::size_t i = 0; i < _positions.size(); ++i)
		{
			varray[i].p = _positions[i];
			varray[i].c = Vector4D(1.f, 1.f, 1.f, 1.f);
			varray[i].tex0 = _texcoord0[i];
			varray[i].n = _normals[i];
			varray[i].bid = _boneID[i];
			varray[i].bweight = _boneWeight[i];
		}

		Log("Read the NGF");

		return true;
	}
	else
	{
		return false;
	}
}

NEPHILIM_NS_END