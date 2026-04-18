/**
 *
 *  @file Timer.hpp
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
#ifndef VIX_TESTS_TIMER_HPP
#define VIX_TESTS_TIMER_HPP

#include <chrono>

namespace vix::tests
{

  /**
   * @class Timer
   * @brief Simple high-resolution timer for test execution.
   *
   * Provides a minimal API to measure elapsed time in milliseconds.
   */
  class Timer
  {
  public:
    /**
     * @brief Constructs and starts the timer.
     */
    Timer()
        : start_(clock::now())
    {
    }

    /**
     * @brief Resets the timer to the current time.
     */
    void reset()
    {
      start_ = clock::now();
    }

    /**
     * @brief Returns elapsed time in milliseconds.
     */
    [[nodiscard]] double elapsed_ms() const
    {
      const auto now = clock::now();
      const auto duration = std::chrono::duration<double, std::milli>(now - start_);
      return duration.count();
    }

  private:
    using clock = std::chrono::high_resolution_clock;
    clock::time_point start_;
  };

} // namespace vix::tests

#endif // VIX_TESTS_TIMER_HPP
