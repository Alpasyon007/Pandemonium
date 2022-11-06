target_sources(
	glad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/glad.cpp
	)

target_include_directories(
	glad 
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)