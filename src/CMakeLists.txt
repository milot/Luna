project(luna)
cmake_minimum_required (VERSION 2.6)
aux_source_directory(. SRC_LIST)
SET(luna_SOURCES main.cpp Luna.cpp)
SET(luna_HEADERS Luna.h)

ADD_EXECUTABLE(luna ${luna_SOURCES}
    ${luna_HEADERS_MOC})

target_link_libraries(luna lua)

# Add C++11 support :)
add_definitions (
    -std=c++11
)
