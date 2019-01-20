cmake_minimum_required(VERSION 3.13)
project(PRI3 C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0 libcurl)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(PRI3 src/main.c src/main_window.c include/main_window.h src/services/http.c include/services/http.h src/data/animal.c include/data/animal.h)
target_link_libraries(PRI3 ${GTK3_LIBRARIES})