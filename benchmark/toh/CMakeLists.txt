add_executable(bench_toh
	bench_terminal_toh.cpp
)

target_link_libraries(bench_toh
	PRIVATE precompiled
	PRIVATE terminal_toh_static
)

Format(bench_toh .)
