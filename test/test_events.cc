//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file test_events.cc
///

#include <unistd.h>

#include <iostream>

#include "events_gva.h"
#include "gva.h"
#include "hmi_gva.h"

using namespace gva;

static EventsGva *events = 0;

TEST_F("eventsGva Constructor1", "Constructor test") {
  events = new EventsGva(hmi::GetRendrer()->GetWindow(), hmi::GetRendrer()->GetTouch());

  REQUIRE(events != 0);
}

TEST_F("eventsGva", "flush") {
  //  events->flush();

  REQUIRE(events != 0);
  free(events);
}

TEST_F("eventsGva Constructor2", "Constructor test2") {
  // instantiate events
  EventKeyPowerOn on;

  hmi::start();
  hmi::dispatch(on);

  EventsGva io(hmi::GetRendrer()->GetWindow(), hmi::GetRendrer()->GetTouch());

  REQUIRE(hmi::GetRendrer()->GetWindow() != 0);
  REQUIRE(events != 0);
}
