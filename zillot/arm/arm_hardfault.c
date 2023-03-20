#include <igris/dprint.h>
#include <stdint.h>

void hardfault_handler(void) __attribute__((naked));
void prvGetRegistersFromStack(uint32_t *pulFaultStackAddress)
    __attribute__((used));

/* The fault handler implementation calls a function called
prvGetRegistersFromStack(). */
void hardfault_handler(void)
{
    __asm volatile(
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n");
}

void prvGetRegistersFromStack(uint32_t *pulFaultStackAddress)
{
    /* These are volatile to try and prevent the compiler/linker optimising them
    away as the variables never actually get used.  If the debugger won't show
    the values of the variables, make them global my moving their declaration
    outside of this function. */
    volatile uint32_t r0;
    volatile uint32_t r1;
    volatile uint32_t r2;
    volatile uint32_t r3;
    volatile uint32_t r12;
    volatile uint32_t lr;  /* Link register. */
    volatile uint32_t pc;  /* Program counter. */
    volatile uint32_t psr; /* Program status register. */

    r0 = pulFaultStackAddress[0];
    r1 = pulFaultStackAddress[1];
    r2 = pulFaultStackAddress[2];
    r3 = pulFaultStackAddress[3];

    r12 = pulFaultStackAddress[4];
    lr = pulFaultStackAddress[5];
    pc = pulFaultStackAddress[6];
    psr = pulFaultStackAddress[7];

    debug_print_newline();
    dprln("HARDFAULT:");

    debug_print("HFSR: ");
    debug_printhex_uint32(*(uint32_t *)0xE000ED2C);
    debug_print_newline();

    debug_print("CFSR: ");
    debug_printhex_uint32(*(uint32_t *)0xE000ED28);
    debug_print_newline();

    debug_print("UFSR: ");
    debug_printhex_uint16(*(uint16_t *)0xE000ED2A);
    debug_print_newline();

    debug_print("BFSR: ");
    debug_printhex_uint8(*(uint8_t *)0xE000ED29);
    debug_print_newline();

    debug_print("MMFSR: ");
    debug_printhex_uint8(*(uint8_t *)0xE000ED28);
    debug_print_newline();

    debug_print("ABFSR: ");
    debug_printhex_uint32(*(uint32_t *)0xE000EFA8);
    debug_print_newline();

    DPRINTHEX(r0);
    DPRINTHEX(r1);
    DPRINTHEX(r2);
    DPRINTHEX(r3);
    DPRINTHEX(r12);
    DPRINTHEX(lr);
    DPRINTHEX(pc);
    DPRINTHEX(psr);

    /* When the following line is hit, the variables contain the register
     * values. */
    for (;;)
        ;
}