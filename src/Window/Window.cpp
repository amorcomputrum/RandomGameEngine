#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION


#if defined(__WIN32) || defined(_WIN64)
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

#include "RGE/glLibs/glad/glad.h"


#include "RGE/System/Exception.h"

#include "RGE/Window/Window.h"

void RGE::Window::hidden::initWindow(int width, int height, std::string title){
	glfwSetErrorCallback(error_callback);

	//Create Window
	if(!glfwInit()) throw RGE::exception("GLFW Failed to Initialize ... You're Fucked");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	RGE::Window::hidden::window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if(!RGE::Window::hidden::window) throw RGE::exception("Window Failed to be Created ... You're Fucked");

	//init variables
	RGE::Window::hidden::clock = new RGE::Clock();

	initOpenGL();
}

void RGE::Window::hidden::initOpenGL(){

	//glfwSetKeyCallback(window, key_callback);
	//glfwSetMouseButtonCallback(window, mouse_callback);
	//glfwSetWindowRefreshCallback(window, window_refresh_callback);

	glfwMakeContextCurrent(RGE::Window::hidden::window);

	gladLoadGL(glfwGetProcAddress);

	glfwSwapInterval(1);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE               );
	glfwWindowHint(GLFW_OPENGL_PROFILE       , GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES              , 2                       );
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	glEnable(GL_MULTISAMPLE); 
	glEnable(GL_BLEND      ); 
	glDisable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwHideWindow(RGE::Window::hidden::window);
}

void RGE::Window::hidden::mainLoop(){
	glfwShowWindow(RGE::Window::hidden::window);

	double lastTime = glfwGetTime();

	glViewport(0,0,RGE::Window::WIDTH, RGE::Window::HEIGHT);

	while(!glfwWindowShouldClose(RGE::Window::hidden::window)){
		//Just keep on Swimming
		RGE::Window::hidden::clock->start();

		glClearColor(RGE::Window::hidden::backgroundColor[0],RGE::Window::hidden::backgroundColor[1],RGE::Window::hidden::backgroundColor[2],1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//call frame events
		try{
			RGE::Window::hidden::updateFunction();
			RGE::Window::hidden::renderFunction();
		}catch(int e) {
			throw RGE::exception("Update() or Render() function not set");
		}

		glfwSwapBuffers(RGE::Window::hidden::window);

		//control fps
		while(glfwGetTime() < lastTime + 1.0/RGE::Window::FPS){
			#if defined(__WIN32) || defined(_WIN64)
				sleep( (lastTime + 1.0/RGE::Window::FPS) - glfwGetTime());
			#else
				usleep((lastTime + 1.0/RGE::Window::FPS) - glfwGetTime());
			#endif 
		}

		lastTime += 1.0/RGE::Window::FPS;
		RGE::Window::DELTA_TIME = RGE::Window::hidden::clock->getTime()/1000.0;

		glfwPollEvents();
	}
}

void RGE::Window::hidden::error_callback(int error, const char* description){
	fprintf(stderr, "OPENGL ERROR: %s\n", description);
}

void RGE::Window::hidden::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	RGE::Event::Type type;
	if(action == GLFW_PRESS) type = RGE::Event::Type::PRESSED;
	else type = RGE::Event::Type::RELEASED;

	if(onKeyFunction == NULL) return;
	onKeyFunction(RGE::KeyEvent{static_cast<RGE::Key>(key), type});
}

void RGE::Window::hidden::cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
	RGE::Window::MOUSEX = xpos;
	RGE::Window::MOUSEY = ypos;
}

void RGE::Window::hidden::cursor_enter_callback(GLFWwindow* window, int entered){
	RGE::Event::Type type;

	if(entered) type = RGE::Event::Type::ENTERED;
	else type = RGE::Event::Type::LEFT;

	if(onMouseFunction == NULL) return;
	onMouseFunction(RGE::MouseEvent{RGE::MouseEvent::Button::NONE, RGE::Window::MOUSEX, RGE::Window::MOUSEY, type});
}

void RGE::Window::hidden::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){

	RGE::Event::Type type;
	if(action == GLFW_PRESS) type = RGE::Event::Type::PRESSED;
	else type = RGE::Event::Type::RELEASED;

	if(onMouseFunction == NULL) return;
	onMouseFunction(RGE::MouseEvent{static_cast<RGE::MouseEvent::Button>(button), RGE::Window::MOUSEX, RGE::Window::MOUSEY, type});
}

