add_executable(google_bench_see
	google_bench_terminal_see.cpp
)
target_link_libraries(google_bench_see
	PRIVATE terminal_see_static
)
target_link_libraries(google_bench_see
	PRIVATE precompiled
)

Format(google_bench_see .)
AddBenchmarks(google_bench_see)
