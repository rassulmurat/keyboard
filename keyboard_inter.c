#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/interrupt.h>	

#define KBD_IRQ             1       /* IRQ number for keyboard (i8042) */
#define KBD_DATA_REG        0x60    /* I/O port for keyboard data */
#define KBD_SCANCODE_MASK   0x7f
#define KBD_STATUS_MASK     0x80

static irqreturn_t keyboard_handler(int irq, void *dev_id)
{
	char scancode;

    scancode = inb(KBD_DATA_REG);
    /* NOTE: i/o ops take a lot of time thus must be avoided in HW ISRs */
    printk("%x \n", scancode);

    return IRQ_HANDLED;
}

static int __init keyboard_init(void)
{
	printk("At least im trying\n");
	request_irq(1, keyboard_handler, IRQF_SHARED, "keyboard_test", (void*)keyboard_handler);
	return 0;
}

static void __exit keyboard_clean(void)
{
	free_irq(1, keyboard_handler);
}

module_init(keyboard_init);
module_exit(keyboard_clean);