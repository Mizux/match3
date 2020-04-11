cmake_minimum_required(VERSION 3.14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(Meta LANGUAGES NONE)

##########################
##  INSTALL PARAMETERS  ##
##########################
# Offer the user the choice of overriding the installation directories
set(CMAKE_INSTALL_PREFIX install)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")

##############################
##  COMPILATION PARAMETERS  ##
##############################
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/usr/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/usr/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/usr/bin)
set(CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/usr/share/doc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(Signal)
add_subdirectory(Match3)
add_subdirectory(Match3App)
