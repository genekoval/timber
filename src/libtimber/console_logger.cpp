#include <timber/timber.h>

#include <fmt/chrono.h>
#include <fmt/color.h>

namespace {
    constexpr auto timestamp_style = fmt::fg(fmt::color::dim_gray);

    auto level_style(timber::level level) -> fmt::text_style {
        auto color = fmt::color::white;

        switch (level) {
            case timber::level::emergency: color = fmt::color::dark_red; break;
            case timber::level::alert: color = fmt::color::crimson; break;
            case timber::level::critical: color = fmt::color::red; break;
            case timber::level::error: color = fmt::color::orange_red; break;
            case timber::level::warning: color = fmt::color::yellow; break;
            case timber::level::notice: color = fmt::color::lime_green; break;
            case timber::level::info: color = fmt::color::steel_blue; break;
            case timber::level::debug: color = fmt::color::plum; break;
            case timber::level::trace: color = fmt::color::blue_violet; break;
        }

        return fmt::fg(color);
    }
}

namespace timber {
    auto console_logger(const log& l) noexcept -> void {
        fmt::print(stderr, timestamp_style, "{:%b %d %r}", l.timestamp);
        fmt::print(stderr, level_style(l.log_level), " {:9} ", l.log_level);
        fmt::print(stderr, "{}\n", l.message);
    }
}
