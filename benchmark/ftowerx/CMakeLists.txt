add_executable(ftowerx_benchmark ftowerx_benchmark.cpp)
target_link_libraries(ftowerx_benchmark PRIVATE ftowerx_static)

target_link_libraries(ftowerx_benchmark PRIVATE precompiled)

include(Format)
Format(ftowerx_benchmark .)
AddBenchmarks(ftowerx_benchmark)
