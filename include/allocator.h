#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

#define HEAP_SIZE (1024 * 1024)  // 1 MB heap size

void my_allocator_init(void);
void* my_malloc(size_t size);
void my_free(void* ptr);
void* my_realloc(void* ptr, size_t size);
void my_heap_dump(void);

#endif // ALLOCATOR_H
