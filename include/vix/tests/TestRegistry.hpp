/**
 *
 *  @file TestRegistry.hpp
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
#ifndef VIX_TESTS_TESTREGISTRY_HPP
#define VIX_TESTS_TESTREGISTRY_HPP

#include <vector>
#include <string>
#include <mutex>

#include <vix/tests/TestCase.hpp>
#include <vix/tests/TestSuite.hpp>

namespace vix::tests
{

  /**
   * @class TestRegistry
   * @brief Central registry for all test cases and suites.
   *
   * This is the single source of truth for test discovery in vix::tests.
   * Tests and suites are registered here, then executed by the TestRunner.
   */
  class TestRegistry
  {
  public:
    /**
     * @brief Returns the global singleton instance.
     */
    static TestRegistry &instance()
    {
      static TestRegistry instance;
      return instance;
    }

    /**
     * @brief Registers a single test case.
     */
    void add(TestCase testCase)
    {
      std::lock_guard<std::mutex> lock(mutex_);
      tests_.push_back(std::move(testCase));
    }

    /**
     * @brief Registers a full test suite.
     */
    void add(TestSuite suite)
    {
      std::lock_guard<std::mutex> lock(mutex_);
      suites_.push_back(std::move(suite));
    }

    /**
     * @brief Returns all registered test cases.
     */
    [[nodiscard]] const std::vector<TestCase> &tests() const noexcept
    {
      return tests_;
    }

    /**
     * @brief Returns all registered test suites.
     */
    [[nodiscard]] const std::vector<TestSuite> &suites() const noexcept
    {
      return suites_;
    }

    /**
     * @brief Clears all registered tests and suites.
     */
    void clear()
    {
      std::lock_guard<std::mutex> lock(mutex_);
      tests_.clear();
      suites_.clear();
    }

    /**
     * @brief Returns total number of test cases (including suites).
     */
    [[nodiscard]] std::size_t total_tests() const noexcept
    {
      std::size_t count = tests_.size();
      for (const auto &suite : suites_)
      {
        count += suite.size();
      }
      return count;
    }

  private:
    TestRegistry() = default;

    std::vector<TestCase> tests_;
    std::vector<TestSuite> suites_;
    mutable std::mutex mutex_;
  };

} // namespace vix::tests

#endif // VIX_TESTS_TESTREGISTRY_HPP
