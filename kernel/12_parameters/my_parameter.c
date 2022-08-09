#include <linux/module.h>
#include <linux/init.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Madhumitha Prabakaran");
MODULE_DESCRIPTION("A simple LKM to demonstrate the use of parameters");

/* Kernel module's parameter*/
static unsigned int gpio_nr = 12;
static char *device_num = "testdevice";

module_param(gpio_nr, uint, S_IRUGO);
module_param(device_num, charp, S_IRUGO);

MODULE_PARM_DESC(gpio_nr, "Nr. of GPIO to use in this LKM");
MODULE_PARM_DESC(device_num, "Device name to use in this LKM");

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init my_init(void) {
	printk("gpio_nr = %u\n", gpio_nr);
    printk("device_name = %s\n", device_num);

    printk("Hello, Kernel!\n");
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */

static void __exit my_exit(void) {
	printk("Goodbye, Kernel\n");
}

module_init(my_init);
module_exit(my_exit);
