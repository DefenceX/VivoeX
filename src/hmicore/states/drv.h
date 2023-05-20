//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file drv.h
///
#ifndef HMICORE_STATES_DRV_H_
#define HMICORE_STATES_DRV_H_

#include <glog/logging.h>

#include <iostream>

#include "hmicore/gva.h"
#include "hmicore/hmi_gva.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/view_gva.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/canvas/canvas.h"
#include "hmicore/widgets/plan_position_indicator.h"

namespace gva {

/// Class definition of the StateDRV
struct StateDRV : Hmi {
  ///
  /// \brief Construct a new State DRV object
  ///
  ///
  StateDRV();

  ///
  /// \brief Update the video
  ///
  ///
  void UpdateVideo();

  ///
  /// \brief Entry into the state
  ///
  ///
  void entry() override;

  ///
  /// \brief Exit from the state
  ///
  ///
  void exit() override;

  ///
  /// \brief React to an event
  ///
  ///
  void react(EventKeyPowerOn const &) override;

  ///
  /// \brief React to an SA change event
  ///
  ///
  void react(EventKeySA const &) override;

  ///
  /// \brief React to a WPN change event
  ///
  ///
  void react(EventKeyWPN const &) override;

  ///
  /// \brief React to a DRV change event
  ///
  ///
  void react(EventKeyDEF const &) override;

  ///
  /// \brief React to a SYS change event
  ///
  ///
  void react(EventKeySYS const &) override;

  ///
  /// \brief React to a DRV change event
  ///
  ///
  void react(EventKeyDRV const &) override;

  ///
  /// \brief React to a COM change event
  ///
  ///
  void react(EventKeySTR const &) override;

  ///
  /// \brief React to a COM change event
  ///
  ///
  void react(EventKeyCOM const &) override;

  ///
  /// \brief React to a COM change event
  ///
  ///
  void react(EventKeyBMS const &) override;

  ///
  /// \brief React to a COM change event
  ///
  ///
  void react(EventKeyAlarms const &) override;

  ///
  /// \brief React to a COM change event
  ///
  /// \param e the event
  ///
  void react(EventKeyFunction const &e) override;

 private:
  /// The video widget
  gva::WidgetVideo *video_ = nullptr;
};

}  // namespace gva

#endif  // HMICORE_STATES_DRV_H_
