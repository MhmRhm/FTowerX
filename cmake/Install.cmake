include(GNUInstallDirs)

add_library(toh::precompiled ALIAS precompiled)
add_library(toh::libtoh_obj ALIAS libtoh_obj)
add_library(toh::libtoh_static ALIAS libtoh_static)
add_library(toh::libtoh_shared ALIAS libtoh_shared)

export(
	TARGETS precompiled libtoh_obj libtoh_static libtoh_shared
	NAMESPACE toh::
	FILE "${PROJECT_BINARY_DIR}/TohLibrary.cmake"
)

install(TARGETS precompiled libtoh_obj libtoh_static libtoh_shared
	EXPORT TohLibrary
	ARCHIVE COMPONENT Runtime
	LIBRARY COMPONENT Development
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/toh
		COMPONENT Development
)

if(UNIX)
	install(CODE "execute_process(COMMAND ldconfig)"
		COMPONENT Development
	)
endif()

install(EXPORT TohLibrary
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/toh/cmake
	NAMESPACE toh::
	COMPONENT Development
)

install(FILES "TohConfig.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/toh/cmake
)

install(TARGETS toh
	RUNTIME COMPONENT Runtime
)

set(CPACK_PACKAGE_CONTACT "Mohammad Rahimi <https://github.com/MhmRhm>")
set(CPACK_PACKAGE_DESCRIPTION "FTowerX: Tower of Hanoi implemented with FTXUI.")
include(CPack)
