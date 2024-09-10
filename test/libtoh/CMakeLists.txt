add_executable(google_test_libtoh
	google_test_toh_model.cpp
)

target_link_libraries(google_test_libtoh
	PRIVATE libtoh_static
	PRIVATE precompiled
)

Format(google_test_libtoh .)
AddTests(google_test_libtoh)
EnableCoverage(libtoh_obj)
