#include "test_asserts.h"

#include "test_logging.h"

[[maybe_unused]] void assert_task(const std::function<bool()>& task,
                                  const std::optional<std::string>& start_message,
                                  const std::optional<std::string>& failure_message) {
    if (start_message) {
        log_status(*start_message);
    }
    if (!task()) {
        if (failure_message) {
            log_SDL2_error(*failure_message);
        }
        abort();
    }
}
