/**
 *
 *  @file test_assert.cpp
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

#include <vix/tests/Assert.hpp>

int main()
{
  using namespace vix::tests;

  // --- Passing assertions ---
  Assert::is_true(true);
  Assert::is_false(false);
  Assert::equal(10, 10);
  Assert::not_equal(10, 20);

  // --- Expected failures (caught manually) ---
  bool caught = false;

  try
  {
    Assert::is_true(false);
  }
  catch (const AssertionError &)
  {
    caught = true;
  }

  Assert::is_true(caught, "is_true should throw on false");

  caught = false;

  try
  {
    Assert::equal(1, 2);
  }
  catch (const AssertionError &)
  {
    caught = true;
  }

  Assert::is_true(caught, "equal should throw on mismatch");

  caught = false;

  try
  {
    Assert::fail("forced failure");
  }
  catch (const AssertionError &)
  {
    caught = true;
  }

  Assert::is_true(caught, "fail should always throw");

  return 0;
}
