set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/glfw ${CMAKE_CURRENT_SOURCE_DIR}/../Game/build/Engine)

target_sources(
	PandemoniumPlatform
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Windows/headers/WindowsWindow.h
	${CMAKE_CURRENT_SOURCE_DIR}/Windows/src/WindowsWindow.cpp
)

target_include_directories(
	PandemoniumPlatform 
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/headers
	../ThirdParty/glfw/Include
)

# target_link_libraries(
#     PandemoniumPlatform
#     PRIVATE
#     glfw
# )