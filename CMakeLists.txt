cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(txp
  VERSION 2.0.0
  LANGUAGES C CXX)
message(STATUS "${PROJECT_NAME} version ${PROJECT_VERSION}")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(GNUInstallDirs)

# Options

# Outputs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# ----------------------------------------------------------------------------
#                        Compile flags (change as needed).
# ----------------------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

# Build-type specific flags.
set(CMAKE_CXX_FLAGS_RELEASE, "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG, "-g -O0")

message(STATUS "Building with the following extra flags: ${CMAKE_CXX_FLAGS}")

# ----------------------------------------------------------------------------
#                         Locate files (no change needed).
# ----------------------------------------------------------------------------
list(APPEND TXP_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
file(GLOB_RECURSE TXP_INCLUDES "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE TXP_SOURCES "src/*.cpp")
file(GLOB_RECURSE TXP_TESTFILES "test/*.cpp")
set(TXP_TEST_MAIN unit_tests.x)

# ----------------------------------------------------------------------------
#                           Dependencies (no change needed).
# ----------------------------------------------------------------------------
# pthread (check only because should use -pthread instead of -lpthread)
find_package(Threads REQUIRED)

# ----------------------------------------------------------------------------
#                         external (no change needed).
# ----------------------------------------------------------------------------
# Google Test
if(BUILD_TESTING)
  add_subdirectory(
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest EXCLUDE_FROM_ALL)

  if (CMAKE_VERSION VERSION_LESS 2.8.11)
   include_directories("${gtest_SOURCE_DIR}/include")
  endif()
endif()

# fmt
add_subdirectory(${PROJECT_SOURCE_DIR}/external/fmt EXCLUDE_FROM_ALL)

add_library(txp-deps INTERFACE)
target_link_libraries(txp-deps INTERFACE
  fmt-header-only
  Threads::Threads)

# ----------------------------------------------------------------------------
#                         Build! (Change as needed)
# ----------------------------------------------------------------------------
add_library(txp INTERFACE)
target_include_directories(txp
  # Used when building this target:
  # PRIVATE
  # "${TXP_INCLUDE_DIRS}"
  # Used by other targets in this project
  INTERFACE
  $<BUILD_INTERFACE:${TXP_INCLUDE_DIRS}>
  # Used by client projects using an installed b2pl
  INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

add_executable(b2pl src/b2pl.cpp)   # Name of exec. and location of file.
target_link_libraries(b2pl
  PRIVATE
  txp
  txp-deps)

# ----------------------------------------------------------------------------
#                       Make Tests (no change needed).
# ----------------------------------------------------------------------------
if(BUILD_TESTING)
  enable_testing()
  add_executable(${TXP_TEST_MAIN} ${TXP_TESTFILES})
  target_link_libraries(${TXP_TEST_MAIN}
    PRIVATE
    txp
    txp-deps
    gtest
    stdc++fs)
  add_test(unit_tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TXP_TEST_MAIN})
endif()

# ----------------------------------------------------------------------------
#                            Misc (no change needed).
# ----------------------------------------------------------------------------
# Ask CMake to output a compile_commands.json file for use with things like Vim YCM.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Generate .clang_complete (no change needed).
include(GenerateClangComplete)
generate_clang_complete()

# install(TARGETS ppfs
#   EXPORT ppfs-export
#   RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
#   LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
#   ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
#
# ppfs_install_dirs(DIRS "${PPFS_INCLUDE_DIRS}")

install(TARGETS b2pl RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# set(CMAKE_INSTALL_CMAKEDIR)
# install(EXPORT ppfs-export
#   FILE ppfs-config.cmake
#   DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake/ppfs"
#   EXPORT_LINK_INTERFACE_LIBRARIES)
# export(EXPORT ppfs-export
#   FILE ppfs-export.cmake)

# # pthread (check only because should use -pthread instead of -lpthread)
# find_package(Threads REQUIRED)
#
# # Boost
# set(Boost_USE_MULTITHREADED ON)
# find_package(
#   Boost 1.60.0
#   REQUIRED
#   COMPONENTS
#   thread
#   system
#   date_time
#   program_options
#   filesystem
#   chrono
# )
# include_directories(${Boost_INCLUDE_DIRS})
# set(LIBS ${LIBS} ${Boost_LIBRARIES})
#
# # msgpack
# find_package(MsgPack REQUIRED)
# include_directories(${MSGPACK_INCLUDE_DIRS})
# set(LIBS ${LIBS} ${MSGPACK_LIBRARIES})
#
# # mpio
# find_package(Mpio REQUIRED)
# include_directories(${MPIO_INCLUE_DIRS})
# set(LIBS ${LIBS} ${MPIO_LIBRARIES})
#
# # msgpack-rpc
# find_package(MsgPackRpc REQUIRED)
# include_directories(${MSGPACK_RPC_INCLUE_DIRS})
# set(LIBS ${LIBS} ${MSGPACK_RPC_LIBRARIES})
#
# # kyotocabinet
# find_package(KyotoCabinet REQUIRED)
# include_directories(${KYOTOCABINET_INCLUE_DIRS})
# set(LIBS ${LIBS} ${KYOTOCABINET_LIBRARIES})
#
# # glog
# find_package(Glog REQUIRED)
# include_directories(${GLOG_INCLUE_DIRS})
# set(LIBS ${LIBS} ${GLOG_LIBRARIES})
#
# # nlohmann::json
# set(NLOHMANN_JSON_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/vendor/json/src")
# include_directories(${NLOHMANN_JSON_INCLUDE_DIRS})
#
# include_directories(
#   "${PROJECT_SOURCE_DIR}/"
#   "${PROJECT_SOURCE_DIR}/src"
#   "${PROJECT_SOURCE_DIR}/src/lib"
# )
#
# add_subdirectory(src/lib)
# add_subdirectory(src/kcviewer)
# add_subdirectory(src/pputil)
# add_subdirectory(src/ppmds)
