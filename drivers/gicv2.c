#include "gicv2.h"
#include "sysio.h"

#define GICV2_DIST_BASE_ADDRESS 0xf9010000U
#define GICV2_ACPU_BASE_ADDRESS 0xf9020000U

#define GICV2_GICD_CTLR         (GICV2_DIST_BASE_ADDRESS + 0x00000000U)
#define GICV2_GICD_ISENABLER    (GICV2_DIST_BASE_ADDRESS + 0x00000100U)
#define GICV2_GICD_IPRIORITYR   (GICV2_DIST_BASE_ADDRESS + 0x00000400U)
#define GICV2_GICD_ITARGETSR    (GICV2_DIST_BASE_ADDRESS + 0x00000800U)

#define GICV2_GICC_CTLR         (GICV2_ACPU_BASE_ADDRESS + 0x00000000U)
#define GICV2_GICC_PMR          (GICV2_ACPU_BASE_ADDRESS + 0x00000004U)
#define GICV2_GICC_IAR          (GICV2_ACPU_BASE_ADDRESS + 0x0000000CU)
#define GICV2_GICC_EOIR         (GICV2_ACPU_BASE_ADDRESS + 0x00000010U)


int gicv2_dist_init()
{
    /* disable distributor */
    sys_write32(0x0, GICV2_GICD_CTLR);

    /* set default priority to '0xa0' for all interrupts */
    unsigned long int def_prio = 0xa0a0a0a0UL;

    for (int i = 0; i < 195; i += 4) {
        sys_write32(def_prio, GICV2_GICD_IPRIORITYR + i);
    }

    /* redirect all interrupts to the cpu core number 0 */
    unsigned long int reg = 0x01010101;

    for (int i = 32; i < 195; i += 4) {
        sys_write32(reg, GICV2_GICD_ITARGETSR + i);
    }

    /* enable SPI */
    // TODO:

    /* enable distributor */
    sys_write32(0x1, GICV2_GICD_CTLR);

    return 0;
}

int gicv2_cpu_init()
{
    gicv2_set_gic_priority_mask(GIC_DEFAULT_PRIORITY_MASK);

    /* enable cpu interface */
    unsigned int reg = sys_read32(GICV2_GICC_CTLR);
    reg |= 0x1;
    sys_write32(0x01, GICV2_GICC_CTLR);

    return 0;
}

int gicv2_set_irq_priority(unsigned int irq, unsigned int priority)
{
    sys_write8(priority & 0xff, GICV2_GICD_IPRIORITYR + irq);
    return 0;
}

int gicv2_set_irq_target(unsigned int irq, unsigned int cpu_target)
{
    return -1;
}

int gicv2_set_irq_unmask(unsigned int irq)
{
    int int_grp, int_off;

    int_grp = irq / 32;
    int_off = irq % 32;

    sys_write32( (1 << int_off), (GICV2_GICD_ISENABLER + int_grp * 4) );
    return 0;
}

int gicv2_set_gic_priority_mask(unsigned int priority_mask)
{
    sys_write32(priority_mask, GICV2_GICC_PMR);
    return 0;
}

unsigned int gicv2_read_iar()
{
    return sys_read32(GICV2_GICC_IAR);
}

void gicv2_write_eoir(unsigned int int_id)
{
    sys_write32(int_id, GICV2_GICC_EOIR);
}
