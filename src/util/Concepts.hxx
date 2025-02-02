// SPDX-License-Identifier: BSD-2-Clause
// author: Max Kellermann <max.kellermann@gmail.com>

#pragma once

#include <concepts>

/**
 * Compatibility wrapper for std::invocable which is unavailable in
 * Apple Xcode.
 */
#if !defined(__APPLE__) && (!defined __clang__ || __clang_major__ >=14)
template<typename F, typename... Args>
concept Invocable = std::invocable<F, Args...>;
#else
template<typename F, typename... Args>
concept Invocable = requires(F f, Args... args) {
	{ f(args...) };
};
#endif

/**
 * Compatibility wrapper for std::predicate which is unavailable in
 * Apple Xcode.
 */
#if !defined(__APPLE__) && (!defined __clang__ || __clang_major__ >=14)
template<typename F, typename... Args>
concept Predicate = std::predicate<F, Args...>;
#else
template<typename F, typename... Args>
concept Predicate = requires(F f, Args... args) {
	{ f(args...) } -> std::same_as<bool>;
};
#endif

template<typename F, typename T>
concept Disposer = Invocable<F, T *>;
