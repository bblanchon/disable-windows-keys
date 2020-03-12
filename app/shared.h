// Disable Windows Keys
// https://bblanchon.github.io/disable-windows-keys
// Copyright (C) 2020  Benoit Blanchon

#pragma once

#define MAIN_WINDOW_CLASS TEXT("{99724371-E3EF-4300-AC75-98E82B83370B}")

#define WM_KEYPRESS_INTERCEPTED (WM_USER + 0x0001)