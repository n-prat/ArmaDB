cmake_minimum_required (VERSION 3.4)

project (Arma_db)
include (GenerateExportHeader)
#set(CMAKE_CONFIGURATION_TYPES "Release")
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)


include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
file(GLOB MY_HDRS "*.h")
source_group("Headers" FILES ${MY_HDRS})
add_library(armadb SHARED dllmain.cpp ${MY_HDRS})


add_subdirectory (sqlite3)


include_external_msproject(UnitTest3 ${PROJECT_SOURCE_DIR}/UnitTest3/UnitTest3.vcxproj)
