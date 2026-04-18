/**
 *
 *  @file TestRunner.hpp
 *  @author Gaspard Kirira
 *
 *  Copyright 2025, Gaspard Kirira.
 *  All rights reserved.
 *  https://github.com/vixcpp/vix
 *
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Vix.cpp
 */
#ifndef VIX_TESTS_TESTRUNNER_HPP
#define VIX_TESTS_TESTRUNNER_HPP

#include <cstddef>

namespace vix::tests
{

  /**
   * @struct RunResult
   * @brief Aggregated result of a test run.
   */
  struct RunResult
  {
    std::size_t total{0};
    std::size_t passed{0};
    std::size_t failed{0};
  };

  /**
   * @class TestRunner
   * @brief Executes all registered tests from the TestRegistry.
   *
   * The runner is responsible for:
   *  - iterating over tests and suites
   *  - catching assertion failures
   *  - aggregating results
   *  - returning a final status
   */
  class TestRunner
  {
  public:
    /**
     * @brief Runs all registered tests.
     * @return RunResult containing aggregated statistics.
     */
    static RunResult run_all();

    /**
     * @brief Runs all registered tests and returns a process exit code.
     * @return 0 if all tests passed, non-zero otherwise.
     */
    static int run_all_and_exit();

  private:
    TestRunner() = default;
  };

} // namespace vix::tests

#endif // VIX_TESTS_TESTRUNNER_HPP
