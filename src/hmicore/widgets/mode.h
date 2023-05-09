//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file mode.h
///

#ifndef HMICORE_WIDGETS_MODE_H_
#define HMICORE_WIDGETS_MODE_H_

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

class WidgetMode : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object
  ///
  /// \param renderer
  ///
  explicit WidgetMode(const RendererGva& renderer);

  ///
  /// \brief Destroy the Widget mode object
  ///
  ///
  ~WidgetMode() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetMode"; };

  ///
  /// \brief Draw the current widget
  ///
  ///
  void Draw() final;

  ///
  /// \brief Set the Mode object
  ///
  /// \param mode
  ///
  void SetMode(const std::string mode);

  /// KWidgetTypeMode
  ///  \brief Get the Mode object
  ///
  ///  \return std::string
  ///
  std::string GetMode() const;

 private:
  std::string mode_ = "Maintenance Mode";
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_MODE_H_