void RGE::Window::hidden::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	if(onScrollFunction == NULL) return;
	onScrollFunction(xoffset, yoffset);
}

void RGE::Window::setIcon(std::string path){
	GLFWimage images[1];
	images[0].pixels = stbi_load(path.c_str(), &images[0].width, &images[0].height, 0, 4);
	glfwSetWindowIcon(RGE::Window::hidden::window, 1, images); 
	stbi_image_free(images[0].pixels);
}

void RGE::Window::setBackgroundColor(int r, int g, int b){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255)){
		RGE::Window::hidden::backgroundColor[0] = r/255.0;
		RGE::Window::hidden::backgroundColor[1] = g/255.0;
		RGE::Window::hidden::backgroundColor[2] = b/255.0;
	}else{
		throw RGE::exception("BackgroundColor - Out Of Range 0-255");
	}
}

void RGE::Window::setSizeLimits(int minW, int minH, int maxW, int maxH){
	glfwSetWindowSizeLimits(RGE::Window::hidden::window, minW, minH, maxW, maxH);
}

void RGE::Window::createWindow(int width, int height, std::string title){
	RGE::Window::WIDTH  = width ;
	RGE::Window::HEIGHT = height;
	RGE::Window::TITLE  = title ;

	//init window and opengl context
	RGE::Window::hidden::initWindow(width, height, title);

	RGE::Window::Camera::X = 0;
	RGE::Window::Camera::Y = 0;
	RGE::Window::Camera::W = width;
	RGE::Window::Camera::H = height;

	RGE::Window::Render r = RGE::Window::Render();

	glfwSetKeyCallback        (RGE::Window::hidden::window, RGE::Window::hidden::key_callback            );
	glfwSetCursorPosCallback  (RGE::Window::hidden::window, RGE::Window::hidden::cursor_position_callback);
	glfwSetCursorEnterCallback(RGE::Window::hidden::window, RGE::Window::hidden::cursor_enter_callback   );
	glfwSetMouseButtonCallback(RGE::Window::hidden::window, RGE::Window::hidden::mouse_button_callback   );
	glfwSetScrollCallback     (RGE::Window::hidden::window, RGE::Window::hidden::scroll_callback         );
}

void RGE::Window::run(){
	RGE::Window::hidden::mainLoop();
}

bool RGE::Window::isMousePressed(RGE::MouseEvent::Button button){
	int state = glfwGetMouseButton(RGE::Window::hidden::window, static_cast<int>(button));
	if (state == GLFW_PRESS) return true;
}

bool RGE::Window::isKeyPressed(RGE::Key key){
	int state = glfwGetKey(RGE::Window::hidden::window, static_cast<int>(key));

	if (state == GLFW_PRESS) return true;
}

void RGE::Window::setUpdateFunction(void(*update)(void)){
	RGE::Window::hidden::updateFunction = update;
}

void RGE::Window::setRenderFunction(void(*render)(void)){
	RGE::Window::hidden::renderFunction = render;
}

void RGE::Window::setOnKeyFunction(void(*onKey)(RGE::KeyEvent)){
	RGE::Window::hidden::onKeyFunction = onKey;
}

void RGE::Window::setOnMouseFunction(void(*onMouse)(RGE::MouseEvent)){
	RGE::Window::hidden::onMouseFunction = onMouse;
}

void RGE::Window::setOnScrollFunction(void(*onScroll)(double, double)){
	RGE::Window::hidden::onScrollFunction = onScroll;
}

GLFWwindow* RGE::Window::hidden::window;
double RGE::Window::DELTA_TIME = 0;
RGE::Clock* RGE::Window::hidden::clock;
double RGE::Window::hidden::backgroundColor[3] = {0, 0, 0};

void(*RGE::Window::hidden::updateFunction)(void);
void(*RGE::Window::hidden::renderFunction)(void);
void(*RGE::Window::hidden::onKeyFunction)(RGE::KeyEvent);
void(*RGE::Window::hidden::onMouseFunction)(RGE::MouseEvent);
void(*RGE::Window::hidden::onScrollFunction)(double, double);
