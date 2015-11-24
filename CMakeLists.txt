cmake_minimum_required (VERSION 3.4)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

project (Arma_db)
include (GenerateExportHeader)
set(CMAKE_CONFIGURATION_TYPES "Release;Debug")


# Use @LIC_C@ in a file to add the C-formatted Licence Header
# Find the list of cpp/c/h files in the source dir and call configure_file on them
# (not faster than copy-pasting manually but who cares)
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

# Get the list of files to configure
# Also, Do NOT use that list list for compiling/linking
# cf warning in CMake docs
# [GLOB_RECURSE goes in build/ so we do it manually]
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
	message("Configuring ${loop_var}")
	configure_file(${loop_var} ${loop_var} @ONLY )
endforeach(loop_var)


set(Boost_USE_STATIC_LIBS ON)
set(BOOST_LIBRARYDIR "W:/Programmes/boost/lib")
find_package( Boost 1.59.0 )
find_package( Boost 1.59.0 REQUIRED COMPONENTS program_options)

message("Boost_PROGRAM_OPTIONS :\n   ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} \n   ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}" )
message("Boost include dir :\n   ${Boost_INCLUDE_DIR}" )

IF(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
	#add_definitions(/Yc"stdafx.h") #precompiled headers
	#set_source_files_properties(${PROJECT_SOURCE_DIR}/sqlite3/sqlite3.c PROPERTIES COMPILE_FLAGS /Y-)
ELSE(WIN32)
	add_definitions(-DUNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
ENDIF(WIN32)

OPTION( WITH_A3DLLPROXY "Rename RVExtension to RVExtension_Dev" OFF )
OPTION( WITH_TESTS "Build Tests(only on windows)" OFF )


include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/sqlite3")
include_directories("${Boost_INCLUDE_DIR}")

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
	${PROJECT_SOURCE_DIR}/sqlite3/sqlite3.h
)

## BUILD main SHARED dll
# Headers are need here to appear in VS solution
add_library(armadb SHARED ${PROJECT_SOURCE_DIR}/dllmain.cpp ${BASE_SOURCES} ${PROJECT_SOURCE_DIR}/dllmain.h ${BASE_HEADERS})
# Link with Boost's program_options (not an header-only lib)
target_link_libraries(armadb debug ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} optimized ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )	
cotire(armadb)

# UnitTest needs a STATIC lib
# Because the DLL as only one exported function
add_library(armadb_static STATIC ${PROJECT_SOURCE_DIR}/dllmain.cpp ${BASE_SOURCES} ${PROJECT_SOURCE_DIR}/dllmain.h ${BASE_HEADERS}) 
IF(WITH_TESTS AND MSVC)		
	#include_external_msproject(UnitTest3 ${PROJECT_SOURCE_DIR}/UnitTest3/UnitTest3.vcxproj)
	#C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\UnitTest\include
	#C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\UnitTest\lib
	include_directories("C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/UnitTest/include")
	add_library(Tests SHARED ${PROJECT_SOURCE_DIR}/UnitTest3/unittest1.cpp ${PROJECT_SOURCE_DIR}/UnitTest3/stdafx.cpp ${PROJECT_SOURCE_DIR}/UnitTest3/stdafx.h ${PROJECT_SOURCE_DIR}/UnitTest3/targetver.h)
	target_link_libraries(Tests "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/UnitTest/lib/Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib")
	target_link_libraries(Tests debug ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} optimized ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )
	target_link_libraries(Tests debug ${PROJECT_BINARY_DIR}/Debug/armadb_static.lib optimized ${PROJECT_BINARY_DIR}/Release/armadb_static.lib)	
ENDIF(WITH_TESTS AND MSVC)


## OPTION build SHARED dll with entry point renamed to RVExtension_Dev
IF(WITH_A3DLLPROXY)	
	add_library(armadb_dev SHARED ${PROJECT_SOURCE_DIR}/dllmain-dev.cpp ${PROJECT_SOURCE_DIR}/dllmain-dev.h )
	target_link_libraries(armadb_dev debug ${PROJECT_BINARY_DIR}/Debug/armadb_static.lib optimized ${PROJECT_BINARY_DIR}/Release/armadb_static.lib)	
	target_link_libraries(armadb_dev debug ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG} optimized ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} )
ENDIF(WITH_A3DLLPROXY)	

