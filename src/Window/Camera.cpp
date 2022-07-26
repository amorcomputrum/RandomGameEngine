#include "RGE/Window/Camera.h"

int RGE::Window::Camera::X{0};
int RGE::Window::Camera::Y{0};
int RGE::Window::Camera::W{0};
int RGE::Window::Camera::H{0};


void RGE::Window::Camera::move(int x, int y){
	X += x;
	Y += y;
}

void RGE::Window::Camera::set(int x, int y){
	X = x;
	Y = y;
}

void RGE::Window::Camera::setCenter(int x, int y){
	X = x - (W/2.0);
	Y = y - (H/2.0);
}