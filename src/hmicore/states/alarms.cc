//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file alarms.cc
///

#include "alarms.h"

namespace gva {

GvaKeyEnum Hmi::KeyAlarms(GvaKeyEnum keypress) {
  auto *table = (WidgetTableDynamic *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:  // F1
      if (table->GetSorted() == WidgetTableDynamic::SortType::kSortDescending) {
        screen_.function_left.labels[0].text = "Sort.Ascending";
        table->SetSorted(WidgetTableDynamic::SortType::kSortAscending);
      } else {
        screen_.function_left.labels[0].text = "Sort.Descending";
        table->SetSorted(WidgetTableDynamic::SortType::kSortDescending);
      }
      return keypress;
      break;
    case GvaKeyEnum::kKeyF2:  // F2
      table->SetSorted(WidgetTableDynamic::SortType::kSortUnsorted);
      return keypress;
      break;
    case GvaKeyEnum::kKeyF3:  // F3
      if (table->GetHideOverride()) {
        screen_.function_left.labels[2].text = "Hide.Overridden";
        table->SetHideOverride(false);
      } else {
        screen_.function_left.labels[2].text = "Show.Overridden";
        table->SetHideOverride(true);
      }
      return keypress;
      break;
    case GvaKeyEnum::kKeyF4:  // F4
      if (table->GetAllHighlighted()) {
        table->SetAllHighlighted(false);
      } else {
        screen_.function_left.labels[2].text = "Hide.Overridden";
        table->SetAllHighlighted(true);
      }
      return keypress;
      break;
    case GvaKeyEnum::kKeyF17:  // Down Arrow
      table->SetPreviousRow();
      return keypress;
      break;
    case GvaKeyEnum::kKeyF18:  // Up Arrow
      table->SetNextRow();
      return keypress;
      break;
    default:  // Do nothing with other keys
      return GvaKeyEnum::kKeyUnknown;
      break;
  }
  return GvaKeyEnum::kKeyUnknown;
};

void StateAlarms::entry() {
  DLOG(INFO) << "Entering the DEF State";

  // Check to see if alarms was requested from hidden state, if so go back to last menu.
  if (screen_.control->labels_[1].state_ != LabelStates::kLabelHidden) {
    auto *table = (WidgetTableDynamic *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic);

    if (alarmson_) {
      alarmson_ = false;
      switch (lastState_) {
        case GvaFunctionEnum::kSituationalAwareness:
          transit<StateSA>();
          return;
        case GvaFunctionEnum::kWeapon:
          transit<StateWPN>();
          return;
        case GvaFunctionEnum::kDefensiveSystems:
          transit<StateDEF>();
          return;
        case GvaFunctionEnum::kSystems:
          transit<StateSYS>();
          return;
        case GvaFunctionEnum::kDriver:
          transit<StateDRV>();
          return;
        case GvaFunctionEnum::KSpecialToRole:
          transit<StateSTR>();
          return;
        case GvaFunctionEnum::kCommunications:
          transit<StateCOM>();
          return;
        case GvaFunctionEnum::kBattlefieldManagementSystem:
          transit<StateBMS>();
          return;
        default:
          return;  // Nothing more to do
      }
    }
    Reset();
    alarmson_ = true;
    manager_->SetScreen(&screen_, GvaFunctionEnum::kAlarmsX);
    table->SetVisible(true);

    // Update the controls
    screen_.control->ForceEnabledSelected(4);  // Up Arrow
    screen_.control->ForceEnabledSelected(5);  // Down Arrow
    screen_.control->ForceEnabledSelected(7);  // Enter
    screen_.control->ForceEnabledSelected(1);
  }
};

void StateAlarms::exit() {
  auto *table = (WidgetTableDynamic *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic);
  table->SetVisible(false);
}

void StateAlarms::react(EventKeySA const &) { transit<StateSA>(); };

void StateAlarms::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateAlarms::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateAlarms::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateAlarms::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateAlarms::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateAlarms::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateAlarms::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateAlarms::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateAlarms::react(EventKeyFunction const &e) {
  Key(e.key);
  KeyAlarms(e.key);
};

}  // namespace gva
