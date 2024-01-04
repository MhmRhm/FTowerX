include(GNUInstallDirs)

install(TARGETS precompiled ftowerx_obj ftowerx_shared ftowerx_static
    EXPORT ftowerxLibrary
    ARCHIVE COMPONENT ftowerx_dev
    LIBRARY COMPONENT ftowerx
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ftowerx
        COMPONENT ftowerx
)

if(UNIX)
    install(CODE "execute_process(COMMAND ldconfig)"
        COMPONENT ftowerx
    )
endif()

install(EXPORT ftowerxLibrary
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MY_PROJECT_NAME}/cmake
    NAMESPACE ${MY_PACKAGE_NAME}::ftowerx::
    COMPONENT ftowerx
)

install(FILES "ProjectConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_PROJECT_NAME}/cmake
    RENAME "${MY_PACKAGE_NAME}Config.cmake"
)

set(CPACK_PACKAGE_VENDOR "Mohammad Rahimi")
set(CPACK_PACKAGE_CONTACT "rahimi.mhmmd@yahoo.com")
set(CPACK_PACKAGE_DESCRIPTION "Tower of Hanoi Implemented by FTXUI")
include(CPack)
