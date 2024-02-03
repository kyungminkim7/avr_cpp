#include <avr_cpp/memory.h>

void * operator new(size_t size) {
    return malloc(size);
}

void * operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void *ptr) {
    free(ptr);
}

void operator delete(void *ptr, 
                     __attribute__((unused)) size_t size) {
    free(ptr);
}

void operator delete[](void *ptr) {
    free(ptr);
}

void operator delete[](void *ptr, 
                       __attribute__((unused)) size_t size) {
    free(ptr);
}