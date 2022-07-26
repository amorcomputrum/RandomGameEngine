set(SOURCE_FILES
	Window/Window.cpp
	Window/Camera.cpp
	Window/Render/Render.cpp
	Window/Render/Color.cpp
	Window/Render/TextureHandler.cpp
	Window/Render/Sprite.cpp
	Window/Render/Shaders/GLSL.cpp
	glLibs/glad.c
	System/Clock.cpp
	System/Exception.cpp
	System/File.cpp
	System/Math.cpp
	System/Vector2d.cpp
	Utils/Animation.cpp
	Utils/PerlinNoise.cpp
	Physics/Body.cpp
	Physics/Box.cpp
	Physics/Circle.cpp
	Physics/DetectCollision.cpp
	Physics/Engine.cpp
	Physics/EngineCollision.cpp
	Physics/TestCollider.cpp
	World/Chunk.cpp
	World/GridWorld.cpp
	World/AutoTiler.cpp
	tinyxml2/tinyxml2.cpp
	tmxparser/base64.cpp
	tmxparser/tmxparser.cpp
	)

add_library(RGE SHARED ${SOURCE_FILES})

target_include_directories(RGE
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(RGE glfw)
target_compile_options(RGE PUBLIC "-lglfw")
target_link_libraries(RGE "-lglfw")

set_target_properties(RGE PROPERTIES
	CXX_STANDARD_REQUIRED YES
	VERSION ${CMAKE_PROJECT_VERSION}
	SOVERSION ${CMAKE_PROJECT_VERSION})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${SOURCE_FILES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)