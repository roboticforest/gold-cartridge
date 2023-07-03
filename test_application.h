/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GOLD_CARTRIDGE_TEST_APPLICATION_H
#define GOLD_CARTRIDGE_TEST_APPLICATION_H

class TestApplication {
  public:
    TestApplication() = default;
    ~TestApplication() = default;

    int run();

  private:
    void input();
    void update();
    void draw();
};

#endif //GOLD_CARTRIDGE_TEST_APPLICATION_H
