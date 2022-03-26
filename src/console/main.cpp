#include <timber/timber>

namespace {
    constexpr auto finest_level = timber::level::trace;
    constexpr auto end = static_cast<int>(finest_level);
}

auto main(int argc, const char** argv) -> int {
    timber::log_handler = &timber::console_logger;

    for (auto i = 0; i <= end; ++i) {
        const auto level = static_cast<timber::level>(i);
        timber::log(level).write("Log message for testing");
    }
}
