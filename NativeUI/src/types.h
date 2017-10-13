#ifndef NATIVEUI_TYPES
#define NATIVEUI_TYPES

namespace NativeUI
{
	struct Point
	{
	public:
		float x;
		float y;

		Point()
			: x(0.0f), y(0.0f)
		{
		}

		Point(const float& arg_x, const float& arg_y)
			: x(arg_x), y(arg_y)
		{
		}
	};

	enum SizeMode
	{
		Absolute,
		Relative
	};
}

#endif // NATIVEUI_TYPES
