cmake_minimum_required(VERSION 3.09)

project(RGE VERSION 0.0.1)

include(GNUInstallDirs)

add_subdirectory(src)

install(TARGETS RGE DESTINATION lib/)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/RGE"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/tinyxml2"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/tmxparser"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)