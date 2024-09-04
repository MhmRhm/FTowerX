include(Boost)

add_executable(boost_test_toh
	boost_test_terminal_toh.cpp
)
target_link_libraries(boost_test_toh
	PRIVATE precompiled
	PRIVATE Boost::unit_test_framework
	PRIVATE terminal_toh_static
)

Format(boost_test_toh .)
