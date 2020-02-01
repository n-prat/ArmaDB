cmake_minimum_required (VERSION 3.4)

## Cotire
#set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
#include(cotire)

project (Arma_db)
#include (GenerateExportHeader)
set(CMAKE_CONFIGURATION_TYPES "Release;Debug")

## Use @LIC_C@ in a file to add the C-formatted Licence Header
## Find the list of cpp/c/h files in the source dir and call configure_file on them
## (not faster than copy-pasting manually but who cares)
SET( LICENCE "	
	ArmaDB - Arma Extension which allows to connect to SQLite
    Copyright (C) 2015  Nathan Prat

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
")
SET(LIC_C "/*\n${LICENCE}\n*/")

## Get the list of files to configure
## Also, Do NOT use that list list for compiling/linking
## cf warning in CMake docs
## [GLOB_RECURSE goes in build/ so we do it manually]
file(GLOB MY_SOURCES 
		"${PROJECT_SOURCE_DIR}/*.cpp" 
		"${PROJECT_SOURCE_DIR}/*.c"
		"${PROJECT_SOURCE_DIR}/*.h"
		"UnitTest3/*.cpp"
		"UnitTest3/*.c"
		"UnitTest3/*.h"
	)
	
# Configure them
foreach(loop_var ${MY_SOURCES})
	#message("Configuring ${loop_var}")
	configure_file(${loop_var} ${loop_var} @ONLY )
endforeach(loop_var)

## Boost
set(BOOST_INCLUDEDIR "W:/Programmes/boost/include/boost-1_59")
find_package( Boost 1.59.0 REQUIRED )
#set(Boost_USE_STATIC_LIBS ON)
#set(BOOST_LIBRARYDIR "W:/Programmes/boost/lib")
#find_package( Boost 1.59.0 REQUIRED COMPONENTS program_options)
#message("Boost_PROGRAM_OPTIONS :\n   ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} \n   ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}" )
message("Boost include dir :\n   ${Boost_INCLUDE_DIR}" )

IF(WIN32)
    add_definitions(-DWIN32)
	
	## Warnings : Wall will show errors on MS and Boost libs
	#add_compile_options(/Wall /WX) # Wall + Werror
	add_compile_options(/W4 /WX) # W4	
	set_source_files_properties(${PROJECT_SOURCE_DIR}/sqlite3/sqlite3.c COMPILE_FLAGS /W3)
	
	#add_compile_options(/MP /INCREMENTAL) # Build with Multiple Processes + Incremental
	add_compile_options(/Gm /Zi) # Minimal Rebuild
	add_compile_options(-D_SCL_SECURE_NO_WARNINGS) # Needed for Boost
	add_compile_options(/EHa) # /EHsc # Yes with Extern C functions (/EHs) #Yes with SEH Exceptions (/EHa) #Yes with Extern C functions (/EHs)
	#add_definitions(/Yc"stdafx.h") #precompiled headers
	#set_source_files_properties(${PROJECT_SOURCE_DIR}/sqlite3/sqlite3.c PROPERTIES COMPILE_FLAGS /Y-)
ELSE(WIN32)
	add_definitions(-DUNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	add_compile_options(-Wall -Wextra -Werror) # Wall + Werror
ENDIF(WIN32)

OPTION( WITH_A3DLLPROXY "Rename RVExtension to RVExtension_Dev" OFF )
OPTION( WITH_TESTS "Build Tests(only on windows)" OFF )

## Set the list of sources
SET( BASE_SOURCES	
	${PROJECT_SOURCE_DIR}/sqlite.cpp
	#${PROJECT_SOURCE_DIR}/stdafx.cpp
	${PROJECT_SOURCE_DIR}/sqlite3/sqlite3.c
	${PROJECT_SOURCE_DIR}/config.cpp
	${PROJECT_SOURCE_DIR}/statement.cpp
)
SET( BASE_HEADERS	
	${PROJECT_SOURCE_DIR}/sqlite.h
	#${PROJECT_SOURCE_DIR}/stdafx.h
	${PROJECT_SOURCE_DIR}/targetver.h
	${PROJECT_SOURCE_DIR}/sqlite3/sqlite3.h
	${PROJECT_SOURCE_DIR}/config.h
	${PROJECT_SOURCE_DIR}/statement.h
)
SET( SRCS_PLUS_MAIN "${PROJECT_SOURCE_DIR}/dllmain.cpp;${BASE_SOURCES}")
SET( HDRS_PLUS_MAIN "${PROJECT_SOURCE_DIR}/dllmain.h;${BASE_HEADERS}")
SET( SRCS_PLUS_DEV "${PROJECT_SOURCE_DIR}/dllmain-dev.cpp;${BASE_SOURCES}")
SET( HDRS_PLUS_DEV "${PROJECT_SOURCE_DIR}/dllmain-dev.h;${BASE_HEADERS}")

## BUILD main SHARED dll
## Headers are needed here to appear in VS solution
#message("sources for armadb:\n ${SRCS_PLUS_MAIN}")
#message("headers for armadb:\n ${HDRS_PLUS_MAIN}")
add_library(armadb SHARED ${SRCS_PLUS_MAIN} ${HDRS_PLUS_MAIN}) 
target_include_directories(armadb SYSTEM PUBLIC "${PROJECT_SOURCE_DIR}/sqlite3" SYSTEM PUBLIC "${Boost_INCLUDE_DIR}")


## Link with Boost's program_options (not an header-only lib)
#target_link_libraries(armadb debug ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} optimized ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )	

## Cotire
#cotire(armadb)

## UnitTest needs a STATIC lib
## Because the DLL as only one exported function
IF(WITH_TESTS OR WITH_A3DLLPROXY)	
	add_library(armadb_static STATIC ${SRCS_PLUS_MAIN} ${HDRS_PLUS_MAIN}) 
	target_include_directories(armadb_static SYSTEM PUBLIC "${PROJECT_SOURCE_DIR}/sqlite3" SYSTEM PUBLIC "${Boost_INCLUDE_DIR}")
ENDIF(WITH_TESTS OR WITH_A3DLLPROXY)

IF(WITH_TESTS AND MSVC)		
	add_library(Tests SHARED ${PROJECT_SOURCE_DIR}/UnitTest3/unittest1.cpp ${PROJECT_SOURCE_DIR}/UnitTest3/stdafx.cpp ${PROJECT_SOURCE_DIR}/UnitTest3/stdafx.h ${PROJECT_SOURCE_DIR}/UnitTest3/targetver.h)
	target_include_directories(Tests SYSTEM PUBLIC "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/UnitTest/include")
	target_include_directories(Tests SYSTEM PUBLIC "${PROJECT_SOURCE_DIR}/sqlite3" SYSTEM PUBLIC "${Boost_INCLUDE_DIR}")
	
	target_link_libraries(Tests "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/UnitTest/lib/Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib")	
	target_link_libraries(Tests armadb_static)	
	
	#target_link_libraries(Tests debug ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} optimized ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )
ENDIF(WITH_TESTS AND MSVC)

## OPTION build SHARED dll with entry point renamed to RVExtension_Dev
IF(WITH_A3DLLPROXY)	
	add_library(armadb_dev SHARED ${PROJECT_SOURCE_DIR}/dllmain-dev.cpp ${PROJECT_SOURCE_DIR}/dllmain-dev.h )
	target_link_libraries(armadb_dev armadb_static)	
ENDIF(WITH_A3DLLPROXY)	
