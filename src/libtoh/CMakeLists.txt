add_library(libtoh_obj OBJECT
	toh_model.cpp
)

target_compile_options(libtoh_obj
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)

target_include_directories(libtoh_obj
	PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	PUBLIC "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

set_target_properties(libtoh_obj PROPERTIES
	PUBLIC_HEADER src/libtoh/include/libtoh/toh_model.h
	POSITION_INDEPENDENT_CODE 1
)

target_link_libraries(libtoh_obj
	PRIVATE precompiled
)

add_library(libtoh_shared SHARED)
target_link_libraries(libtoh_shared libtoh_obj)
set_target_properties(libtoh_shared PROPERTIES
	PREFIX "lib"
	OUTPUT_NAME "toh$<$<CONFIG:Debug>:d>"
)

add_library(libtoh_static STATIC)
target_link_libraries(libtoh_static libtoh_obj)
set_target_properties(libtoh_static PROPERTIES
	PREFIX "lib"
	OUTPUT_NAME "toh$<$<CONFIG:Debug>:d>"
)

BuildInfo(libtoh_obj)
CleanCoverage(libtoh_static)
Format(libtoh_static .)
AddCppCheck(libtoh_static)
Doxygen(libtoh_static src/libtoh)
