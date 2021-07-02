#pragma once

#include <filesystem>

#include "log.h"

#ifdef VR_DEBUG
    #if defined(__has_builtin) && !defined(__ibmxl__)
        #if __has_builtin(__builtin_debugtrap)
            #define VR_DEBUGBREAK() __builtin_debugtrap()
        #elif __has_builtin(__debugbreak)
            #define VR_DEBUGBREAK() __debugbreak()
        #endif
    #endif
    #if !defined(VR_DEBUGBREAK)
        #if defined(_MSC_VER) || defined(__INTEL_COMPILER)
            #define VR_DEBUGBREAK() __debugbreak()
        #elif defined(__ARMCC_VERSION)
            #define VR_DEBUGBREAK() __breakpoint(42)
        #elif defined(__ibmxl__) || defined(__xlC__)
            #include <builtins.h>
            #define VR_DEBUGBREAK() __trap(42)
        #elif defined(__DMC__) && defined(_M_IX86)
static inline void VR_DEBUGBREAK(void)
{
    __asm int 3h;
}
        #elif defined(__i386__) || defined(__x86_64__)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__("int3");
}
        #elif defined(__thumb__)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__(".inst 0xde01");
}
        #elif defined(__aarch64__)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__(".inst 0xd4200000");
}
        #elif defined(__arm__)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__(".inst 0xe7f001f0");
}
        #elif defined(__alpha__) && !defined(__osf__)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__("bpt");
}
        #elif defined(_54_)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__("ESTOP");
}
        #elif defined(_55_)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP");
}
        #elif defined(_64P_)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__("SWBP 0");
}
        #elif defined(_6x_)
static inline void VR_DEBUGBREAK(void)
{
    __asm__ __volatile__("NOP\n .word 0x10000000");
}
        #elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
            #define VR_DEBUGBREAK() __builtin_trap()
        #else
            #include <signal.h>
            #if defined(SIGTRAP)
                #define VR_DEBUGBREAK() raise(SIGTRAP)
            #else
                #define VR_DEBUGBREAK() raise(SIGABRT)
            #endif
        #endif
    #endif

    // VR_ASSERT will only have the expression, while VR_ASSERT_MSG will have
    // both the expression and a message. Core and app will have different
    // assertion macros.
    #define VR_INTERNAL_ASSERT(type, expr, ...)                                                    \
        if (!(expr))                                                                               \
        VR##type##ERROR(__VA_ARGS__), VR_DEBUGBREAK()

    #define VR_INTERNAL_ASSERT_MSG(type, expr, msg, ...)                                           \
        VR_INTERNAL_ASSERT(type, expr, "Assertion failed: " msg, ##__VA_ARGS__)

    #define VR_INTERNAL_ASSERT_NO_MSG(type, expr)                                                  \
        VR_INTERNAL_ASSERT(type, expr, "Assertion '{0}' failed at: {1}:{2}", #expr,                \
                           std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define VR_CORE_ASSERT(expr) VR_INTERNAL_ASSERT_NO_MSG(_CORE_, expr)
    #define VR_CORE_ASSERT_MSG(expr, msg, ...)                                                     \
        VR_INTERNAL_ASSERT_MSG(_CORE_, expr, msg, ##__VA_ARGS__)

    #define VR_ASSERT(expr) VR_INTERNAL_ASSERT_NO_MSG(_, expr)
    #define VR_ASSERT_MSG(expr, msg, ...) VR_INTERNAL_ASSERT_MSG(_, expr, msg, ##__VA_ARGS__)

#else
    #define VR_CORE_ASSERT(expr)
    #define VR_CORE_ASSERT_MSG(expr, ...)

    #define VR_ASSERT(expr)
    #define VR_ASSERT_MSG(expr, ...)

    #define VR_DEBUGBREAK()
#endif

// These asserts will not be removed from release builds
// TODO: make this use a popup error message box
#define VR_INTERNAL_ASSERT_RELEASE(type, expr, msg, ...)                                           \
    if (!(expr))                                                                                   \
    VR##type##ERROR("ERROR: " msg, ##__VA_ARGS__), exit(-1)

#define VR_CORE_ASSERT_RELEASE(expr, msg, ...)                                                     \
    VR_INTERNAL_ASSERT_RELEASE(_CORE_, expr, msg, ##__VA_ARGS__)

#define VR_ASSERT_RELEASE(expr, msg, ...) VR_INTERNAL_ASSERT_RELEASE(_, expr, msg, ##__VA_ARGS__)
