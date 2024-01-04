function(EnableCoverage target)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        target_compile_options(${target} PRIVATE --coverage -fno-inline)
        target_link_options(${target} PUBLIC --coverage)
    endif()
endfunction()

function(CleanCoverage target)
    add_custom_command(TARGET ${target} PRE_BUILD
    COMMAND "$<$<PLATFORM_ID:UNIX>:find ${CMAKE_BINARY_DIR} -type f -name '*.gcda' -exec rm {} +>"
            "<$<PLATFORM_ID:WIN32>:(ls -Path ${CMAKE_BINARY_DIR} -Filter *.gcda -Recurse).FullName | ForEach-Object -Process {del $_}>"
    )
endfunction()

function(AddCoverage target)
    if(UNIX)
        find_program(LCOV_PATH lcov REQUIRED)
        find_program(GENHTML_PATH genhtml REQUIRED)
        add_custom_target(coverage-${target}
            COMMAND ${LCOV_PATH} -d . --zerocounters
            COMMAND $<TARGET_FILE:${target}>
            COMMAND ${LCOV_PATH} -d . --capture -o coverage.info
            COMMAND ${LCOV_PATH} -r coverage.info '/usr/include/*'
                                 -o filtered.info
            COMMAND ${GENHTML_PATH} -o coverage-${target}
                                    filtered.info --legend
            COMMAND rm -rf coverage.info filtered.info
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()
endfunction()
