add_library(ftowerx_obj OBJECT
	ftowerx.cpp
)
target_compile_options(ftowerx_obj
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
target_include_directories(ftowerx_obj INTERFACE
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(ftowerx_obj PROPERTIES
    PUBLIC_HEADER src/ftowerx/include/ftowerx/ftowerx.h
    POSITION_INDEPENDENT_CODE 1
)
target_link_libraries(ftowerx_obj PRIVATE precompiled)
BuildInfo(ftowerx_obj)

add_library(ftowerx_shared SHARED)
target_link_libraries(ftowerx_shared ftowerx_obj)
add_library(ftowerx_static STATIC)
target_link_libraries(ftowerx_static ftowerx_obj)

add_executable(towerofhanoi main.cpp)
target_link_libraries(towerofhanoi PRIVATE ftxui::screen ftxui::dom ftxui::component)

include(Coverage)
CleanCoverage(ftowerx_static)
include(Format)
Format(ftowerx_static .)
include(CppCheck)
AddCppCheck(ftowerx_obj)
include(Doxygen)
Doxygen(ftowerx src/ftowerx)
