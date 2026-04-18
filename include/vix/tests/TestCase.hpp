/**
 *
 *  @file TestCase.hpp
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
#ifndef VIX_TESTS_TESTCASE_HPP
#define VIX_TESTS_TESTCASE_HPP

#include <functional>
#include <string>

namespace vix::tests
{

  /**
   * @class TestCase
   * @brief Represents a single test unit in vix::tests.
   *
   * A test case stores a name and the function that executes the test.
   * The function is expected to throw on failure.
   */
  class TestCase
  {
  public:
    /**
     * @brief Function type used by a test case.
     */
    using Function = std::function<void()>;

    /**
     * @brief Constructs an empty test case.
     */
    TestCase() = default;

    /**
     * @brief Constructs a test case with a name and executable function.
     */
    TestCase(std::string name, Function function)
        : name_(std::move(name)), function_(std::move(function))
    {
    }

    /**
     * @brief Returns the test case name.
     */
    [[nodiscard]] const std::string &name() const noexcept
    {
      return name_;
    }

    /**
     * @brief Returns true if the test case has an executable function.
     */
    [[nodiscard]] bool valid() const noexcept
    {
      return static_cast<bool>(function_);
    }

    /**
     * @brief Executes the test case.
     */
    void run() const
    {
      if (function_)
      {
        function_();
      }
    }

  private:
    std::string name_;
    Function function_;
  };

} // namespace vix::tests

#endif // VIX_TESTS_TESTCASE_HPP
