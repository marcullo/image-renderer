include(set_inc_path)
include(set_ext_path)
include(set_src_path)

include(fetch_raw_lib)
fetch_raw_lib(bitmap http://www.partow.net/downloads/bitmap.zip)

project(graphics)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/renders)
file(GLOB sources
	${SRC_PATH}/*.cpp
	${SRC_PATH}/**/*.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC
	${INC_PATH}
	${EXT_PATH}
)
target_link_libraries(${PROJECT_NAME} PUBLIC
	dice
	logging
	validation
)
