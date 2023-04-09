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
///
/// \file hmi_gva.h
///

#ifndef HMICORE_HMI_GVA_H_
#define HMICORE_HMI_GVA_H_
#include <iostream>
#include <string>

#include "hmicore/config_reader.h"
#include "hmicore/gva.h"
#include "hmicore/hmi_gva_defaults.h"
#include "hmicore/hmi_gva_helpers.h"
#include "hmicore/renderer_map.h"
#include "hmicore/screen_gva.h"
#include "hmicore/states/alarms.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/states/bms.h"
#include "hmicore/states/com.h"
#include "hmicore/states/def.h"
#include "hmicore/states/drv.h"
#include "hmicore/states/off.h"
#include "hmicore/states/on.h"
#include "hmicore/states/sa.h"
#include "hmicore/states/str.h"
#include "hmicore/states/sys.h"
#include "hmicore/states/wpn.h"
#include "hmicore/view_gva.h"

namespace gva {

using hmi = Hmi;

}  // namespace gva

#endif  // HMICORE_HMI_GVA_H_
