target_sources(
	PandemoniumPreCompiled
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers/ppch.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/ppch.cpp
)

target_include_directories(
	PandemoniumPreCompiled
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)