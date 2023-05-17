//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
/// \brief Manage the touch screen events
///
/// \file trace.h
///

#ifndef UPDATER_UPDATER_BASE_H_
#define UPDATER_UPDATER_BASE_H_

#include <string>

#include "hmicore/widgets/widget.h"

namespace gva {

class UpdaterBase {
 public:
  ///
  /// \brief Construct a new Updater object
  ///
  /// \param id The HMI identity, will only get updates for this ID.
  ///
  explicit UpdaterBase(uint64_t id) : id_(id) {}

  ///
  /// \brief Destroy the Updater Base object
  ///
  ///
  virtual ~UpdaterBase() = default;

  ///
  /// \brief Update the HMI state
  ///
  /// \param state The new state
  ///
  virtual void UpdateState(std::string state) = 0;

  ///
  /// \brief Process at HMI event
  ///
  /// \param event
  ///
  virtual void Event(std::string event) = 0;

 private:
  /// The updater unique identity
  uint64_t id_ = 0;
};

}  // namespace gva

#endif  // UPDATER_UPDATER_BASE_H_
