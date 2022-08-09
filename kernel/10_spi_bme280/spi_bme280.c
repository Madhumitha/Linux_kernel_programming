#include <linux/module.h>
#include <linux/init.h>
#include <linux/spi/spi.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Madhumitha Prabakaran");
MODULE_DESCRIPTION("A simple LKM to read and write some registers");

#define MY_BUS_NUM 0
static struct spi_device *bme280_dev;


static int __init ModuleInit(void) {
    struct spi_master *master;
    u8 id;
    u8 val[] = {0x75, 0x40};

    /*Parameters for SPI device*/
struct spi_board_info spi_device_info = {
            .modalias = "bme280",
            .max_speed_hz = 1000000,
            .bus_num = MY_BUS_NUM,
            .chip_select = 0,
            .mode = 3,
    };

    /*Get access to spi bus */
    master = spi_busnum_to_master(MY_BUS_NUM);
    /* Check if we could get the master */
    if(!master) {
            printk("There is no spi bus with Nr. %d\n", MY_BUS_NUM);
            return -1;
    }

    /* Create new SPI device */
    bme280_dev = spi_new_device(master, &spi_device_info);
    if(!bme280_dev) {
            printk("Could not create device!\n");
            return -1;
    }

    bme280_dev-> bits_per_word = 8;

    /* Setup the bus for device's parameters */
    if(spi_setup(bme280_dev) !=0) {
            printk("Could not change bus setup!\n");
            spi_unregister_device(bme280_dev);
            return -1;
    }
    
    /* Read Chip ID */
    id = spi_w8r8(bme280_dev, 0xD0);
    printk("Chip ID: 0x%x \n", id);

    /* Write to config reg */
    spi_write(bme280_dev, val, sizeof(8));
    id = spi_w8r8(bme280_dev, 0xF5);
    printk("Config Reg. Value: ox%x\n", id);


    printk("Hello, World!\n");
	return 0;
}

static void __exit ModuleExit(void) {
    if (bme280_dev)
        spi_unregister_device(bme280_dev);

    printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);


