#include "mbed.h"
#include <inttypes.h>

#if TARGET_NUMAKER_PFM_NUC472
void demo_disable_ebi_ram(void);
#elif TARGET_NUMAKER_IOT_M467
void demo_enable_hyperram(void);
#endif

int main()
{
#if TARGET_NUMAKER_PFM_NUC472
    demo_disable_ebi_ram();
#elif TARGET_NUMAKER_IOT_M467
    demo_enable_hyperram();
#endif

    return 0;
}

#if TARGET_NUMAKER_PFM_NUC472

void demo_disable_ebi_ram(void)
{
    uint32_t *heap = new uint32_t[32];
    
    uint32_t heap_ = ((uint32_t) heap) & 0xF0000000;
    switch (heap_) {
    case 0x20000000:
        printf("Heap allocated at %" PRIxPTR " (IRAM)\n", (uintptr_t) heap);
        break;

    case 0x60000000:
        printf("Heap allocated at %" PRIxPTR " (EBI RAM)\n", (uintptr_t) heap);
        break;

    default:
        printf("Heap allocated at %" PRIxPTR " (ILLEGAL)\n", (uintptr_t) heap);
    }

    uint32_t *my_heap_data1_p = &heap[1];
    *my_heap_data1_p = 1;
    uint32_t *my_heap_data2_p = &heap[2];
    *my_heap_data2_p = 2;
    uint32_t *my_heap_data3_p = &heap[3];
    *my_heap_data3_p = 3;

    while (true) {
        printf("Heap data 1: %" PRIu32 " (%" PRIxPTR ")\n", *my_heap_data1_p, (uintptr_t) my_heap_data1_p);
        printf("Heap data 2: %" PRIu32 " (%" PRIxPTR ")\n", *my_heap_data2_p, (uintptr_t) my_heap_data2_p);
        printf("Heap data 3: %" PRIu32 " (%" PRIxPTR ")\n", *my_heap_data3_p, (uintptr_t) my_heap_data3_p);

        *my_heap_data1_p += 1;
        *my_heap_data2_p += 2;
        *my_heap_data3_p += 3;

        ThisThread::sleep_for(2s);
    }

    delete [] heap;
    heap = NULL;
}

#elif TARGET_NUMAKER_IOT_M467

#if MBED_CONF_TARGET_HBI_ENABLE
/* Locate initialized data at HyperRAM */
__attribute__((section(".data.nu.hyperram")))
#endif
uint32_t my_data = 100;

#if MBED_CONF_TARGET_HBI_ENABLE
/* Locate zero-initialized data at HyperRAM */
__attribute__((section(".bss.nu.hyperram")))
#endif
uint32_t my_bss;

void demo_enable_hyperram(void)
{
    while (true) {
        printf("Initialized data: %" PRIu32 " (%" PRIxPTR ")\n", my_data, (uintptr_t) &my_data);
        printf("Zero-initialized data: %" PRIu32 " (%" PRIxPTR ")\n", my_bss, (uintptr_t) &my_bss);

        my_data ++;
        my_bss ++;

        ThisThread::sleep_for(2s);
    }
}

#endif
