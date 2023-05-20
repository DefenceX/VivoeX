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

#ifndef HMICORE_TRACE_H_
#define HMICORE_TRACE_H_

#undef TRACEPOINT_PROVIDER
/// Define the tracepoint provider
#define TRACEPOINT_PROVIDER vivoe_lite

#undef TRACEPOINT_INCLUDE
/// Define the tracepoint include
#define TRACEPOINT_INCLUDE "src/trace.h"

#if !defined(_TRACE_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TRACE_H

#include <lttng/tracepoint.h>

/// Tracepoint for the main function
TRACEPOINT_EVENT(vivoe_lite, main, TP_ARGS(int, my_integer_arg, char*, my_string_arg),
                 TP_FIELDS(ctf_string(my_string_field, my_string_arg)
                               ctf_integer(int, my_integer_field, my_integer_arg)))
/// Tracepoint for the app callback
TRACEPOINT_EVENT(vivoe_lite, app_callback, TP_ARGS(int, counter),
                 TP_FIELDS(ctf_integer(int, my_integer_field, counter)))

#endif  // _TRACE_H

#include <lttng/tracepoint-event.h>

#endif  // HMICORE_TRACE_H_
