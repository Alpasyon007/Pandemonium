# CMake Bulid File
#
# CMake Version
cmake_minimum_required(VERSION 3.12)

# Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER_ID MSVC)

set(ENGINE_DLL_PATH ${CMAKE_CURRENT_BINARY_DIR}/Engine/Debug/Pandemonium.dll)
set(ENGINE_LIB_PATH ${CMAKE_CURRENT_BINARY_DIR}/Engine/Debug/Pandemonium.lib)
set(ENGINE_PATH "../Engine")

if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:preprocessor")
endif()

# Define Windows Plaftorm if on Windows
if (WIN32)
    add_compile_definitions(PANDEMONIUM_PLATFORM_WINDOWS)
    add_compile_definitions(PANDEMONIUM_BUILD_DLL)
endif()

# Set the project name
project(PandemoniumGame)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${ENGINE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Engine)

add_executable(
	PandemoniumGame
	${CMAKE_CURRENT_SOURCE_DIR}/src/PandemoniumGame.cpp
)

target_include_directories(
	PandemoniumGame
	PRIVATE
	${ENGINE_PATH}/Include
	${ENGINE_PATH}/Pandemonium-Math/Include
	${ENGINE_PATH}/Pandemonium-Log/Include
	${ENGINE_PATH}/Pandemonium-Core/headers
	${ENGINE_PATH}/Pandemonium-Log/headers
	${ENGINE_PATH}/Pandemonium-Math/Pandemonium-Vec/headers
	${ENGINE_PATH}/Pandemonium-Math/Pandemonium-Mat/headers
	${ENGINE_PATH}/Pandemonium-Events/headers
	${ENGINE_PATH}/Pandemonium-PreCompiled/headers
	${ENGINE_PATH}/Pandemonium-Renderer/headers
)

target_link_libraries(
	PandemoniumGame 
	PRIVATE
	${ENGINE_LIB_PATH}
)

add_custom_command(TARGET PandemoniumGame POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${ENGINE_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Debug)

# # Remove old DLL
# file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/Debug/Pandemonium.dll)

# # Move Engine DLL to Game Binary Location
# file(
# 	COPY ${ENGINE_DLL_PATH}
# 	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug
# )