add_executable(google_bench_toh
	google_bench_terminal_toh.cpp
)
target_link_libraries(google_bench_toh
	PRIVATE terminal_toh_static
)
target_link_libraries(google_bench_toh
	PRIVATE precompiled
)

Format(google_bench_toh .)
AddBenchmarks(google_bench_toh)
