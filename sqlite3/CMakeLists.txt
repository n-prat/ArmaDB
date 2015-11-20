
include_directories ("${PROJECT_SOURCE_DIR}/sqlite3")

add_library(sqlite STATIC sqlite3.c)
