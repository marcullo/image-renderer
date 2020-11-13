include(set_inc_path)
include(set_src_path)

project(shell)

file(GLOB sources
	${SRC_PATH}/*.cpp
	${SRC_PATH}/**/*.cpp
)

add_library(${PROJECT_NAME} OBJECT ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC
	${INC_PATH}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	logging
	validation
	rt
)
