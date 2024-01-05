include(FetchContent)

FetchContent_Declare(ftxui
	GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
	GIT_TAG v5.0.0
	GIT_SHALLOW 1
)

option(FTXUI_BUILD_DOCS "Set to ON to build docs" OFF)
option(FTXUI_BUILD_EXAMPLES "Set to ON to build examples" OFF)
option(FTXUI_BUILD_TESTS "Set to ON to build tests" OFF)
option(FTXUI_BUILD_TESTS_FUZZER "Set to ON to enable fuzzing" OFF)
option(FTXUI_ENABLE_INSTALL "Generate the install target" OFF)
option(FTXUI_CLANG_TIDY "Execute clang-tidy" OFF)
option(FTXUI_ENABLE_COVERAGE "Execute code coverage" OFF)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
	FetchContent_Populate(ftxui)
	add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
