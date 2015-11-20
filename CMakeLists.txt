cmake_minimum_required (VERSION 3.4)

project (Arma_db)
include (GenerateExportHeader)
set(CMAKE_CONFIGURATION_TYPES Release)
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)


include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
add_library(armadb SHARED dllmain.cpp)


add_subdirectory (sqlite3)
add_subdirectory(UnitTest)
