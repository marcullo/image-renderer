include(set_inc_path)
include(set_src_path)

project(validation)

file(GLOB sources
	${SRC_PATH}/*.cpp
	${SRC_PATH}/**/*.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC
	${INC_PATH}
)
