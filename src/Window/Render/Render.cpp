#include "RGE/glLibs/glad/glad.h"
#include "RGE/Window/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "RGE/Window/Render/Render.h"

RGE::Color RGE::Window::Render::fillColor = RGE::Color(150,150,150);
RGE::GLSL RGE::Window::Render::spriteShader = RGE::GLSL();
RGE::GLSL RGE::Window::Render::shapeShader = RGE::GLSL();
RGE::Window::Render::Shader RGE::Window::Render::Rect = RGE::Window::Render::Shader();
RGE::Window::Render::Shader RGE::Window::Render::Ellipse = RGE::Window::Render::Shader();

RGE::Window::Render::Render(){
	initShaders();
}

void RGE::Window::Render::setFillColor(int r, int g, int b){
	fillColor = RGE::Color(r,g,b);
}

void RGE::Window::Render::setFillColor(RGE::Color color){
	fillColor = color;
}

void RGE::Window::Render::drawSprite(RGE::Sprite* sprite, int x, int y){
    //Transformations
	glm::mat4 projection;
	projection  = glm::ortho(RGE::Window::Camera::X*1.0f, (RGE::Window::Camera::W*1.0f + RGE::Window::Camera::X*1.0f)-1.0f, (RGE::Window::Camera::H*1.0f + RGE::Window::Camera::Y*1.0f)-1.0f,RGE::Window::Camera::Y*1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x*1.0f, y*1.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix    , glm::vec3(sprite->getWidth()*1.0f, sprite->getHeight()*1.0f, 1.0f));
	
	sprite->Bind();
	glEnable(GL_TEXTURE_2D); 
	spriteShader.use();

	//Set uniforms
	spriteShader.uniformMat4("ModelMatrix", ModelMatrix);
	spriteShader.uniformMat4("projection" , projection);

	glBindVertexArray(sprite->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glDisable(GL_TEXTURE_2D);
}

void RGE::Window::Render::drawSprite(RGE::Sprite* sprite, int x, int y, double rotation){
	//Transformations
	glm::mat4 projection;
	projection  = glm::ortho(RGE::Window::Camera::X, (RGE::Window::Camera::W + RGE::Window::Camera::X)-1, (RGE::Window::Camera::H + RGE::Window::Camera::Y)-1, RGE::Window::Camera::Y);
	glm::mat4 ModelMatrix(1.0f);
	
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x, y, 0.0f));

	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(0.5f,0.5f,0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, (float)rotation, glm::vec3(0.0f,0.0f,1.0f));
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(-0.5f,-0.5f,0.0f));

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-sprite->getWidth()/2, -sprite->getHeight()/2, 0.0f));

	ModelMatrix = glm::scale(ModelMatrix    , glm::vec3(sprite->getWidth(), sprite->getHeight(), 1.0f));



	//Draw Sprite and cleanup
	glActiveTexture(GL_TEXTURE0);
	sprite->Bind();
	spriteShader.use();

	//Set uniforms
	spriteShader.uniformMat4("ModelMatrix", ModelMatrix);
	spriteShader.uniformMat4("projection" , projection);

	glBindVertexArray(sprite->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void RGE::Window::Render::drawRect(int x, int y, int w, int h){
	
	//Transformations
	glm::mat4 projection;
	projection  = glm::ortho(RGE::Window::Camera::X + 0.0f, (float)RGE::Window::Camera::W + RGE::Window::Camera::X, (float)RGE::Window::Camera::H + RGE::Window::Camera::Y,0.0f + RGE::Window::Camera::Y, -1.0f, 1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x, y, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix    , glm::vec3(w, h, 1.0f));

	float r,g,b,a;
	r = RGE::Color::getFloat(fillColor.r);
	g = RGE::Color::getFloat(fillColor.g);
	b = RGE::Color::getFloat(fillColor.b);
	a = RGE::Color::getFloat(fillColor.a);
	glm::vec4 Color(r, g, b, a);

	shapeShader.use();
	//Set Uniforms
	shapeShader.uniformMat4("ModelMatrix", ModelMatrix);
	shapeShader.uniformMat4("projection" , projection );
	shapeShader.uniformVec4("Color"      , Color      );

	glBindVertexArray(*Rect.getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

void RGE::Window::Render::drawRect(int x, int y, int w, int h, double rotation){
	//Transformations
	glm::mat4 projection;
	projection  = glm::ortho(RGE::Window::Camera::X + 0.0f, (float)RGE::Window::Camera::W + RGE::Window::Camera::X, (float)RGE::Window::Camera::H + RGE::Window::Camera::Y,0.0f + RGE::Window::Camera::Y, -1.0f, 1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x, y, 0.0f));

	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(0.5f,0.5f,0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, (float)rotation, glm::vec3(0.0f,0.0f,1.0f));
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(-0.5f,-0.5f,0.0f));

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-w/2, -h/2, 0.0f));

	ModelMatrix = glm::scale(ModelMatrix    , glm::vec3(w, h, 1.0f));

	float r,g,b,a;
	r = RGE::Color::getFloat(fillColor.r);
	g = RGE::Color::getFloat(fillColor.g);
	b = RGE::Color::getFloat(fillColor.b);
	a = RGE::Color::getFloat(fillColor.a);
	glm::vec4 Color(r, g, b, a);

	shapeShader.use();
	//Set Uniforms
	shapeShader.uniformMat4("ModelMatrix", ModelMatrix);
	shapeShader.uniformMat4("projection" , projection );
	shapeShader.uniformVec4("Color"      , Color      );

	glBindVertexArray(*Rect.getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

void RGE::Window::Render::drawEllipse(int x, int y, int w, int h){
	//Transformations
	glm::mat4 projection;
	projection  = glm::ortho(RGE::Window::Camera::X + 0.0f, (float)RGE::Window::Camera::W + RGE::Window::Camera::X, (float)RGE::Window::Camera::H + RGE::Window::Camera::Y,0.0f + RGE::Window::Camera::Y, -1.0f, 1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x  , y  , 0.0f));
	ModelMatrix = glm::scale(ModelMatrix    , glm::vec3(w/2, h/2, 1.0f));

	float r,g,b,a;
	r = RGE::Color::getFloat(fillColor.r);
	g = RGE::Color::getFloat(fillColor.g);
	b = RGE::Color::getFloat(fillColor.b);
	a = RGE::Color::getFloat(fillColor.a);
	glm::vec4 Color(r, g, b, a);

	shapeShader.use();
	//Set Uniforms
	shapeShader.uniformMat4("ModelMatrix", ModelMatrix);
	shapeShader.uniformMat4("projection" , projection );
	shapeShader.uniformVec4("Color"      , Color      );

	glBindVertexArray(*Ellipse.getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 720);
	glBindVertexArray(0);
}

