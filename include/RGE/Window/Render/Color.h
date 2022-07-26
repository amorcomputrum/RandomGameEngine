#pragma once

namespace RGE{
	class Color{
	public:
		/**
		 * r=red
		 * g=green
		 * b=blue
		 * a=alpha
		*/
		int r,g,b,a;
		/**
		 * Predefined colors
		 * Black(0,0,0)
		 * Red(255,0,0)
		 * Green(0,255,0)
		 * Blue(0,0,255)
		 * White(255,255,255)
		*/
		static const RGE::Color Black;
		static const RGE::Color Red;
		static const RGE::Color Green;
		static const RGE::Color Blue;
		static const RGE::Color White;
		Color(){};
		/**
		 * Initialize Color
		 * 
		 * @param r The Red Value on the RGB/RGBA scale
		 * @param g The Green Value on the RGB/RGBA scale
		 * @param b The Blue Value on the RGB/RGBA scale
		*/
		Color(int r, int g, int b);
		/**
		 * Initialize Color
		 * 
		 * @param r The Red Value on the RGB/RGBA scale
		 * @param g The Green Value on the RGB/RGBA scale
		 * @param b The Blue Value on the RGB/RGBA scale
		 * @param a The Alpha Value on the RGB/RGBA scale
		*/
		Color(int r, int g, int b, int a);
		/**
		 * Return the Float value of a color
		 * 
		 * @param color A value that is red,green,blue,OR alpha to convert to 0-1
		 * 
		 * @return The 0-1 value of the color
		*/
		static float getFloat(int color);
	};
}
