//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file sa.h
///
#ifndef HMICORE_STATES_SA_H_
#define HMICORE_STATES_SA_H_

#include <iostream>

#include "hmicore/gva.h"
#include "hmicore/hmi_gva.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/view_gva.h"
#include "hmicore/widgets/ai/object_localisation.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/plan_position_indicator.h"

namespace gva {

/// The SA state
struct StateSA : Hmi {
  void entry() override;
  void exit() override;
  void react(EventKeyPowerOn const &) override;
  void react(EventKeySA const &) override;
  void react(EventKeyWPN const &) override;
  void react(EventKeyDEF const &) override;
  void react(EventKeySYS const &) override;
  void react(EventKeyDRV const &) override;
  void react(EventKeySTR const &) override;
  void react(EventKeyCOM const &) override;
  void react(EventKeyBMS const &) override;
  void react(EventKeyAlarms const &) override;
  void react(EventKeyFunction const &e) override;

 private:
  GvaKeyEnum current_selection_ = GvaKeyEnum::kKeyF5;
  gva::WidgetVideo *video_ = nullptr;
};

}  // namespace gva

#endif  // HMICORE_STATES_SA_H_
