include(set_inc_path)
include(set_src_path)

project(renderer LANGUAGES CXX)

file(GLOB sources
	${SRC_PATH}/*.cpp
	${SRC_PATH}/**/*.cpp
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE
	${INC_PATH}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
	dice
	graphics
	logging
	shell
)

include(print_target_size)
