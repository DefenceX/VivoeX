///
/// MIT License
///
/// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
/// associated documentation files (the 'Software'), to deal in the Software without restriction,
/// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial
/// portions of the Software.
/// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
/// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
/// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
/// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief HMI Manager
///
/// \file hmi_gva.h
///

#ifndef HMI_DISPLAY_SRC_HMI_GVA_H_
#define HMI_DISPLAY_SRC_HMI_GVA_H_
#include <iostream>
#include <string>

#include "src/config_reader.h"
#include "src/gva.h"
#include "src/hmi_gva_defaults.h"
#include "src/hmi_gva_helpers.h"
#include "src/renderer_map.h"
#include "src/screen_gva.h"
#include "src/states/alarms.h"
#include "src/states/base_hmi.h"
#include "src/states/bms.h"
#include "src/states/com.h"
#include "src/states/def.h"
#include "src/states/drv.h"
#include "src/states/off.h"
#include "src/states/on.h"
#include "src/states/sa.h"
#include "src/states/str.h"
#include "src/states/sys.h"
#include "src/states/wpn.h"
#include "src/view_gva.h"

namespace gva {

//
// forward declarations
//
// struct StateOff;
// struct StateSA;
// struct StateWPN;
// struct StateDEF;
// struct StateDRV;
// struct StateSYS;
// struct StateSTR;
// struct StateCOM;
// struct StateBMS;
// struct StateAlarms;

using hmi = Hmi;

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_HMI_GVA_H_
