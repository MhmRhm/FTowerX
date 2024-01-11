add_executable(ftowerx_test ftowerx_test.cpp)
target_link_libraries(ftowerx_test
	PRIVATE precompiled
	PRIVATE ftowerx_static
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
	PRIVATE ftxui::component
)

include(Format)
Format(ftowerx_test .)
AddTests(ftowerx_test)
EnableCoverage(ftowerx_obj)
