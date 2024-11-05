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








# cmake_minimum_required(VERSION 3.10)
# project(WebServer)

# set(CMAKE_CXX_STANDARD 17)

# # Function to embed text files as string literals
# function(embed_file_as_string input_file output_variable)
#     file(READ "${input_file}" content)
#     # Escape backslashes and double quotes for C++ compatibility
#     string(REPLACE "\\" "\\\\" content "${content}")
#     string(REPLACE "\"" "\\\"" content "${content}")
#     string(REPLACE "\n" "\\n\"\n\"" content "${content}")
#     set(${output_variable} "\"${content}\"" PARENT_SCOPE)
# endfunction()

# # Embed the HTML file as a string
# embed_file_as_string(${CMAKE_SOURCE_DIR}/web-app/dist/index.html INDEX_HTML)

# # Define paths for the input .ico and output C++ file
# set(FAVICON_FILE "${CMAKE_SOURCE_DIR}/web-app/dist/favicon.ico")
# set(FAVICON_OUTPUT "${CMAKE_BINARY_DIR}/favicon_data.cpp")

# # Use xxd to convert the favicon.ico to a C++ array in favicon_data.cpp
# add_custom_command(
#     OUTPUT ${FAVICON_OUTPUT}
#     COMMAND xxd -i ${FAVICON_FILE} > ${FAVICON_OUTPUT}
#     COMMENT "Embedding favicon.ico as a byte array"
#     DEPENDS ${FAVICON_FILE}
# )

# # Configure web_app.cpp with embedded HTML content
# configure_file(
#     ${CMAKE_SOURCE_DIR}/src/web_app.cpp.in
#     ${CMAKE_BINARY_DIR}/web_app.cpp
#     @ONLY
# )

# # Add executable with generated files
# add_executable(WebServer src/main.cpp ${CMAKE_BINARY_DIR}/web_app.cpp ${FAVICON_OUTPUT})

# target_include_directories(WebServer PRIVATE ${CMAKE_BINARY_DIR})

# # Link libhttpserver
# find_library(HTTPSERVER_LIBRARY NAMES httpserver PATHS /usr/local/lib)
# target_link_libraries(WebServer PRIVATE ${HTTPSERVER_LIBRARY})
