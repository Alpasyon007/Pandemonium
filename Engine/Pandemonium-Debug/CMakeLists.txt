set_target_properties(PandemoniumDebug PROPERTIES LINKER_LANGUAGE CXX)

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

target_sources(PandemoniumDebug PUBLIC ${HEADERS} ${SRC})

target_include_directories(
	PandemoniumDebug
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers
			${CMAKE_CURRENT_SOURCE_DIR}/src
)