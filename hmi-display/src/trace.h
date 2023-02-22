//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
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
/// \brief Manage the touch screen events
///
/// \file trace.h
///

#ifndef HMI_DISPLAY_SRC_TRACE_H_
#define HMI_DISPLAY_SRC_TRACE_H_

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER vivoe_lite

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "src/trace.h"

#if !defined(_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TRACE_H

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(vivoe_lite, main, TP_ARGS(int, my_integer_arg, char*, my_string_arg),
                 TP_FIELDS(ctf_string(my_string_field, my_string_arg)
                               ctf_integer(int, my_integer_field, my_integer_arg)))

TRACEPOINT_EVENT(vivoe_lite, app_callback, TP_ARGS(int, counter),
                 TP_FIELDS(ctf_integer(int, my_integer_field, counter)))

#endif  // _TRACE_H

#include <lttng/tracepoint-event.h>

#endif  // HMI_DISPLAY_SRC_TRACE_H_
