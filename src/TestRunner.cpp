/**
 *
 *  @file TestRunner.cpp
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

#include <iostream>
#include <exception>

#include <vix/tests/TestRunner.hpp>
#include <vix/tests/TestRegistry.hpp>
#include <vix/tests/Assert.hpp>
#include <vix/tests/Summary.hpp>
#include <vix/tests/Timer.hpp>
#include <vix/tests/Colors.hpp>

namespace vix::tests
{

  namespace
  {
    void run_test(const TestCase &test, Summary &summary)
    {
      summary.total++;

      try
      {
        test.run();
        summary.passed++;

        std::cout << Colors::green("[PASS] ") << test.name() << '\n';
      }
      catch (const AssertionError &e)
      {
        summary.failed++;
        std::cout << Colors::red("[FAIL] ") << test.name()
                  << " -> " << e.what() << '\n';
      }
      catch (const std::exception &e)
      {
        summary.failed++;
        std::cout << Colors::red("[ERROR] ") << test.name()
                  << " -> " << e.what() << '\n';
      }
      catch (...)
      {
        summary.failed++;
        std::cout << Colors::red("[ERROR] ") << test.name()
                  << " -> unknown exception\n";
      }
    }
  } // namespace

  RunResult TestRunner::run_all()
  {
    Summary summary;
    Timer timer;

    auto &registry = TestRegistry::instance();

    // Run standalone tests
    for (const auto &test : registry.tests())
    {
      run_test(test, summary);
    }

    // Run suites
    for (const auto &suite : registry.suites())
    {
      std::cout << Colors::cyan("\n[SUITE] " + suite.name()) << '\n';

      for (const auto &test : suite.tests())
      {
        run_test(test, summary);
      }
    }

    summary.duration_ms = timer.elapsed_ms();

    // Final summary
    std::cout << "\n";
    std::cout << Colors::bold("Summary: ") << summary << '\n';

    return RunResult{
        summary.total,
        summary.passed,
        summary.failed};
  }

  int TestRunner::run_all_and_exit()
  {
    auto result = run_all();
    return result.failed == 0 ? 0 : 1;
  }

} // namespace vix::tests
