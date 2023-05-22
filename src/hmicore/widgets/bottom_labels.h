//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file bottom_labels.h
///
#ifndef HMICORE_WIDGETS_BOTTOM_LABELS_H_
#define HMICORE_WIDGETS_BOTTOM_LABELS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/events_gva.h"
#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

/// Class defining the bottom labels widget
class WidgetBottomLabels : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object, this widget is interactive and requires the touch events
  ///
  /// \param renderer The underlying renderer, should be cairo
  /// \param touch the touch object
  ///
  explicit WidgetBottomLabels(const RendererGva& renderer, TouchGva* touch);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetBottomLabels() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetBottomLabels"; };

  ///
  /// \brief The base overloaded Draw fuctions to draw this widget type
  ///
  ///, TouchType& touch
  void Draw() final;

  ///
  /// \brief Set the Labels object
  ///
  /// \param labels
  ///
  void SetLabels(std::array<CommonTaskKeys::Labels, 8>* labels);

  ///
  /// \brief Enable a label
  ///
  /// \param key
  ///
  void EnableLabel(GvaKeyEnum key);

  ///
  /// \brief Disable a label
  ///
  /// \param key
  ///
  void DisableLabel(GvaKeyEnum key);

 private:
  void DrawControlLabels();
  ConfigData* config_ = nullptr;
  std::array<CommonTaskKeys::Labels, 8> labels_;
  TouchGva* touch_;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_BOTTOM_LABELS_H_
