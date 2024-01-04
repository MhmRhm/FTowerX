add_executable(ftowerx_test ftowerx_test.cpp)
target_link_libraries(ftowerx_test PRIVATE ftowerx_static)

target_link_libraries(ftowerx_test PRIVATE precompiled)

include(Format)
Format(ftowerx_test .)
AddTests(ftowerx_test)
EnableCoverage(ftowerx_obj)
