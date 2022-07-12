#ifndef GIC_V_2_H_
#define GIC_V_2_H_

#define GIC_DEFAULT_PRIORITY_MASK 0xf0

#define GIC_IRQ_ENABLE  0
#define GIC_IRQ_DISABLE 1

int gicv2_dist_init();

int gicv2_cpu_init();

int gicv2_set_irq_priority(unsigned int irq, unsigned int priority);

int gicv2_set_irq_target(unsigned int irq, unsigned int cpu_target);

int gicv2_set_irq_unmask(unsigned int irq);

int gicv2_set_gic_priority_mask(unsigned int priority_mask);

#endif
