/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GOLD_CARTRIDGE_TEST_ASSERTS_H
#define GOLD_CARTRIDGE_TEST_ASSERTS_H

#include <functional>
#include <optional>
#include <string>

/**
 * Assert that a given task has completed successfully, otherwise terminate the application.
 * @param task A boolean function performing a desired task and returning true if the task was successfully completed.
 * @param start_message An optional logged description of the task about to be performed.
 * @param failure_message An optional message to log if the task failed.
 */
[[maybe_unused]] void assert_task(const std::function<bool()>& task,
                                  const std::optional<std::string>& start_message,
                                  const std::optional<std::string>& failure_message);

#endif //GOLD_CARTRIDGE_TEST_ASSERTS_H