#include <timber/macros.h>

#include <cxxabi.h>

namespace {
    namespace internal {
        timber::level terminate_level;

        auto demangling_error(int status) -> std::string_view {
            switch (status) {
                case -1: return "memory allocation failure";
                case -2: return "name not valid under C++ ABI mangling rules";
                case -3: return "invalid argument to demangling function";
                default: return "unknown";
            }
        }

        auto log_exception(const std::exception& ex) noexcept -> void {
            const auto name = typeid(ex).name();

            auto status = 0;
            auto* realname =
                abi::__cxa_demangle(name, nullptr, nullptr, &status);

            if (status == 0) {
                TIMBER_LOG(
                    terminate_level,
                    "terminate called after throwing an instance of '{}': {}",
                    realname,
                    ex.what()
                );
            }
            else {
                TIMBER_LOG(
                    terminate_level,
                    "terminate called after throwing an instance of '{}' "
                    "(demangling failed: {}): {}",
                    name,
                    demangling_error(status),
                    ex.what()
                );
            }

            free(realname);
        }

        auto handler() noexcept -> void {
            const auto exception = std::current_exception();

            if (!exception) {
                TIMBER_LOG(
                    terminate_level,
                    "terminate called without an active exception"
                );
                return;
            }

            try {
                std::rethrow_exception(exception);
            }
            catch (const std::exception& ex) {
                log_exception(ex);
            }
            catch (...) {
                TIMBER_LOG(
                    terminate_level,
                    "terminate called after throwing an object of unknown type"
                );
            }
        }
    }
}

namespace timber {
    auto set_terminate(level log_level) noexcept -> void {
        internal::terminate_level = log_level;
        std::set_terminate(internal::handler);
    }
}
