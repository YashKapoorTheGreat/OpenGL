#pragma once

#if defined(_MSC_VER)
// For MSVC (Visual Studio)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
// For GCC and Clang
#if defined(__x86_64__) || defined(__i386__)
// Inline assembly for Intel/AMD processors
#define DEBUG_BREAK() __asm__ volatile("int $3")
#else
// Built-in trap for other architectures (like ARM)
#define DEBUG_BREAK() __builtin_trap()
#endif
#endif
