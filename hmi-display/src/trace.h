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

#endif /* _TRACE_H */

#include <lttng/tracepoint-event.h>