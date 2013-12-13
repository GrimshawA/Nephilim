#ifndef RenderModes_h__
#define RenderModes_h__

namespace Render
{
	namespace Primitive
	{
		enum Type
		{
			Triangles,
			TriangleFan,
			TriangleStrip,
			Lines,
			LineLoop,
			LineStrip,
			Points
		};
	}

	namespace Blend
	{
		enum Mode
		{
			Alpha,
			Add,       ///< Simply sums the incoming color to the destination color.
			AddAlpha,
			Multiply,
			None
		};
	}
};

#endif // RenderModes_h__
