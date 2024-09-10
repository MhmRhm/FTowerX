add_executable(google_bench_libtoh
	google_bench_toh_model.cpp
)

target_link_libraries(google_bench_libtoh
	PRIVATE precompiled
	PRIVATE libtoh_static
)

Format(google_bench_libtoh .)
AddBenchmarks(google_bench_libtoh)
