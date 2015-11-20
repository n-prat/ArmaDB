cmake_minimum_required (VERSION 3.4)

project (Arma_db)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_library(armadb SHARED dllmain.cpp)
include (GenerateExportHeader)

include_directories ("${PROJECT_SOURCE_DIR}/SQLiteDLL")
add_subdirectory (SQLiteDLL) 

