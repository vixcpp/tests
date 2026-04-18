/**
 *
 *  @file Colors.hpp
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
#ifndef VIX_TESTS_COLORS_HPP
#define VIX_TESTS_COLORS_HPP

#include <string>

namespace vix::tests
{

  /**
   * @class Colors
   * @brief ANSI color utilities for terminal output.
   *
   * Provides a minimal API to colorize text output in a portable way.
   * Colors can be disabled globally (useful for CI or non-TTY environments).
   */
  class Colors
  {
  public:
    /**
     * @brief Enables or disables colored output globally.
     */
    static void set_enabled(bool enabled) noexcept
    {
      enabled_ = enabled;
    }

    /**
     * @brief Returns whether colors are enabled.
     */
    [[nodiscard]] static bool enabled() noexcept
    {
      return enabled_;
    }

    /**
     * @brief Wraps text in green color (success).
     */
    [[nodiscard]] static std::string green(const std::string &text)
    {
      return wrap("\033[32m", text);
    }

    /**
     * @brief Wraps text in red color (failure).
     */
    [[nodiscard]] static std::string red(const std::string &text)
    {
      return wrap("\033[31m", text);
    }

    /**
     * @brief Wraps text in yellow color (warning/info).
     */
    [[nodiscard]] static std::string yellow(const std::string &text)
    {
      return wrap("\033[33m", text);
    }

    /**
     * @brief Wraps text in cyan color (highlight).
     */
    [[nodiscard]] static std::string cyan(const std::string &text)
    {
      return wrap("\033[36m", text);
    }

    /**
     * @brief Wraps text in bold style.
     */
    [[nodiscard]] static std::string bold(const std::string &text)
    {
      return wrap("\033[1m", text);
    }

  private:
    static inline bool enabled_{true};

    [[nodiscard]] static std::string wrap(const char *code, const std::string &text)
    {
      if (!enabled_)
        return text;

      return std::string(code) + text + "\033[0m";
    }
  };

} // namespace vix::tests

#endif // VIX_TESTS_COLORS_HPP
