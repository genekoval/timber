#include <timber/timber>

namespace {
    constexpr auto finest_level = timber::level::trace;
    constexpr auto end = static_cast<int>(finest_level);

    auto newline() -> void {
        fmt::print("\n");
    }

    auto print_logs() -> void {
        for (auto i = 0; i <= end; ++i) {
            const auto level = static_cast<timber::level>(i);
            timber::log(level).write("Log message for testing");
        }
    }
}

auto main(int argc, char** argv) -> int {
    timber::log_handler = &timber::console::logger;

    print_logs();

    timber::thread_name = "main";
    newline();

    print_logs();
}
