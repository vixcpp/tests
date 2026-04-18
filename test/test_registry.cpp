/**
 *
 *  @file test_registry.cpp
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

#include <vix/tests/TestRegistry.hpp>
#include <vix/tests/TestCase.hpp>
#include <vix/tests/TestSuite.hpp>
#include <vix/tests/Assert.hpp>

int main()
{
  using namespace vix::tests;

  auto &registry = TestRegistry::instance();

  // Ensure clean state
  registry.clear();

  // Add single test
  registry.add(TestCase("registry single test", []
                        { Assert::is_true(true); }));

  Assert::equal(registry.tests().size(), static_cast<std::size_t>(1),
                "registry should contain 1 test");

  // Add suite
  TestSuite suite("registry suite");

  suite.add(TestCase("suite test 1", []
                     { Assert::is_true(true); }));

  suite.add(TestCase("suite test 2", []
                     { Assert::is_true(true); }));

  registry.add(std::move(suite));

  Assert::equal(registry.suites().size(), static_cast<std::size_t>(1),
                "registry should contain 1 suite");

  Assert::equal(registry.total_tests(), static_cast<std::size_t>(3),
                "registry total test count mismatch");

  return 0;
}
