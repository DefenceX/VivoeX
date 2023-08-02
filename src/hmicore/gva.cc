//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file gva.cc
///

#include "gva.h"

namespace gva {

    hmiScreenSize& hmiScreenSize::getInstance() {
        static hmiScreenSize instance;
        return instance;
    }

    std::tuple<int, int> hmiScreenSize::getMinimumSize() const {
        return minimumSize;
    }

    void hmiScreenSize::setMinimumSize(int width, int height) {
        minimumSize = std::make_tuple(width, height);
    }

    hmiScreenSize::hmiScreenSize() {
        minimumSize = std::make_tuple(640, 480);
    }

}