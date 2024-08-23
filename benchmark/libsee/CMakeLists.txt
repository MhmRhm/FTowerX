add_executable(google_bench_libsee
	google_bench_see_model.cpp
)
target_link_libraries(google_bench_libsee
	PRIVATE libsee_static
)
target_link_libraries(google_bench_libsee
	PRIVATE precompiled
)

Format(google_bench_libsee .)
AddBenchmarks(google_bench_libsee)
