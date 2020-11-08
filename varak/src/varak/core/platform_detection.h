#pragma once

// for now only support 64-bit windows

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #ifdef _WIN64
        #define VR_PLATFORM_WINDOWS
    #else
        #error "Varak does not support 32-bit Windows!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define VR_PLATFORM_IOS
        #error "Varak does not support IOS simulator!"
    #elif TARGET_OS_IPHONE == 1
        #define VR_PLATFORM_IOS
        #error "Varak does not support IOS!"
    #elif TARGET_OS_MAC == 1
        #define VR_PLATFORM_MACOS
        #error "Varak does not support MacOS!"
    #else
        #error "Unknown Apple platform!"
    #endif
#elif defined(__ANDROID__)
    #define VR_PLATFORM_ANDROID
    #error "Varak does not support Android!"
#elif defined(__linux__)
    #define VR_PLATFORM_LINUX
    #error "Varak does not support Linux!"
#else
    #error "Unknown platform!"
#endif
