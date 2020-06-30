#pragma once

#include <timber/timber.h>

#ifndef LOGGER_MAX_LEVEL
#define LOGGER_MAX_LEVEL timber::level::trace
#endif

#define LOG(level) \
    if (level > LOGGER_MAX_LEVEL) ;\
    else if (level > timber::reporting_level()) ;\
    else timber::log(level).stream

#define ERROR() \
    LOG(timber::level::error)

#define WARN() \
    LOG(timber::level::warn)

#define INFO() \
    LOG(timber::level::info)

#define DEBUG() \
    LOG(timber::level::debug)

#define TRACE() \
    LOG(timber::level::trace)
