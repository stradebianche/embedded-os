#include "sysio.h"
#include "gicv2.h"

extern int systick;

void os_interrupt_handler(void) 
{
    unsigned int int_id;
    /* read ACK register */
    int_id = gicv2_read_iar();

    /* ARM Generic Interrupt Controller Architecture version 2.0 Architecture Specification, chapter 4.4.5:
    For every read of a valid Interrupt ID from the GICC_IAR, the connected processor must perform a matching write
    to the GICC_EOIR. The value written to the GICC_EOIR must be the interrupt ID read from the GICC_IAR.
    If a read of the GICC_IAR returns the ID of a spurious interrupt, software does not have to make a corresponding
    write to the GICC_EOIR. If software writes the ID of a spurious interrupt to the GICC_EOIR, the GIC ignores that
    write. */

    int_id = int_id & 0x3FFU; /* int ack mask */

    switch(int_id) {
    case 27:
        asm volatile ("nop");
	    asm volatile ("mrs x0, cntvct_el0");    /* store current counter value into x0 */
	    asm volatile ("isb");
	    asm volatile ("mov x1, #1");
	    asm volatile ("lsl x1, x1, #28");
	    asm volatile ("add x0, x0, x1");        /* add 2^28 to the counter value */
        /* writing value bigger than current CNTVCT_EL0 will clear irq bit in CNTV_CTL_EL0 */
	    asm volatile ("msr cntv_cval_el0, x0");

        systick = 1;
        break;
    default:
        break;
    }

    /* write EOI register */
    gicv2_write_eoir(int_id);
    return;
}
