###############################################################################
# Project setup
###############################################################################

cmake_minimum_required(VERSION 3.5)
project(Liberty C CXX)
set(CMAKE_BUILD_TYPE DEBUG)

###############################################################################
# Fetch files
###############################################################################

file(GLOB LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)
list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/syntform.c)
message(${LIB_SOURCES})
file(GLOB LIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

###############################################################################
# Flex/Bison targets
###############################################################################

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
bison_target(liberty_parser ${CMAKE_CURRENT_SOURCE_DIR}/src/liberty_parser.y ${CMAKE_CURRENT_SOURCE_DIR}/src/liberty_parser.c)
bison_target(syntax_parser ${CMAKE_CURRENT_SOURCE_DIR}/src/syntax_parser.y ${CMAKE_CURRENT_SOURCE_DIR}/src/syntax_parser.c)
flex_target(token ${CMAKE_CURRENT_SOURCE_DIR}/src/token.l ${CMAKE_CURRENT_SOURCE_DIR}/src/token.c)
flex_target(synttok ${CMAKE_CURRENT_SOURCE_DIR}/src/synttok.l ${CMAKE_CURRENT_SOURCE_DIR}/src/synttok.c)
add_flex_bison_dependency(token liberty_parser)
add_flex_bison_dependency(synttok syntax_parser)
set(FLEX_BISON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/liberty_parser.c ${CMAKE_CURRENT_SOURCE_DIR}/src/syntax_parser.c ${CMAKE_CURRENT_SOURCE_DIR}/src/synttok.c ${CMAKE_CURRENT_SOURCE_DIR}/src/token.c)

###############################################################################
# Executable target
###############################################################################

# Add executable target
add_executable(liberty ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${LIB_SOURCES} ${LIB_HEADERS} ${FLEX_BISON_SOURCES})

# Add include directories
target_include_directories(liberty PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
