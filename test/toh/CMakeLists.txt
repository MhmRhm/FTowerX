add_executable(google_test_toh
	google_test_terminal_toh.cpp
)

target_link_libraries(google_test_toh
	PRIVATE precompiled
	PRIVATE terminal_toh_static
)

Format(google_test_toh .)
AddTests(google_test_toh)
EnableCoverage(terminal_toh_static)
