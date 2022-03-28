#pragma once

#include <timber/timber.h>

#ifndef TIMBER_MAX_LEVEL
#define TIMBER_MAX_LEVEL trace
#endif

#define TIMBER_LOG(lvl, ...) \
    if (lvl > timber::level::TIMBER_MAX_LEVEL) ;\
    else if (lvl > timber::reporting_level) ;\
    else if (!timber::log_handler) ;\
    else timber::log(lvl).write(__VA_ARGS__);

#define TIMBER_EMERGENCY(...) \
    TIMBER_LOG(timber::level::emergency, __VA_ARGS__)

#define TIMBER_ALERT(...) \
    TIMBER_LOG(timber::level::alert, __VA_ARGS__)

#define TIMBER_CRITICAL(...) \
    TIMBER_LOG(timber::level::critical, __VA_ARGS__)

#define TIMBER_ERROR(...) \
    TIMBER_LOG(timber::level::error, __VA_ARGS__)

#define TIMBER_WARNING(...) \
    TIMBER_LOG(timber::level::warning, __VA_ARGS__)

#define TIMBER_NOTICE(...) \
    TIMBER_LOG(timber::level::notice, __VA_ARGS__)

#define TIMBER_INFO(...) \
    TIMBER_LOG(timber::level::info, __VA_ARGS__)

#define TIMBER_DEBUG(...) \
    TIMBER_LOG(timber::level::debug, __VA_ARGS__)

#define TIMBER_TRACE(...) \
    TIMBER_LOG(timber::level::trace, __VA_ARGS__)

#define TIMBER_CONCAT_INNER(a, b) a ## b
#define TIMBER_CONCAT(a, b) TIMBER_CONCAT_INNER(a, b)
#define TIMBER_VARNAME(base) TIMBER_CONCAT(base, __LINE__)

#ifdef TIMBER_TIMER_ACTIVE
#define TIMBER_TIMER(...) \
    const auto TIMBER_VARNAME(_timber_timer_) = timber::auto_timer(__VA_ARGS__)
#else
#define TIMBER_TIMER(...)
#endif

#define TIMBER_FUNC() \
    TIMBER_TIMER(timber::level::trace); \
    TIMBER_TRACE( \
        "{} started", \
        timber::source_location::current().function_name() \
    )
