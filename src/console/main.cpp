#include <timber/timber>

namespace {
    constexpr auto finest_level = timber::level::trace;
    constexpr auto end = static_cast<int>(finest_level);
}

auto main(int argc, char** argv) -> int {
    timber::thread_name = "main";
    timber::log_handler = &timber::console::logger;

    for (auto i = 0; i <= end; ++i) {
        const auto level = static_cast<timber::level>(i);
        timber::log(level).write("Log message for testing");
    }
}
