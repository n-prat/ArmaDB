file(GLOB MY_HDRS "*.h")
source_group("Headers" FILES ${MY_HDRS})
include_directories ("${PROJECT_SOURCE_DIR}/sqlite3")

add_library(sqlite SHARED sqlite3.c ${MY_HDRS})
