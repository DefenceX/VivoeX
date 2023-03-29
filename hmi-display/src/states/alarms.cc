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
//
///
/// \file alarms.cc
///

#include "alarms.h"

#include "src/hmi_gva.h"
#include "src/states/states.h"

namespace gva {

GvaKeyEnum Hmi::KeyAlarms(GvaKeyEnum keypress) {
  auto *table = (WidgetTableDynamic *)HmiState::GetInstance().screen_render_->GetWidget(
      widget::WidgetEnum::KWidgetTypeTableDynamic);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:  // F1
      if (table->GetSorted() == WidgetTableDynamic::SortType::kSortDescending) {
        HmiState::GetInstance().screen_.function_left.labels[0].text = "Sort.Ascending";
        table->SetSorted(WidgetTableDynamic::SortType::kSortAscending);
      } else {
        HmiState::GetInstance().screen_.function_left.labels[0].text = "Sort.Descending";
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
        HmiState::GetInstance().screen_.function_left.labels[2].text = "Hide.Overridden";
        table->SetHideOverride(false);
      } else {
        HmiState::GetInstance().screen_.function_left.labels[2].text = "Show.Overridden";
        table->SetHideOverride(true);
      }
      return keypress;
      break;
    case GvaKeyEnum::kKeyF4:  // F4
      if (table->GetAllHighlighted()) {
        table->SetAllHighlighted(false);
      } else {
        HmiState::GetInstance().screen_.function_left.labels[2].text = "Hide.Overridden";
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
  // Check to see if alarms was requested from hidden state, if so go back to last menu.
  if (HmiState::GetInstance().screen_.control->labels_[1].state_ != LabelStates::kLabelHidden) {
    auto *table = (WidgetTableDynamic *)HmiState::GetInstance().screen_render_->GetWidget(
        widget::WidgetEnum::KWidgetTypeTableDynamic);

    if (HmiState::GetInstance().alarmson_) {
      HmiState::GetInstance().alarmson_ = false;
      switch (HmiState::GetInstance().lastState_) {
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
    HmiState::GetInstance().ResetHmi();
    HmiState::GetInstance().alarmson_ = true;
    HmiState::GetInstance().manager_->SetScreen(&HmiState::GetInstance().screen_, GvaFunctionEnum::kAlarmsX);
    table->SetVisible(true);

    // Update the controls
    HmiState::GetInstance().screen_.control->ForceEnabledSelected(4);  // Up Arrow
    HmiState::GetInstance().screen_.control->ForceEnabledSelected(5);  // Down Arrow
    HmiState::GetInstance().screen_.control->ForceEnabledSelected(7);  // Enter
    HmiState::GetInstance().screen_.control->ForceEnabledSelected(1);
  }
};

void StateAlarms::exit() {
  auto *table = (WidgetTableDynamic *)HmiState::GetInstance().screen_render_->GetWidget(
      widget::WidgetEnum::KWidgetTypeTableDynamic);
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
  HmiState::GetInstance().Key(e.key);
  KeyAlarms(e.key);
};

}  // namespace gva
