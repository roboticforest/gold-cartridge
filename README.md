# Project Gold Cartridge: SDL2 Starter Template

## Overview

Jump-start your Simple Direct-Media Layer projects with this foundational code base.

The aim of this project is to provide a simplified starting point for developers new to SDL2, or anyone that just wants to quickly test an idea without the hassle of setup and configuration.

### Features

- Initializes SDL2, SDL2\_image, and SDL2\_ttf.
- Cross-platform support (Linux, Windows).
- Provides a default window, renderer, and font.

### Quick Start

1. `git clone git@github.com:roboticforest/gold-cartridge.git`
2. Open in a C++ IDE with CMake support.
3. Build and run (you should the test application).
4. Edit `main.cpp` to your liking.

## Project Structure

This template repo is intended to get simple projects up and running in minutes or less. Basic SDL2 configuration and initialization are handled with placeholders marked out for your own code.

If you wish to do something more complex you are free to ignore any of the provided files or functions, or tweak them to better fit your needs.

### What's Provided

- `main.cpp` -- Program entry point. Check the comments for guide posts.

  SDL2 start-up occurs here and a simple game-loop is in place. Empty `input()`, `update()`, and `draw()` functions are provided for you to fill in with your own code.

  Most simple projects are expected to only ever need to edit this one file.

- `sdl2_loading.h` -- Handles SDL2 start-up and shutdown.

- `globals.h` -- **Semi-Optional** -- Holds variables for the default window, renderer, and font, plus other data for internal testing and debugging.

  Edit or ignore this file if you plan on doing something non-trivial with how SDL2 is initialized.

- `button.h & .cpp` -- **Optional** -- Provides a simple clickable button.

- `colors.h & .cpp` -- **Optional** -- Provides many predefined `SDL_Color` constants.

- `test_*` -- **Optional** -- Safe to ignore. Provides functions for testing, debugging, and logging SDL2's setup.

## Contribute

Open-source under MPL 2.0. See [issues](https://github.com/roboticforest/gold-cartridge/issues) for any open tasks.

## License

This software is provided under the Mozilla Public License Version 2.0 (MPL 2.0). See [LICENSE.txt](LICENSE.txt), or visit the [Mozilla Public License](https://mozilla.org/MPL/2.0/) website for full details. The following summary is ***not*** a substitute for the full license.

MPL 2.0 allows you to freely use, modify, and distribute this software, even for commercial projects. If you modify any part of this software, you must make those changes available under MPL 2.0. You're not required to open-source your entire project, just the modified files of the original software.

You must keep all copyright, patent, trademark, and attribution notices intact when you distribute or display any part of this software.

No warranties are provided, and the creators aren't liable for damages.

The license also grants you the right to use patents from contributors to the original software, but this doesn't extend to modified or combined software.
