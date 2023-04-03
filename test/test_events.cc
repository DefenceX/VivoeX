//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
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
//
///
/// \file test_events.cc
///

#include <unistd.h>

#include <iostream>

#include "gtest/gtest.h"
#include "src/events_gva.h"
#include "src/gva.h"
#include "src/hmi_gva.h"

namespace {

static gva::EventsGva *events = 0;

TEST(Events, ConstructorTest) {
  events = new gva::EventsGva(gva::hmi::GetRendrer()->GetWindow(), gva::hmi::GetRendrer()->GetTouch());

  EXPECT_EQ(events, nullptr);
}

TEST(Events, Flush) {
  //  events->flush();

  EXPECT_EQ(events, nullptr);
  free(events);
}

TEST(Events, ConctructorTest2) {
  // instantiate events
  gva::EventKeyPowerOn on;

  gva::hmi::start();
  gva::hmi::dispatch(on);

  gva::EventsGva io(gva::hmi::GetRendrer()->GetWindow(), gva::hmi::GetRendrer()->GetTouch());

  EXPECT_EQ(gva::hmi::GetRendrer()->GetWindow(), nullptr);
  EXPECT_EQ(events, nullptr);
}

}  // namespace
