#pragma once

// Detect used platform
#if defined(_WIN32) || defined(_WIN64)
#   define PLATFORM_WINDOWS 1
#else
#   define PLATFORM_LINUX 1
#endif


// Include platform specific elements.
#if PLATFORM_WINDOWS
#   include "platformWindows.h"
#elif PLATFORM_LINUX
#   include "platformLinux.h"
#endif
