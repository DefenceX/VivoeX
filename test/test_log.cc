//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the 'Software'), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief Tests for logger
///
/// \file test_log.cc
///

#define CATCH_CONFIG_MAIN
#include <unistd.h>

#include <catch/catch.hpp>
#include <iostream>
#include <string>

#include "events_gva.h"
#include "gva.h"
#include "log_gva.h"

using namespace gva;

static EventsGva *events;

TEST_CASE("Log", "Logging tests") {
  std::string test1 = "This is a string test";
  char test2[] = "This is a char* test";
  //  logGva::log(test1, LOG_INFO);
  logGva::log(test2, LOG_INFO);
  logGva::log(test2, LOG_DEBUG);
  logGva::log(test2, LOG_ERROR);
  logGva::log(test2, LOG_WARNING);
  logGva::finish();

  REQUIRE(0 == 0);
}
