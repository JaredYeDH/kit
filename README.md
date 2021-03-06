# kit
My personal C++11 toolset

Open-source under MIT License

Copyright (c) 2013 Grady O'Connell

## async
- Stackful coroutines
- Per-thread event loops
- Coroutine-friendly YIELD(), AWAIT(), and SLEEP()
- Transfer tasks between threads
- Thread-safe channels
- Async fstream alternative (WIP)

## reactive
signals, reactive values (signal-paired vars), and lazy evaluation

## meta
Thread-aware serializable meta-objects, property trees, and reflection

## freq
Timelines, alarms, animation/easing, waypoints/keyframes, interpolation

## log
Logger w/ error handling, thread-safe scoped indent, silencing, and capturing

## math
some math stuff to use with glm

## common (kit.h)
Common stuff used by other modules, including:

- freezable: freeze objects as immutable
- make_unique: clone of c++14 function
- dummy_mutex
- ENTIRE() range macro
- bit() and mask()
- null_ptr_exception
- scoped_unlock
- thread-safe singleton
- timed function auto-retry
- index data structures w/ unused ID approximation

