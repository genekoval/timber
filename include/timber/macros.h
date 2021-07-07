#pragma once

#include <timber/timber.h>

#ifndef LOGGER_MAX_LEVEL
#define LOGGER_MAX_LEVEL timber::level::trace
#endif

#define LOG(level) \
    if (level > LOGGER_MAX_LEVEL) ;\
    else if (level > timber::reporting_level) ;\
    else timber::log(level).stream

#define EMERGENCY() \
    LOG(timber::level::emergency)

#define ALERT() \
    LOG(timber::level::alert)

#define CRITICAL() \
    LOG(timber::level::critical)

#define ERROR() \
    LOG(timber::level::error)

#define WARNING() \
    LOG(timber::level::warning)

#define NOTICE() \
    LOG(timber::level::notice)

#define INFO() \
    LOG(timber::level::info)

#define DEBUG() \
    LOG(timber::level::debug)

#define TRACE() \
    LOG(timber::level::trace)
