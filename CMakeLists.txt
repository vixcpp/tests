#  @file CMakeLists.txt
#  @author Gaspard Kirira
#
#  Copyright 2025, Gaspard Kirira. All rights reserved.
#  https://github.com/vixcpp/vix
#  Use of this source code is governed by a MIT license
#  that can be found in the License file.
#
# ====================================================================
# Vix.cpp - Tests Module
# ====================================================================
# Purpose:
#   Native testing module for Vix.cpp.
#   Provides the public testing API, assertions, registry, runner,
#   summaries, and optional CTest integration.
#
#   Builds as STATIC when sources exist, otherwise as a header-only
#   INTERFACE target.
#
# Public Targets:
#   - vix_tests  : The actual library target (STATIC or INTERFACE)
#   - vix::tests : Namespaced alias for consumers
#
# Public Dependencies:
#   - none by default
#
# Optional Dependencies:
#   - CTest, only when VIX_TESTS_ENABLE_CTEST=ON
#
# Installation/Export:
#   Installs into the umbrella export-set `VixTargets`.
# ====================================================================

cmake_minimum_required(VERSION 3.20)
project(vix_tests VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Global settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Sources discovery
file(GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Options
option(VIX_TESTS_BUILD_TESTS "Build tests module self-tests" OFF)
option(VIX_TESTS_ENABLE_CTEST "Enable optional CTest integration" OFF)

# --------------------------------------------------------------------
# Library target
# --------------------------------------------------------------------

# STATIC
if (TESTS_SOURCES)
  message(STATUS "[tests] Building STATIC library with detected sources.")

  add_library(vix_tests STATIC ${TESTS_SOURCES})
  add_library(vix::tests ALIAS vix_tests)

  target_compile_features(vix_tests PUBLIC cxx_std_20)

  target_include_directories(vix_tests
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

  if (TARGET vix_warnings)
    target_link_libraries(vix_tests PUBLIC vix_warnings)
  endif()

  if (VIX_ENABLE_SANITIZERS AND TARGET vix_sanitizers)
    target_link_libraries(vix_tests PUBLIC vix_sanitizers)
  endif()

  target_compile_definitions(vix_tests
    PUBLIC
      $<$<BOOL:${VIX_TESTS_ENABLE_CTEST}>:VIX_TESTS_ENABLE_CTEST=1>
  )

  set_target_properties(vix_tests PROPERTIES
    OUTPUT_NAME vix_tests
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    EXPORT_NAME tests
  )

  install(TARGETS vix_tests
    EXPORT VixTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

# HEADER-ONLY
else()
  message(STATUS "[tests] Building HEADER-ONLY library (no sources).")

  add_library(vix_tests INTERFACE)
  add_library(vix::tests ALIAS vix_tests)

  target_compile_features(vix_tests INTERFACE cxx_std_20)

  target_include_directories(vix_tests INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

  target_compile_definitions(vix_tests
    INTERFACE
      $<$<BOOL:${VIX_TESTS_ENABLE_CTEST}>:VIX_TESTS_ENABLE_CTEST=1>
  )

  if (VIX_ENABLE_SANITIZERS AND TARGET vix_sanitizers)
    target_link_libraries(vix_tests INTERFACE vix_sanitizers)
  endif()

  install(TARGETS vix_tests
    EXPORT VixTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
endif()

# Install headers
if (NOT (DEFINED VIX_UMBRELLA_BUILD AND VIX_UMBRELLA_BUILD))
  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
          FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")
endif()

# Package config
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/vix_testsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/vix_testsConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/vix_tests"
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/vix_testsConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/vix_testsConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/vix_testsConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/vix_tests"
)

install(EXPORT VixTargets
  FILE VixTargets.cmake
  NAMESPACE vix::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/vix_tests"
)

# Self-tests
if (VIX_TESTS_BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(test)
endif()

# Summary
message(STATUS "------------------------------------------------------")
message(STATUS "vix::tests configured (${PROJECT_VERSION})")
if (TESTS_SOURCES)
  message(STATUS "Mode: STATIC / sources found")
else()
  message(STATUS "Mode: HEADER-ONLY / no sources")
endif()
message(STATUS "CTest bridge: ${VIX_TESTS_ENABLE_CTEST}")
message(STATUS "Include dir: ${CMAKE_CURRENT_SOURCE_DIR}/include (for <vix/tests/...>)")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "------------------------------------------------------")
