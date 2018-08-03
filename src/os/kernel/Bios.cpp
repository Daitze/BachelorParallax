/**
 * BIOS - provides BIOS-call functions in Protected Mode / Paging - environment
 *
 * @author Michael Schoettner, Filip Krakowski, Christian Gesse, Fabian Ruhland, Burak Akguel
 * @date HHU, 2018
 */

#include <kernel/memory/MemLayout.h>
#include "kernel/cpu/Cpu.h"

#include "kernel/Bios.h"


// extern code in interrupt.asm
extern "C" { void bios_call(); }   

// pointer to memory for parameters
struct BIOScall_params* BC_params = (struct BIOScall_params*)VIRT_BIOS16_PARAM_BASE;

/**
 * Builds up a 16-bit code segment manually. The start address
 * of this code segment is in the GDT for bios calls
 */
void Bios::init() {
	// pointer to memory segment for 16 bit code
    uint8_t *codeAddr = (uint8_t*)VIRT_BIOS16_CODE_MEMORY_START;

    // the assembler instructions are placed manually into the memory
    // in the following steps

    // mov eax, 5000
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0xB8;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x50;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;

    // mov [eax], esp
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0x67;   codeAddr++;
    *codeAddr = 0x89;   codeAddr++;
    *codeAddr = 0x20;   codeAddr++;
    
    
    
    // mov eax,cr0
    *codeAddr = 0x0F;   codeAddr++;
    *codeAddr = 0x20;   codeAddr++;
    *codeAddr = 0xC0;   codeAddr++;
    
    // and eax, 7FFEFFFE
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0x25;   codeAddr++;
    *codeAddr = 0xFE;   codeAddr++;
    *codeAddr = 0xFF;   codeAddr++;
    *codeAddr = 0xFE;   codeAddr++;
    *codeAddr = 0x7F;   codeAddr++;
    
    // mov cr0, eax
    *codeAddr = 0x0F;   codeAddr++;
    *codeAddr = 0x22;   codeAddr++;
    *codeAddr = 0xC0;   codeAddr++;
    
    // jmp 2400:001B flush pipeline & switch decoding unit
    // 0400:001B (0400<<4 = 4000 + 1B)
    *codeAddr = 0xEA;   codeAddr++;
    *codeAddr = 0x1B;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x04;   codeAddr++;
    
    // mov ds,400
    *codeAddr = 0xBA;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x04;   codeAddr++;
    
    // mov ss,dx
    *codeAddr = 0x8E;   codeAddr++;
    *codeAddr = 0xD2;   codeAddr++;
    
    // mov gs,dx
    *codeAddr = 0x8E;   codeAddr++;
    *codeAddr = 0xEA;   codeAddr++;
    
    // mov esp,2000 -> BIOS16_PARAM_BASE 0x6000
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0xBC;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x20;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    
    // pop ds
    *codeAddr = 0x1F;   codeAddr++;
    
    // pop es
    *codeAddr = 0x07;   codeAddr++;
    
    // pop fs
    *codeAddr = 0x0f;   codeAddr++;
    *codeAddr = 0xa1;   codeAddr++;
    
    // pop ax -> we have to pop something for symmetry
    *codeAddr = 0x58;   codeAddr++;
    
    // popad
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0x61;   codeAddr++;
    
    // interrupt number (written here)
    *codeAddr = 0xCD;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    
    // pushad
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0x60;   codeAddr++;
    
    // pushf
    *codeAddr = 0x9C;   codeAddr++;
    
    // push fs
    *codeAddr = 0x0f;   codeAddr++;
    *codeAddr = 0xa0;   codeAddr++;
    
    // push es
    *codeAddr = 0x06;   codeAddr++;
    
    // push ds
    *codeAddr = 0x1E;   codeAddr++;
    
    // mov eax,cr0
    *codeAddr = 0x0F;   codeAddr++;
    *codeAddr = 0x20;   codeAddr++;
    *codeAddr = 0xC0;   codeAddr++;
    
    // or eax, 00010001 (protected mode without paging)
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0x0D;   codeAddr++;
    *codeAddr = 0x01;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x01;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;

    // mov cr0, eax
    *codeAddr = 0x0F;   codeAddr++;
    *codeAddr = 0x22;   codeAddr++;
    *codeAddr = 0xC0;   codeAddr++;
    
    // jmp 0018:0049, flush pipeline & switch decoding
    // 0018:0049
    *codeAddr = 0xEA;   codeAddr++;
    *codeAddr = 0x49;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x18;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    
    // mov dx,0010
    *codeAddr = 0xBA;   codeAddr++;
    *codeAddr = 0x10;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    
    // mov ds,dx
    *codeAddr = 0x8E;   codeAddr++;
    *codeAddr = 0xDA;   codeAddr++;
    
    // mov es,dx
    *codeAddr = 0x8E;   codeAddr++;
    *codeAddr = 0xC2;   codeAddr++;
    
    // mov es,dx
    *codeAddr = 0x8E;   codeAddr++;
    *codeAddr = 0xE2;   codeAddr++;
    
    // mov fs,dx
    *codeAddr = 0x8E;   codeAddr++;
    *codeAddr = 0xEA;   codeAddr++;
    
    // mov ss,dx
    *codeAddr = 0x8E;   codeAddr++;
    *codeAddr = 0xD2;   codeAddr++;
    
    // mov eax, 25000
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0xB8;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x50;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    *codeAddr = 0x00;   codeAddr++;
    
    // mov esp, [eax]
    *codeAddr = 0x66;   codeAddr++;
    *codeAddr = 0x67;   codeAddr++;
    *codeAddr = 0x8B;   codeAddr++;
    *codeAddr = 0x20;   codeAddr++;
    
    // far ret
    *codeAddr = 0x66;	codeAddr++;
    *codeAddr = 0xCB;   codeAddr++;
}


/**
 * Provides a bios call via software interrupt
 */
void Bios::Int(int inter) {
	// get pointer to bios call segment
    uint8_t *ptr = (uint8_t*)VIRT_BIOS16_CODE_MEMORY_START;
    // write number of bios interrupt manually into the segment
    *(ptr+48) = (uint8_t)inter;
    
    // no interrupts during the bios call
    Cpu::disableInterrupts();
    // jump into assembler code
    bios_call ();
    // bios call is returned, interrupts are allowed now
    Cpu::enableInterrupts();
}