#pragma once

#include "timber.h"

namespace timber::console {
    extern std::FILE* file;

    auto logger(const log& l) noexcept -> void;
}
