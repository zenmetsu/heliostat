cmake_minimum_required (VERSION 3.14)

project(heliostat)

set(HELIOSTAT_MAJOR_VERSION 0)
set(HELIOSTAT_MINOR_VERSION 0)
set(HELIOSTAT_PATCH_VERSION 0)
set(HELIOSTAT_VERSION
	${HELIOSTAT_MAJOR_VERSION}.${HELIOSTAT_MINOR_VERSION}.${HELIOSTAT_PATCH_VERSION}
)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (NOT (GCC_VERSION VERSION_GREATER 4.9 OR GCC_VERSION VERSION_EQUAL 4.9))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.9 or greater.")
    endif ()
else ()
    message(FATAL_ERROR "Your C++ compiler does not support C++11")
endif ()


# Add sub-directories
add_subdirectory(main)
