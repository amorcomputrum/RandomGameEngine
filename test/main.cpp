#include "RGE/Window/Window.h"
#include "RGE/World/GridWorld.h"
#include "RGE/System/File.h"

#include<iostream>

RGE::Sprite* sprite;
RGE::GridWorld* world = new RGE::GridWorld(1,1,2,8,8,2,"test");

void update(){
}
void render(){
	RGE::Window::Render::drawSprite(sprite,0,0);
	RGE::Window::Render::drawRect(0,0,20,20);
}

void onKey(RGE::KeyEvent event){
}

int main(){
	RGE::Window::createWindow(800,600,"Test Window");
	sprite = new RGE::Sprite("TestIcon.jpg");
	sprite->resize(800,600);
	RGE::Window::setUpdateFunction(&update);
	RGE::Window::setRenderFunction(&render);
	RGE::Window::setOnKeyFunction (&onKey );
	RGE::Window::setIcon("TestIcon.jpg");
	RGE::Window::run();
}