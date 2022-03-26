#pragma once

#include <timber/timber.h>

#ifndef LOGGER_MAX_LEVEL
#define LOGGER_MAX_LEVEL timber::level::trace
#endif

#define TIMBER_LOG(level, ...) \
    if (level > LOGGER_MAX_LEVEL) ;\
    else if (level > timber::reporting_level) ;\
    else if (!timber::log_handler) ;\
    else timber::log(level).write(__VA_ARGS__);

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
