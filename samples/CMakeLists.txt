project(samples)

file(GLOB samples
	${CMAKE_CURRENT_SOURCE_DIR}/*.txt
)

set(RENDERS_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/renders)
file(MAKE_DIRECTORY ${RENDERS_PATH})
message(STATUS "Renders in: ${RENDERS_PATH}")
foreach(samplesrc IN LISTS samples)
	get_filename_component(name ${samplesrc} NAME_WE)
	if(name STREQUAL "CMakeLists")
		continue()
	endif()
	file(MAKE_DIRECTORY ${RENDERS_PATH}/${name})
endforeach()
