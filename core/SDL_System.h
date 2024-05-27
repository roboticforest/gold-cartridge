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

        /**
         * Get the global SDL_System instance to perform global actions on the SDL library.
         * @return The global SDL_System singleton.
         */
        static SDL_System& instance();

        // Prevent copying.
        SDL_System(const SDL_System&) = delete;
        void operator=(const SDL_System&) = delete;

        bool startup();
        void shutdown();

    private:

        // Prevent manual instantiation.
        SDL_System();
        ~SDL_System();
    };

} // Core

#endif //GOLD_CARTRIDGE_SDL_SYSTEM_H
