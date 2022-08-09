#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/i2c.h>
#include <linux/kernel.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Madhumitha Prabakaran");
MODULE_DESCRIPTION("A deiver for reading out a BMP280 temperature sensor");

/* Variables for device and deviceclass */
static dev_t myDeviceNr;
static struct class *myClass;
static struct cdev myDevice;

#define DRIVER_NAME "bme280"
#define DRIVER_CLASS "bme280Class"

static struct i2c_adapter *bme_i2c_adapter = NULL;
static struct i2c_client *bme280_i2c_client = NULL;

/* Defines for device identification */
#define I2C_BUS_AVAILABLE 1 /* I2C Bus avaiable on the raspberry */
#define SLAVE_DEVICE_NAME "BME280" /* Device and Driver Name */
#define BME280_SLAVE_ADDRESS 0x77 /* BME280 I2C address */

static const struct i2c_device_id bme_id[] = {
	{ SLAVE_DEVICE_NAME, 0 },
	{ }
};

static struct i2c_driver bme_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE
	}
};

static struct i2c_board_info bme_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME, BME280_SLAVE_ADDRESS)
};

/* Variables for temperature calculation */
s32 dig_T1, dig_T2, dig_T3;

/**
* @brief Read current temperature from BMP280 sensor
*
* @return temperature in degree
*
*/

s32 read_temperature(void) {
        int var1, var2;
        s32 raw_temp;
        s32 d1, d2, d3;

        /* Read the temperature reisters */

    d1 = i2c_smbus_read_word_data(bme280_i2c_client, 0xFA);
    d2 = i2c_smbus_read_word_data(bme280_i2c_client, 0xFB);
    d3 = i2c_smbus_read_word_data(bme280_i2c_client, 0xFC);

    raw_temp = ((d1<<16) | (d2<<8) | d3) >> 4;

    var1 = ((((raw_temp >> 3) - (dig_T1 << 1)))* dig_T2) >> 11;
    var2 = (((((raw_temp >> 4) - (dig_T1)) * ((raw_temp >> 4) - dig_T1)) >> 12) * dig_T3) >> 14;

    return ((var1 + var2) * 5 + 128) >> 8;
 }
    

/**
 *  @brief Read data out of the buffer
 */

static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;
    char out_string[20];
    int temperature;

	/* Get amount of data to copy */
	to_copy = min(count, sizeof(out_string));
        
    /* Get temperature */
    temperature = read_temperature();
    snprintf(out_string, sizeof(out_string), "%d.%d\n", temperature/100, temperature%100);


	/* Copy data to user */
	not_copied = copy_to_user(user_buffer, out_string, to_copy);

	/* Calculate data */
	delta = to_copy - not_copied;

	return delta;
}

/** 
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *deviceFile, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}

/**
 * @ brief This function is called, when the device file is closed
 */
static int driver_close(struct inode *deviceFile, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}

/* Map the file operations */
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
};

/* The return value is not equal to 0, the device number is already in use. The upper 12 bits of the return value are major device number, the lower 20 bits are the minor device number */

static int __init ModuleInit(void) {
	int ret = -1;
    u8 id;
	printk("Hello, World!\n");
	
	/* Allocate a device number */
	if( alloc_chrdev_region(&myDeviceNr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}
	printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", myDeviceNr >> 20, myDeviceNr && 0xfffff);

	/* Create device class */
	if((myClass = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device ckass cannot be created!\n");
		goto ClassError;
	}

	/* Create device file */
	if(device_create(myClass, NULL, myDeviceNr, NULL, DRIVER_NAME) == NULL) {
		printk("Cannot create device file!\n");
		goto FileError;
	}

	/* Initialize device file */
	cdev_init(&myDevice, &fops);

	/* Registering device to kernel */
	if(cdev_add(&myDevice, myDeviceNr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto KernelError;
	}

    bme_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

    if(bme_i2c_adapter != NULL) {
            bme280_i2c_client = i2c_new_client_device(bme_i2c_adapter, &bme_i2c_board_info);
            if(bme280_i2c_client != NULL) {
                    if(i2c_add_driver(&bme_driver) != -1) {
                            ret = 0;
                            }
                        else
                                printk("Can't add driver...\n");
            }
            i2c_put_adapter(bme_i2c_adapter);
        }
    printk("BME280 Driver added!\n");

    /* Read Chip ID*/
    id = i2c_smbus_read_byte_data(bme280_i2c_client, 0xD0);
    printk("ID: 0x%x\n", id);

    /* Read Calibration Values */
    dig_T1 = i2c_smbus_read_word_data(bme280_i2c_client, 0x88);
    dig_T2 = i2c_smbus_read_word_data(bme280_i2c_client, 0x8A);
    dig_T3 = i2c_smbus_read_word_data(bme280_i2c_client, 0x8C);

    if(dig_T2 > 32767)
        dig_T2 -= 65536;

    if(dig_T3 > 32767)
        dig_T3 -= 65536;

    /* Initialize the sensor */
    i2c_smbus_write_byte_data(bme280_i2c_client, 0xf5, 5<<5);
    i2c_smbus_write_byte_data(bme280_i2c_client, 0xf4, 5<<5 | 5<<2 | 3<<0);

    return ret;

KernelError:
	device_destroy(myClass, myDeviceNr);
FileError:
	class_destroy(myClass);
ClassError:
	unregister_chrdev(myDeviceNr, DRIVER_NAME);
	return -1;
}

/*
 * This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	i2c_unregister_device(bme280_i2c_client);
    i2c_del_driver(&bme_driver);
    cdev_del(&myDevice);
	device_destroy(myClass, myDeviceNr);
	class_destroy(myClass);
	unregister_chrdev_region(myDeviceNr, 1);
	printk("Goodbye Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);


