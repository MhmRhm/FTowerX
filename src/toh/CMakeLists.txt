add_library(terminal_toh_static STATIC
	terminal_toh.cpp
)
target_include_directories(terminal_toh_static
	PUBLIC "include"
)
target_link_libraries(terminal_toh_static
	PRIVATE precompiled
	PRIVATE libtoh_static
)

BuildInfo(terminal_toh_static)
CleanCoverage(terminal_toh_static)
Format(terminal_toh_static .)
AddCppCheck(terminal_toh_static)
Doxygen(terminal_toh_static src/toh)

add_executable(toh main.cpp)
target_compile_options(toh
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
target_link_libraries(toh
	PRIVATE precompiled
	PRIVATE terminal_toh_static
)
