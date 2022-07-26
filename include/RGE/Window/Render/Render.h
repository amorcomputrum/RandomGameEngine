#pragma once

#include "RGE/Window/Render/Color.h"
#include "RGE/Window/Render/Shaders/GLSL.h"
#include "RGE/Window/Render/Sprite.h"

namespace RGE{
	namespace Window{
		class Render
		{
		public:
			Render();

			static void setFillColor(int r, int g, int b);
			static void setFillColor(RGE::Color color);

			static void drawSprite(RGE::Sprite* sprite, int x, int y);
			static void drawSprite(RGE::Sprite* sprite, int x, int y, double rotation);

			static void drawRect(int x, int y, int w, int h);
			static void drawRect(int x, int y, int w, int h, double rotation);

			static void drawEllipse(int x, int y, int w, int h);
			static void drawEllipse(int x, int y, int w, int h, double rotation);

			static void drawCircle(int x, int y, int r);
		private:
			static RGE::Color fillColor;
			
			class Shader{
			public:
				Shader();
				unsigned int* getVAO();
				unsigned int* getVBO();
			private:
				unsigned int VAO,VBO;
			};

			static Shader Ellipse;
			static Shader Rect;
			//Shader Shape;
			static RGE::GLSL spriteShader;
			static RGE::GLSL shapeShader;

			static void initShaders();
			static void initRectShader();
			static void initEllipseShader();
			static void initSpriteShader();
			static void initShapeShader();
		};
	}
}