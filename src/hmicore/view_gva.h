//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file view_gva.h
///

#ifndef HMICORE_VIEW_GVA_H_
#define HMICORE_VIEW_GVA_H_
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "hmicore/config_reader.h"
#include "hmicore/gva.h"
#include "hmicore/screen_gva.h"
#include "hmicore/touch_gva.h"

namespace gva {

struct ToggleInfo {
  /// Toggle visibility
  bool visible;
  /// Right toggle active
  bool right_active;
  /// Right toggle label
  std::string right_label;
  /// Left toggle active
  bool left_active;
  /// Left toggle label
  std::string left_label;
};

class LabelAction {
 public:
  ///
  /// \brief Bind a key to a callback
  ///
  /// \param fn
  ///
  void Bind(std::function<int(int parentId, GvaKeyEnum key)> fn) {
    privateCallback = std::bind(fn, std::placeholders::_1, std::placeholders::_2);
  }
  /// Toggle info
  ToggleInfo toggle_;
  /// Callback
  std::function<int(int parentId, GvaKeyEnum key)> privateCallback;  // Callback
};

class ViewGva {
 public:
  ///
  /// \brief Construct a new View Gva object
  ///
  /// \param function settings
  /// \param top label settings
  /// \param bottom label settings
  /// \param left label settings
  /// \param right label settings
  ///
  ViewGva(GvaFunctionEnum function, FunctionSelect *top, CommonTaskKeys *bottom, FunctionKeys left, FunctionKeys right)
      : function_(function), function_top_(top), common_bottom_(bottom), function_left_(left), function_right_(right) {}

  ///
  /// \brief Set the view as valid
  ///
  /// \return true if valid
  /// \return false if not valid
  ///
  bool Valid() const { return valid_; }

  ///
  /// \brief Release the view
  ///
  ///
  void Release() { valid_ = false; }

  ///
  /// \brief Get the Top attribute
  ///
  /// \return FunctionSelect*
  ///
  FunctionSelect *GetTop() { return function_top_; }

  ///
  /// \brief Get the Bottom attribute
  ///
  /// \return CommonTaskKeys*
  ///
  CommonTaskKeys *GetBottom() { return common_bottom_; }

  ///
  /// \brief Get the Left attribute
  ///
  /// \return FunctionKeys*
  ///
  FunctionKeys *GetLeft() { return &function_left_; }

  ///
  /// \brief Get the Right attribute
  ///
  /// \return FunctionKeys*
  ///
  FunctionKeys *GetRight() { return &function_right_; }

  ///
  /// \brief Get the Function attribute
  ///
  /// \return GvaFunctionEnum
  ///
  GvaFunctionEnum GetFunction() const { return function_; }

 private:
  /// Valid view
  bool valid_ = true;
  /// Function enumeration indicating active area
  GvaFunctionEnum function_;
  // Screen top
  FunctionSelect *function_top_;
  // Screen bottom
  CommonTaskKeys *common_bottom_;
  // Screen left
  FunctionKeys function_left_;
  /// Left label action
  std::array<LabelAction, 6> function_left_action_;
  // Screen right
  FunctionKeys function_right_;
  /// Right label action
  std::array<LabelAction, 6> function_right_action_;
};

class ViewGvaManager {
 public:
  ///
  /// \brief Construct a new View Gva Manager object
  ///
  ///
  ViewGvaManager();

  ///
  /// \brief Get the View Gva Manager object
  ///
  /// \param function
  /// \param top
  /// \param bottom
  /// \param left
  /// \param right
  ///
  void AddNewView(GvaFunctionEnum function, FunctionSelect *top, CommonTaskKeys *bottom, FunctionKeys left,
                  FunctionKeys right);

  ///
  /// \brief Set the Screen attribute
  ///
  /// \param screen info
  /// \param function area to set
  ///
  void SetScreen(Screen *screen, GvaFunctionEnum function) const;

  ///
  /// \brief Get the View attribute
  ///
  /// \param function
  /// \return ViewGva*
  ///
  ViewGva *GetView(GvaFunctionEnum function);

 private:
  /// View list
  std::vector<ViewGva> views_;
  /// The last view ID
  int idLast_ = 0;
  /// The current view ID
  int id_ = 0;
};

}  // namespace gva

#endif  // HMICORE_VIEW_GVA_H_
