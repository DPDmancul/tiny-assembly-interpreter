cmake_minimum_required(VERSION 3.0.0)
project(TinyAssemblyInterpreter VERSION 1.0.0 LANGUAGES C)
set(CMAKE_C_STANDARD 99)

set(SRC_FOLDER src)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# BUILD TARGET

add_subdirectory (${SRC_FOLDER})
target_compile_definitions(TinyAssemblyInterpreter PRIVATE __TAS_VERSION__="${PROJECT_VERSION}")


# TEST TARGET

include (CTest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)
add_subdirectory (test)
add_custom_target(
  test_memcheck
  COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --test-action memcheck # Do test and memory check
  COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log" # Print Valgrind output
)


# DOXYGEN TARGET

find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create the HTML based documentation (requires Doxygen)." ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()

  set(doxy_main_page "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${doxyfile_in} ${doxyfile} @ONLY)

  add_custom_target(
    doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM
  )
endif()