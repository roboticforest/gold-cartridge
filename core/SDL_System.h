/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2024 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GOLD_CARTRIDGE_SDL_SYSTEM_H
#define GOLD_CARTRIDGE_SDL_SYSTEM_H

namespace Core {

    class SDL_System {
    public:
        static bool is_initialized();
        static bool start_up();
        static void shut_down();

        SDL_System(const SDL_System&) = delete;
        void operator=(const SDL_System&) = delete;

    private:
        SDL_System();
        ~SDL_System();

    private:
        static bool m_library_initialized;
    };

} // Core

#endif //GOLD_CARTRIDGE_SDL_SYSTEM_H
