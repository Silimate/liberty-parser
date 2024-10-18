################################################################################
# Fetch files
################################################################################

file(GLOB LIB_SOURCES "*.c")
list(REMOVE_ITEM LIB_SOURCES "main.c")
message(${LIB_SOURCES})
file(GLOB LIB_HEADERS "../include/*.h")

################################################################################
# Set variables
################################################################################

SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(BUILD_SHARED_LIBRARIES OFF)
# SET(CMAKE_EXE_LINKER_FLAGS "-static") # SILIMATE: Will not build on macOS

################################################################################
# Library target
################################################################################

# Add library target
add_library(si2dr_liberty STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Tell cmake target's dependencies
target_include_directories(si2dr_liberty
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

################################################################################
# Installation rules
################################################################################

# Install rule for target
install(
    TARGETS si2dr_liberty
    DESTINATION lib
    EXPORT si2dr_libertyConfig
)

# Install rule for headers
install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include/si2dr_liberty.h
    DESTINATION include
)

################################################################################
# SILIMATE: Executable target
################################################################################

# Add executable target
add_executable(parse_liberty ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

# Tell cmake target's dependencies
target_include_directories(parse_liberty
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Set output directory
set_target_properties(parse_liberty PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Link library
target_link_libraries(parse_liberty si2dr_liberty)
