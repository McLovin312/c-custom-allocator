#include "allocator.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct BlockHeader {
    size_t size;               // Size of the payload in bytes
    bool free;                 // 1 if free, 0 if allocated
    struct BlockHeader* next;  // Next block in the list
} BlockHeader;

static unsigned char heap[HEAP_SIZE];
static BlockHeader* free_list = NULL;

// Align size up to the nearest multiple of 8
static size_t align8(size_t size) {
    return (size + 7) & ~((size_t)7);
}

void my_allocator_init(void) {
    free_list = (BlockHeader*)heap;
    free_list->size = HEAP_SIZE - sizeof(BlockHeader);
    free_list->free = true;
    free_list->next = NULL;
}

void* my_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    size = align8(size);

    BlockHeader* current = free_list;
    while (current) {
        if (current->free && current->size >= size) {
            size_t remaining = current->size - size;

            // Only split if there's enough space for a new header + some payload
            if (remaining >= sizeof(BlockHeader) + 8) {
                BlockHeader* new_block = (BlockHeader*)((unsigned char*)current
                                                        + sizeof(BlockHeader)
                                                        + size);
                new_block->size = remaining - sizeof(BlockHeader);
                new_block->free = true;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }

            current->free = false;
            return (unsigned char*)current + sizeof(BlockHeader);
        }
        current = current->next;
    }
    return NULL; // No suitable block found
}

void my_free(void* ptr) {
    if (!ptr) return;

    BlockHeader* block = (BlockHeader*)((unsigned char*)ptr - sizeof(BlockHeader));
    block->free = true;

    BlockHeader* current = free_list;
    while (current) {
        if (current->free && current->next && current->next->free) {
            current->size += sizeof(BlockHeader) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void* my_realloc(void* ptr, size_t new_size) {

    if (ptr == NULL) {
        return my_malloc(new_size);
    }

    if (new_size == 0) {
        my_free(ptr);
        return NULL;
    }

    new_size = align8(new_size);

    // Get the block header for this allocation
    BlockHeader* block = (BlockHeader*)((unsigned char*)ptr - sizeof(BlockHeader));

    // If the current block is already large enough, reuse it
    if (block->size >= new_size) {
        return ptr;
    }

    //allocate a new block, copy, and free the old one
    void* new_ptr = my_malloc(new_size);
    if (!new_ptr) {
        // Allocation failed, keep the old block intact
        return NULL;
    }

    size_t copy_size = (block->size < new_size) ? block->size : new_size;
    memcpy(new_ptr, ptr, copy_size);

    my_free(ptr);
    return new_ptr;
}

void my_heap_dump(void) {
    printf("\n--- HEAP DUMP ---\n");

    BlockHeader* current = free_list;
    int index = 0;

    while (current) {
        printf(
            "Block %d: header=%p | size=%zu | free=%d | next=%p\n",
            index,
            (void*)current,
            current->size,
            current->free,
            (void*)current->next
        );

        current = current->next;
        index++;
    }

    printf("--- END HEAP DUMP ---\n\n");
}
