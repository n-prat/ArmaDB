
include_directories ("${PROJECT_SOURCE_DIR}/UnitTest" "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/UnitTest/include")
link_directories("C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/UnitTest/lib")

add_library(unittest1 SHARED unittest1.cpp)
