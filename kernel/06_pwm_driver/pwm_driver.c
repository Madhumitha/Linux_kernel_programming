#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/pwm.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Madhumitha Prabakaran");
MODULE_DESCRIPTION("A simple PWM driver to access the hardware PWM IP");

/* Variables for devcice and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "my_pwm_driver"
#define DRIVER_CLASS "MyModuleClass"

/* Variables for device PWM */
struct pwm_device *pwm0 = NULL;
u32 pwm_on_time = 500000000;

/**
 *  @brief Write data to buffer
 */

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;
	char value;

	/* Get amount of data to copy */
	to_copy = min(count, sizeof(value));

	/* Copy data from user */
	not_copied = copy_from_user(&value, user_buffer, to_copy);
	
	/* Set PWM on time */
	if(value < 'a' || value > 'j')
		printk("Invalid value\n");
	else
		pwm_config(pwm0, 100000000 * (value -'a'), 1000000000);

	/* Calculate data */
	delta = to_copy - not_copied;

	return delta;
}
/** 
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}

/**
 * @ brief This function is called, when the device file is closed
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.write = driver_write
};


/* The return value is not equal to 0, the device number is already in use. The upper 12 bits of the return value are major device number, the lower 20 bits are the minor device number */

static int __init ModuleInit(void) {
	printk("Hello, World!\n");
	
	/* Allocate a device number */
	if( alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}
	printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr && 0xfffff);

	/* Create device class */
	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device ckass cannot be created!\n");
		goto ClassError;
	}

	/* Create device file */
	if(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Cannot create device file!\n");
		goto FileError;
	}

	/* Initialize device file */
	cdev_init(&my_device, &fops);

	/* Registering device to kernel */
	if(cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto AddError;
	}
	
	pwm0 = pwm_request(0, "my-pwm");
	if(pwm0 == NULL) {
		printk("Could not get PWM0!\n");
		goto AddError;
	}

	pwm_config(pwm0, pwm_on_time, 1000000000);
	pwm_enable(pwm0);
		
	return 0;
AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;
}

/*
 * This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	pwm_disable(pwm0);
	pwm_free(pwm0);
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);


