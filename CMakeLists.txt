cmake_minimum_required(VERSION 3.31)
project(web_shell VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(WEBKITGTK REQUIRED webkitgtk-6.0)
pkg_check_modules(GTK_LAYER_SHELL REQUIRED gtk4-layer-shell-0)

add_subdirectory(web-shell-js-bridge)

configure_file(templates/constants.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/WebShell/constants.h @ONLY)

add_executable(web_shell src/main.cpp
        src/WebShell/Application.cpp
        src/WebShell/Application.h
        src/WebShell/WidgetWindow.cpp
        src/WebShell/WidgetWindow.h
        src/WebShell/WidgetSpecification.h
        web-shell-js-bridge/main.cpp)

target_include_directories(web_shell
    PRIVATE
        ${GTKMM_INCLUDE_DIRS}
        ${WEBKITGTK_INCLUDE_DIRS}
        ${GTK_LAYER_SHELL_INCLUDE_DIRS}
)

target_link_libraries(web_shell
    PRIVATE
        ${GTKMM_LIBRARIES}
        ${WEBKITGTK_LIBRARIES}
        ${GTK_LAYER_SHELL_LIBRARIES}
)
