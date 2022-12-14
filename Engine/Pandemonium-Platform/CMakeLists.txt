set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/glfw ${CMAKE_CURRENT_SOURCE_DIR}/../Game/build/Engine)

file(
	GLOB_RECURSE
	HEADERS
	CONFIGURE_DEPENDS
	"*.h"
)

file(
	GLOB_RECURSE
	SRC
	CONFIGURE_DEPENDS
	"*.cpp"
)

target_sources(PandemoniumPlatform PUBLIC ${HEADERS} ${SRC})

# target_sources( PandemoniumPlatform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Windows/src/WindowsWindow.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/Windows/headers/WindowsWindow.h ${CMAKE_CURRENT_SOURCE_DIR}/Windows/src/WindowsInput.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/Windows/headers/WindowsInput.h ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/headers/OpenGLContext.h
# ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/OpenGLContext.cpp ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/headers/OpenGLBuffer.h
# ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/src/OpenGLBuffer.cpp )

target_include_directories(
	PandemoniumPlatform
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Windows/headers
			${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/headers
			${CMAKE_CURRENT_SOURCE_DIR}/../Pandemonium-Core/headers
			${CMAKE_CURRENT_SOURCE_DIR}/../Pandemonium-Renderer/headers
			${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/glfw/include
			${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/imgui
			${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/imgui/backends
)

# target_link_libraries( PandemoniumPlatform PRIVATE glfw )
