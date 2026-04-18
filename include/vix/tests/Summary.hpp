/**
 *
 *  @file Summary.hpp
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
#ifndef VIX_TESTS_SUMMARY_HPP
#define VIX_TESTS_SUMMARY_HPP

#include <cstddef>
#include <string>
#include <ostream>

namespace vix::tests
{

  /**
   * @struct Summary
   * @brief Represents a summary of a test run.
   *
   * Contains aggregated statistics and optional execution time.
   */
  struct Summary
  {
    std::size_t total{0};
    std::size_t passed{0};
    std::size_t failed{0};
    double duration_ms{0.0};

    /**
     * @brief Returns true if all tests passed.
     */
    [[nodiscard]] bool success() const noexcept
    {
      return failed == 0;
    }

    /**
     * @brief Returns success ratio between 0.0 and 1.0.
     */
    [[nodiscard]] double success_ratio() const noexcept
    {
      if (total == 0)
        return 1.0;
      return static_cast<double>(passed) / static_cast<double>(total);
    }

    /**
     * @brief Converts the summary to a human-readable string.
     */
    [[nodiscard]] std::string to_string() const
    {
      return "total=" + std::to_string(total) +
             " passed=" + std::to_string(passed) +
             " failed=" + std::to_string(failed) +
             " duration_ms=" + std::to_string(duration_ms);
    }
  };

  /**
   * @brief Streams a Summary to an output stream.
   */
  inline std::ostream &operator<<(std::ostream &os, const Summary &summary)
  {
    os << summary.to_string();
    return os;
  }

} // namespace vix::tests

#endif // VIX_TESTS_SUMMARY_HPP