void RGE::Window::Render::drawEllipse(int x, int y, int w, int h, double rotation){
	//Transformations
	glm::mat4 projection;
	projection  = glm::ortho(RGE::Window::Camera::X + 0.0f, (float)RGE::Window::Camera::W + RGE::Window::Camera::X, (float)RGE::Window::Camera::H + RGE::Window::Camera::Y,0.0f + RGE::Window::Camera::Y, -1.0f, 1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x, y, 0.0f));

	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(0.5f,0.5f,0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, (float)rotation, glm::vec3(0.0f,0.0f,1.0f));
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(-0.5f,-0.5f,0.0f));

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-w/2, -h/2, 0.0f));

	ModelMatrix = glm::scale(ModelMatrix    , glm::vec3(w, h, 1.0f));

	float r,g,b,a;
	r = RGE::Color::getFloat(fillColor.r);
	g = RGE::Color::getFloat(fillColor.g);
	b = RGE::Color::getFloat(fillColor.b);
	a = RGE::Color::getFloat(fillColor.a);
	glm::vec4 Color(r, g, b, a);

	shapeShader.use();
	//Set Uniforms
	shapeShader.uniformMat4("ModelMatrix", ModelMatrix);
	shapeShader.uniformMat4("projection" , projection );
	shapeShader.uniformVec4("Color"      , Color      );

	glBindVertexArray(*Ellipse.getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, 720);
	glBindVertexArray(0);
}

void RGE::Window::Render::drawCircle(int x, int y, int r){
	RGE::Window::Render::drawEllipse(x, y, r*2, r*2);
}

RGE::Window::Render::Shader::Shader(){}

unsigned int* RGE::Window::Render::Shader::getVAO(){
	return &VAO;
}

unsigned int* RGE::Window::Render::Shader::getVBO(){
	return &VBO;
}


void RGE::Window::Render::initShaders(){
	RGE::Window::Render::initSpriteShader();
	RGE::Window::Render::initShapeShader();
	RGE::Window::Render::initRectShader();
	RGE::Window::Render::initEllipseShader();
}

void RGE::Window::Render::initRectShader(){
	Rect = RGE::Window::Render::Shader();
	
	float vertices[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	glGenVertexArrays(1, Rect.getVAO());
	glGenBuffers(1, Rect.getVBO());

	glBindVertexArray(*Rect.getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, *Rect.getVBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void RGE::Window::Render::initEllipseShader(){
	Ellipse = RGE::Window::Render::Shader();
	float vertices[720];
	for(int i = 0; i < 720; i+=2){
		vertices[i]     = 0.0f + (cos(i/2*(3.14*2)/360)*1.0);
		vertices[i + 1] = 0.0f + (sin(i/2*(3.14*2)/360)*1.0);
	}

	glGenVertexArrays(1, Ellipse.getVAO());
	glGenBuffers(1, Ellipse.getVBO());

	glBindVertexArray(*Ellipse.getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, *Ellipse.getVBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void RGE::Window::Render::initSpriteShader(){
	const std::string file =
	#include "RGE/Window/Render/Shaders/Sprite.glsl"
	;
	spriteShader     = RGE::GLSL(file);
}

void RGE::Window::Render::initShapeShader(){
	const std::string file =
	#include "RGE/Window/Render/Shaders/Shape.glsl"
	;
	shapeShader     = RGE::GLSL(file);
}
