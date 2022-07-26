#pragma once

namespace RGE{
	namespace Window{
			struct Camera{
				static int X, Y, W, H;

				static void move(int x, int y);
				static void set (int x, int y);
				static void setCenter(int x, int y);
			};
	};
};