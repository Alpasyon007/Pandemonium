# CMake Bulid File
#
# CMake Version
cmake_minimum_required(VERSION 3.12)

# Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Variables set(SOURCE_DIR src) set(VULKAN_PATH C:/VulkanSDK/1.3.231.1) set(GLFW_PATH glfw)

# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# set(LOG_DIR Pandemonium-Log) set(MATH_DIR Pandemonium-Math) set(RENDERER_DIR Pandemonium-Renderer)

# set(LOG_SOURCE_DIR Pandemonium-Log/src) set(MATH_SOURCE_DIR Pandemonium-Math/src) set(RENDERER_SOURCE_DIR Pandemonium-Renderer/src)

# set(CMAKE_CXX_COMPILER_ID MSVC) set(VULKAN_PATH C:/VulkanSDK/1.3.231.1)

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:preprocessor")
endif()

# Define Windows Plaftorm if on Windows
if(WIN32)
	add_compile_definitions(PANDEMONIUM_PLATFORM_WINDOWS)
	add_compile_definitions(PANDEMONIUM_BUILD_DLL)
endif()

# Set the project name
project(Pandemonium)

# Pandemonium Libs
add_library(PandemoniumLog)
add_library(PandemoniumMath)
add_library(PandemoniumPreCompiled)
add_library(PandemoniumEvents)
add_library(PandemoniumImGui)
add_library(PandemoniumPlatform)
add_library(PandemoniumCore)

add_subdirectory(Pandemonium-Log)
add_subdirectory(Pandemonium-Math)
add_subdirectory(Pandemonium-Events)
add_subdirectory(Pandemonium-PreCompiled)
add_subdirectory(Pandemonium-Platform)
add_subdirectory(Pandemonium-ImGui)
add_subdirectory(Pandemonium-Core)

# Third Party Libs
add_library(glad)
add_library(imgui)

add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/imgui)

# Add the executable
add_library(Pandemonium SHARED "Include/Pandemonium.h")

# Define Windows Plaftorm if on Windows
if(WIN32)
	target_compile_definitions(Pandemonium PRIVATE "IMGUI_API=__declspec(dllexport)")
	# target_compile_definitions(PandemoniumGame PRIVATE PANDEMONIUM_PLATFORM_WINDOWS) target_compile_definitions(PandemoniumGame PRIVATE PANDEMONIUM_BUILD_DLL)
endif()

target_precompile_headers(Pandemonium PRIVATE Pandemonium-PreCompiled/headers/ppch.h)

include_directories(
	Pandemonium
	PRIVATE
	Pandemonium-Core/Include
	Pandemonium-Log/Include
	Pandemonium-Math/Include
	Pandemonium-Core/headers
	Pandemonium-Log/headers
	Pandemonium-Math/Pandemonium-Vec/headers
	Pandemonium-Math/Pandemonium-Mat/headers
	Pandemonium-Events/headers
	Pandemonium-PreCompiled/headers
	Pandemonium-Renderer/headers
	Pandemonium-Platform/Windows/headers
	Pandemonium-Platform/OpenGL/headers
	Pandemonium-ImGui/headers
	ThirdParty/glfw
	ThirdParty/glad/include
	ThirdParty/imgui
	ThirdParty/glm
)

target_link_libraries(
	Pandemonium
	PRIVATE PandemoniumCore
			PandemoniumMath
			PandemoniumPreCompiled
			# PandemoniumRenderer
			PandemoniumPlatform
			PandemoniumImGui
			glad
			imgui
			# PandemoniumCore ${VULKAN_PATH}/Lib/vulkan-1.lib
			glfw
			opengl32.lib
)
