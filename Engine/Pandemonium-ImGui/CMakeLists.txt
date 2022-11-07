target_sources(
	PandemoniumImGui
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers/ImGuiLayer.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/ImGuiLayer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ImGuiBuild.cpp

)

target_include_directories(
	PandemoniumImGui 
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/headers
	../Pandemonium-Core/headers
	../Pandemonium-Platform/OpenGL
	../ThirdParty/glfw/include
	../ThirdParty/imgui
	../ThirdParty/imgui/backends
)