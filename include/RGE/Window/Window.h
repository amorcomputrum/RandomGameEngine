#pragma once

#include "GLFW/glfw3.h"
#include "RGE/Window/Render/stb_image.h"
#include <string>

#include "RGE/System/Clock.h"
#include "RGE/Window/Events/KeyEvent.h"
#include "RGE/Window/Events/MouseEvent.h"
#include "RGE/Window/Camera.h"
#include "RGE/Window/Render/Render.h"

namespace RGE{
	namespace Window{
		static int WIDTH, HEIGHT, FPS{60};
		extern double DELTA_TIME;
		static std::string TITLE;
		static int MOUSEX{0}, MOUSEY{0};

		//functions not for public use
		namespace hidden{
			extern GLFWwindow* window;
			extern RGE::Clock* clock;
			extern double backgroundColor[3];

			extern void(*updateFunction)(void);
			extern void(*renderFunction)(void);
			extern void(*onKeyFunction)(RGE::KeyEvent);
			extern void(*onMouseFunction)(RGE::MouseEvent);
			extern void(*onScrollFunction)(double, double);

			void initWindow(int width, int height, std::string title);
			void initOpenGL();
			void mainLoop();

			static void error_callback(int error, const char* description);
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			static void cursor_enter_callback(GLFWwindow* window, int entered);
			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		}

		//Functions to control Window
		void setIcon(std::string path);
		void setTitle(std::string title);
		void setBackgroundColor(int r, int g, int b);
		void setSizeLimits(int minW, int minH, int maxW, int maxH);

		void createWindow(int width, int height, std::string title);
		void run();

		bool isMousePressed(RGE::MouseEvent::Button button);
		bool isKeyPressed(RGE::Key key);

		//Functions to set event functions
		void setUpdateFunction     (void(*update)  (void));
		void setRenderFunction     (void(*render)  (void));
		void setOnKeyFunction      (void(*onKey)   (RGE::KeyEvent));
		void setOnMouseFunction    (void(*onMouse) (RGE::MouseEvent));
		void setOnScrollFunction   (void(*onScroll)(double, double));

	};
};