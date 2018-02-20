project(TENT)
cmake_minimum_required(VERSION 3.8)

# =========================
# General Config
# =========================
set (CMAKE_CXX_STANDARD 17)
set(HDRS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# =========================
# Options
# =========================
option(TENTBUILDTESTS "build tests" ON)

# =========================
# External Resources
# =========================
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules)
set(CMAKE_PREFIX_PATH ${CMAKE_INSTALL_PREFIX}/share/cmake)

# =========================
# TENT
# =========================
set(TENT_HEADERS ${HDRS_DIR}/TENT.hpp)
set(TENT_LIB_SRC ${LIB_DIR}/TENT.cpp)

add_library(TENT ${TENT_LIB_SRC} ${TENT_HEADERS})

# =========================
# Testing
# =========================
if (TENTBUILDTESTS)
  enable_testing()
endif (TENTBUILDTESTS)
message ("TENTBUILDTESTS : ${TENTBUILDTESTS}")

# macro to make unit tests simpler to build
MACRO(UNIT_TEST NAMESPACE NAME EXTRA_LIBS)
  if (TENTBUILDTESTS)
    add_executable(${NAMESPACE}_test_${NAME} ${NAME}_test.cpp)

    set_property(TARGET ${NAMESPACE}_test_${NAME} PROPERTY FOLDER test)
    target_include_directories(${NAMESPACE}_test_${NAME}
                               PRIVATE
                               ${CMAKE_SOURCE_DIR}/src/test)
    target_link_libraries(${NAMESPACE}_test_${NAME}
                          ${EXTRA_LIBS} # Extra libs MUST be first.
                          )
    add_test(NAME ${NAMESPACE}_test_${NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
             COMMAND $<TARGET_FILE:${NAMESPACE}_test_${NAME}>)
  target_compile_definitions(${NAMESPACE}_test_${NAME}
    PRIVATE -DTHIS_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
endif (TENTBUILDTESTS)
ENDMACRO(UNIT_TEST)

add_subdirectory(src/test)
