# C Custom Memory Allocator

A custom memory allocator written in C that manages a fixed-size heap
inside the process. It provides `malloc`/`free`/`realloc`-style functions and
supports:

First-fit allocation strategy
Block splitting when a free block is larger than requested
Coalescing of adjacent free blocks on `free`
8-byte alignment of allocations
A `my_heap_dump()` helper for visualizing the heap layout

This project is meant as a learning / portfolio piece to understand how allocators works.

## Project Structure

c-custom-allocator/
- src/
- - allocator.c    # Implementation of the custom allocator
- - main.c         # Simple test harness / demo
- include/
- - allocator.h    # Public API (my_malloc, my_free, my_realloc, etc.)
- Makefile          # Build script
- README.md
