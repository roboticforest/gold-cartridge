/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

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
