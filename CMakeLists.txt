cmake_minimum_required(VERSION 3.10)
project(WebServer)

set(CMAKE_CXX_STANDARD 17)

# Include CMakeRC.cmake
include(CMakeRC.cmake)

# Embed files using CMakeRC
cmrc_add_resource_library(resources
    NAMESPACE res
    WHENCE ${CMAKE_SOURCE_DIR}/web-app/dist
    ${CMAKE_SOURCE_DIR}/web-app/dist/index.html
    ${CMAKE_SOURCE_DIR}/web-app/dist/favicon.ico
)

# Set up your main executable
add_executable(WebServer src/main.cpp)

# Find libhttpserver
find_library(HTTPSERVER_LIBRARY NAMES httpserver PATHS /usr/local/lib)

# Link the embedded resource library and libhttpserver with your executable
target_link_libraries(WebServer PRIVATE resources ${HTTPSERVER_LIBRARY})