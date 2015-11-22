cmake_minimum_required (VERSION 3.4)

project (Arma_db)
include (GenerateExportHeader)
#set(CMAKE_CONFIGURATION_TYPES "Release")

IF(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
ELSE(WIN32)
	add_definitions(-DUNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
ENDIF(WIN32)

OPTION( WITH_A3DLLPROXY "Rename RVExtension to RVExtension_Dev" OFF )
OPTION( WITH_TESTLIB "Build STATIC lib for use by UnitTest" OFF )

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/sqlite3")
#file(GLOB HDRS_BASE "*.h")
source_group("Headers Files" FILES ${HDRS_BASE})


## Set the list of sources
SET( BASE_SOURCES	
	${PROJECT_SOURCE_DIR}/sqlite.cpp
	${PROJECT_SOURCE_DIR}/stdafx.cpp
	${PROJECT_SOURCE_DIR}/sqlite3/sqlite3.c
)
SET( BASE_HEADERS	
	${PROJECT_SOURCE_DIR}/sqlite.h
	${PROJECT_SOURCE_DIR}/stdafx.h
	${PROJECT_SOURCE_DIR}/targetver.h
	${PROJECT_SOURCE_DIR}/sqlite3/sqlite3.c
)

## BUILD main SHARED dll
# Headers are need here to appear in VS solution
add_library(armadb SHARED ${PROJECT_SOURCE_DIR}/dllmain.cpp ${BASE_SOURCES} ${PROJECT_SOURCE_DIR}/dllmain.h ${BASE_HEADERS})

# UnitTest needs a STATIC lib
# Because the DLL as only one exported function
add_library(armadb_static STATIC ${PROJECT_SOURCE_DIR}/dllmain.cpp ${BASE_SOURCES} ${PROJECT_SOURCE_DIR}/dllmain.h ${BASE_HEADERS}) 
IF(WITH_TESTLIB AND WIN32)	
	# external project created from VS ( windows-only )
	include_external_msproject(UnitTest3 ${PROJECT_SOURCE_DIR}/UnitTest3/UnitTest3.vcxproj)
ENDIF(WITH_TESTLIB AND WIN32)


## OPTION build SHARED dll with entry point renamed to RVExtension_Dev
IF(WITH_A3DLLPROXY)	
	add_library(armadb_dev SHARED ${PROJECT_SOURCE_DIR}/dllmain-dev.cpp ${PROJECT_SOURCE_DIR}/dllmain-dev.h )
	target_link_libraries(armadb_dev debug ${PROJECT_BINARY_DIR}/Debug/armadb_static.lib optimized ${PROJECT_BINARY_DIR}/Release/armadb_static.lib)
	#add_library(armadb_dev SHARED ${PROJECT_SOURCE_DIR}/dllmain-dev.cpp ${PROJECT_SOURCE_DIR}/dllmain-dev.h ${HDRS_BASE})
ENDIF(WITH_A3DLLPROXY)	

