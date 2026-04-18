/**
 *
 *  @file TestSuite.hpp
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
#ifndef VIX_TESTS_TESTSUITE_HPP
#define VIX_TESTS_TESTSUITE_HPP

#include <string>
#include <vector>

#include <vix/tests/TestCase.hpp>

namespace vix::tests
{

  /**
   * @class TestSuite
   * @brief Groups multiple test cases under a single suite name.
   *
   * A test suite is a lightweight container used to organize related
   * test cases together.
   */
  class TestSuite
  {
  public:
    /**
     * @brief Constructs an empty test suite.
     */
    TestSuite() = default;

    /**
     * @brief Constructs a test suite with a name.
     */
    explicit TestSuite(std::string name)
        : name_(std::move(name))
    {
    }

    /**
     * @brief Returns the suite name.
     */
    [[nodiscard]] const std::string &name() const noexcept
    {
      return name_;
    }

    /**
     * @brief Adds a test case to the suite.
     */
    void add(TestCase testCase)
    {
      tests_.push_back(std::move(testCase));
    }

    /**
     * @brief Returns all test cases in the suite.
     */
    [[nodiscard]] const std::vector<TestCase> &tests() const noexcept
    {
      return tests_;
    }

    /**
     * @brief Returns true if the suite has no test cases.
     */
    [[nodiscard]] bool empty() const noexcept
    {
      return tests_.empty();
    }

    /**
     * @brief Returns the number of test cases in the suite.
     */
    [[nodiscard]] std::size_t size() const noexcept
    {
      return tests_.size();
    }

  private:
    std::string name_;
    std::vector<TestCase> tests_;
  };

} // namespace vix::tests

#endif // VIX_TESTS_TESTSUITE_HPP
