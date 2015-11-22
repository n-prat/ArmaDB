cmake_minimum_required (VERSION 3.4)

project (Arma_db)
include (GenerateExportHeader)
#set(CMAKE_CONFIGURATION_TYPES "Release")

IF(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
ELSE(WIN32)
	add_definitions(-DUNIX)
    set(CMAKE_CXX_FLAGS "-Wall -g")
ENDIF(WIN32)

OPTION( WITH_A3DLLPROXY "Rename RVExtension to RVExtension_Dev" OFF )
IF(WITH_A3DLLPROXY)
	SET( RVE_EXT "RVExtension_Dev" )
ELSE(WITH_A3DLLPROXY)
	SET( RVE_EXT "RVExtension" )	
ENDIF(WITH_A3DLLPROXY)	

configure_file(${CMAKE_SOURCE_DIR}/dllmain.h.in ${CMAKE_SOURCE_DIR}/dllmain.h)
configure_file(${CMAKE_SOURCE_DIR}/dllmain.cpp.in ${CMAKE_SOURCE_DIR}/dllmain.cpp)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/sqlite3")
file(GLOB MY_HDRS "*.h")
file(GLOB MY_SRC "*.cpp")
source_group("Headers" FILES ${MY_HDRS})
add_library(armadb SHARED sqlite3/sqlite3.c ${MY_SRC} ${MY_HDRS})
add_library(armadb_static STATIC sqlite3/sqlite3.c ${MY_SRC} ${MY_HDRS}) # needed for unit tests

#set_target_properties(armadb_static PROPERTIES RVExt RVExtension_Dev)
#set_target_properties(armadb PROPERTIES RVExt RVExtension)

#add_subdirectory (sqlite3)


include_external_msproject(UnitTest3 ${PROJECT_SOURCE_DIR}/UnitTest3/UnitTest3.vcxproj)
