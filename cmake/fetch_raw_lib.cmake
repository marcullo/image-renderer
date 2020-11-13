include_guard()

include(FetchContent)
include(set_ext_path)

function(fetch_raw_lib lib_name url)
	string(TOLOWER ${lib_name} lcName)
	FetchContent_Populate(${lib_name}
		URL ${url}
		SOURCE_DIR ${EXT_PATH}/${lib_name}
		QUIET
	)
	message(STATUS "External content: ${lib_name}: in ${${lcName}_SOURCE_DIR}")
endfunction()
