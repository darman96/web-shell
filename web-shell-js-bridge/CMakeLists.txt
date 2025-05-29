
find_package(PkgConfig)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(WEBKITGTK REQUIRED webkitgtk-6.0)
pkg_check_modules(GTK_LAYER_SHELL REQUIRED gtk4-layer-shell-0)

add_library(web-shell-js-bridge MODULE
        main.cpp
)

target_include_directories(web-shell-js-bridge
    PRIVATE
        ${WEBKITGTK_INCLUDE_DIRS}
)

target_link_libraries(web-shell-js-bridge
        ${WEBKITGTK_LIBRARIES}
)

set_target_properties(web-shell-js-bridge
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/web-shell-js-bridge
)