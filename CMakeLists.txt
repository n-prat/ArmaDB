cmake_minimum_required (VERSION 3.4)

project (Arma_db)
include (GenerateExportHeader)
#set(CMAKE_CONFIGURATION_TYPES "Release")
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)


include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/sqlite3")
file(GLOB MY_HDRS "*.h")
file(GLOB MY_SRC "*.cpp")
source_group("Headers" FILES ${MY_HDRS})
add_library(armadb SHARED sqlite3/sqlite3.c ${MY_SRC} ${MY_HDRS})
add_library(armadb_static STATIC sqlite3/sqlite3.c ${MY_SRC} ${MY_HDRS}) # needed for unit tests


#add_subdirectory (sqlite3)


include_external_msproject(UnitTest3 ${PROJECT_SOURCE_DIR}/UnitTest3/UnitTest3.vcxproj)
