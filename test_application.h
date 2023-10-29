/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GOLD_CARTRIDGE_TEST_APPLICATION_H
#define GOLD_CARTRIDGE_TEST_APPLICATION_H

#include "button.h"

#include <memory>

class TestApplication {
  public:
    TestApplication();
    ~TestApplication() = default;

    int run();

  private:
    void input();
    void update();
    void draw();

    // SDL2 Test Buttons
    std::unique_ptr<Button> test_button;
    std::unique_ptr<Button> test_button_2;
    std::function<void()> button_action;
};

#endif //GOLD_CARTRIDGE_TEST_APPLICATION_H
