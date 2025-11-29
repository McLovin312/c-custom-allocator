#include <stdio.h>
#include "allocator.h"

static void print_ptr(const char* label, void* ptr) {
    printf("%s = %p\n", label, ptr);
}

int main(void) {
    printf("Initializing allocator...\n");
    my_allocator_init();
    my_heap_dump();

    printf("\n=== Basic allocations ===\n");
    void* a = my_malloc(100);
    void* b = my_malloc(200);
    void* c = my_malloc(50);

    print_ptr("a", a);
    print_ptr("b", b);
    print_ptr("c", c);
    my_heap_dump();

    printf("\n=== Freeing middle block (b) ===\n");
    my_free(b);
    my_heap_dump();

    printf("Allocating d (180 bytes) – ideally reuses freed space from b\n");
    void* d = my_malloc(180);
    print_ptr("d", d);
    my_heap_dump();

    printf("\n=== Freeing remaining blocks ===\n");
    my_free(a);
    my_free(c);
    my_free(d);
    my_heap_dump();

    printf("\nDone.\n");
    return 0;
}
