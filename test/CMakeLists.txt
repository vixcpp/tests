#  @file CMakeLists.txt
#  @author Gaspard Kirira
#
#  Copyright 2025, Gaspard Kirira. All rights reserved.
#  https://github.com/vixcpp/vix
#  Use of this source code is governed by a MIT license
#  that can be found in the License file.

file(GLOB TESTS_MODULE_TEST_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

foreach(test_src IN LISTS TESTS_MODULE_TEST_SOURCES)
  get_filename_component(test_name "${test_src}" NAME_WE)

  add_executable("${test_name}" "${test_src}")

  target_compile_features("${test_name}" PRIVATE cxx_std_20)

  target_link_libraries("${test_name}"
    PRIVATE
      vix_tests
  )

  add_test(
    NAME "${test_name}"
    COMMAND "${test_name}"
  )
endforeach()
