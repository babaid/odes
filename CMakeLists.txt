cmake_minimum_required(VERSION 3.0)
set(PROJECT_VERSION "1.0")
project(odes VERSION ${PROJECT_VERSION})

include(GNUInstallDirs)
add_library(odes STATIC src/odes.cpp) 
enable_testing()
add_executable(Test src/main.cpp test/test.cpp include/odes.h test/catch2/catch.hpp)
target_link_libraries(Test odes)
set_target_properties(odes PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/odes.h)

configure_file(odes.pc.in odes.pc @ONLY)

target_include_directories(odes PRIVATE include)
target_include_directories(odes PRIVATE src)

add_test(NAME Test COMMAND Test)
add_custom_command(TARGET Test
                   POST_BUILD
                   COMMAND ctest -C $<CONFIGURATION> --output-on-failure)



install(TARGETS odes
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/odes.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)








