/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "test_application.h"

int main(int num_args, char** args) {
    (void) num_args; // Ignored.
    (void) args;     // Ignored.

    TestApplication app;
    app.run();

    return 0;
}