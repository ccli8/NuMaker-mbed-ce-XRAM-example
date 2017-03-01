#include "mbed.h"

// main() runs in its own thread in the OS
int main() {
    
    while (true) {
        void *heap = new uint8_t[32];
        
        uint32_t heap_ = ((uint32_t) heap) & 0xF0000000;
        switch (heap_) {
            case 0x20000000:
                printf("Heap allocated at 0x%08x (IRAM)\r\n", heap);
                break;
                
            case 0x60000000:
                printf("Heap allocated at 0x%08x (XRAM)\r\n", heap);
                break;
                
            default:
                printf("Heap allocated at 0x%08x (ILLEGAL)\r\n", heap);
        }
    
        delete [] heap;
        heap = NULL;
    
        wait(2.0);
    }
    
    return 0;
}
