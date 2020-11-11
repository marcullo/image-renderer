cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(set_runtime_output_directory)

project(image_renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_CXX_FLAGS_DEBUG "-O1 -ggdb3 -DDEBUG=1")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -g0 -DNDEBUG=1")
set(CMAKE_C_FLAGS_DEBUG "-O1 -ggdb3 -DDEBUG=1")
set(CMAKE_C_FLAGS_RELEASE "-Os -g0 -DNDEBUG=1")

set(common_options
	-fdiagnostics-color=always
	-fno-builtin
	-fno-strict-aliasing
	-fomit-frame-pointer
	-fshort-enums
)
add_compile_options(
	${common_options}
	${debug_optimization_options}

	-ffunction-sections
	-fdata-sections
	-fmerge-all-constants
	-fno-common

	-Wall
	-Wextra
	-Werror
)
add_compile_definitions(
	BUILD_MODE_STR=$<IF:$<CONFIG:DEBUG>,"Debug","Release">
)
add_link_options(
	-Wl,--gc-sections
)

add_subdirectory(commander)
add_subdirectory(renderer)
add_subdirectory(sdk)
