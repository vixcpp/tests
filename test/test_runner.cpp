/**
 *
 *  @file test_runner.cpp
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

#include <vix/tests/TestRunner.hpp>
#include <vix/tests/TestRegistry.hpp>
#include <vix/tests/TestCase.hpp>
#include <vix/tests/TestSuite.hpp>
#include <vix/tests/Assert.hpp>

int main()
{
  using namespace vix::tests;

  auto &registry = TestRegistry::instance();
  registry.clear();

  // Add standalone tests
  registry.add(TestCase("runner pass test", []
                        { Assert::is_true(true); }));

  registry.add(TestCase("runner fail test", []
                        { Assert::is_true(false, "intentional failure"); }));

  // Add suite
  TestSuite suite("runner suite");

  suite.add(TestCase("suite pass", []
                     { Assert::equal(1 + 1, 2); }));

  suite.add(TestCase("suite fail", []
                     { Assert::equal(2 * 2, 5, "intentional failure"); }));

  registry.add(std::move(suite));

  // Run
  auto result = TestRunner::run_all();

  // Validate results
  Assert::equal(result.total, static_cast<std::size_t>(4),
                "total test count mismatch");

  Assert::equal(result.passed, static_cast<std::size_t>(2),
                "passed count mismatch");

  Assert::equal(result.failed, static_cast<std::size_t>(2),
                "failed count mismatch");

  return 0;
}
