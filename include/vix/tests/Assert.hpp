/**
 *
 *  @file Assert.hpp
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
#ifndef VIX_TESTS_ASSERT_HPP
#define VIX_TESTS_ASSERT_HPP

#include <string>
#include <stdexcept>
#include <sstream>

namespace vix::tests
{

  /**
   * @class AssertionError
   * @brief Exception thrown when an assertion fails.
   */
  class AssertionError : public std::runtime_error
  {
  public:
    explicit AssertionError(const std::string &message)
        : std::runtime_error(message)
    {
    }
  };

  /**
   * @class Assert
   * @brief Assertion utilities for vix::tests.
   *
   * Provides a minimal and explicit assertion API without macros.
   */
  class Assert
  {
  public:
    /**
     * @brief Fails if the condition is false.
     */
    static void is_true(bool condition, const std::string &message = "")
    {
      if (!condition)
      {
        fail(build_message("Expected condition to be true", message));
      }
    }

    /**
     * @brief Fails if the condition is true.
     */
    static void is_false(bool condition, const std::string &message = "")
    {
      if (condition)
      {
        fail(build_message("Expected condition to be false", message));
      }
    }

    /**
     * @brief Fails if two values are not equal.
     */
    template <typename T, typename U>
    static void equal(const T &expected, const U &actual, const std::string &message = "")
    {
      if (!(expected == actual))
      {
        std::ostringstream oss;
        oss << "Expected [" << expected << "] but got [" << actual << "]";
        fail(build_message(oss.str(), message));
      }
    }

    /**
     * @brief Fails if two values are equal.
     */
    template <typename T, typename U>
    static void not_equal(const T &lhs, const U &rhs, const std::string &message = "")
    {
      if (lhs == rhs)
      {
        std::ostringstream oss;
        oss << "Values should not be equal [" << lhs << "]";
        fail(build_message(oss.str(), message));
      }
    }

    /**
     * @brief Forces a failure.
     */
    static void fail(const std::string &message = "Assertion failed")
    {
      throw AssertionError(message);
    }

  private:
    static std::string build_message(const std::string &base, const std::string &extra)
    {
      if (extra.empty())
        return base;

      return base + " | " + extra;
    }
  };

} // namespace vix::tests

#endif // VIX_TESTS_ASSERT_HPP
