#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/interrupt.h>	

static irqreturn_t keyboard_handler(int irq, void *dev_id)
{
	printk("Hello\n");
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