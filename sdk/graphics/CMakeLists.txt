include(set_inc_path)
include(set_src_path)

project(graphics)

file(GLOB sources
	${SRC_PATH}/*.cpp
	${SRC_PATH}/**/*.cpp
)

add_library(${PROJECT_NAME} INTERFACE ${sources})

target_include_directories(${PROJECT_NAME} INTERFACE
	${INC_PATH}
)
