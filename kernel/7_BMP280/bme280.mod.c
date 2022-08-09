#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x7d0b00ef, "module_layout" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x61ba7417, "cdev_del" },
	{ 0x18321fdf, "i2c_del_driver" },
	{ 0xe5079f75, "i2c_unregister_device" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x89fbe416, "class_destroy" },
	{ 0x3c400e9b, "i2c_smbus_write_byte_data" },
	{ 0x478ee7af, "i2c_smbus_read_byte_data" },
	{ 0xcc1ba8dd, "i2c_put_adapter" },
	{ 0x2b8189c2, "i2c_register_driver" },
	{ 0xc0dee0ab, "i2c_new_client_device" },
	{ 0xf4a81870, "i2c_get_adapter" },
	{ 0xf881000e, "device_destroy" },
	{ 0x280ef9cf, "cdev_add" },
	{ 0x32318926, "cdev_init" },
	{ 0x5dad8514, "device_create" },
	{ 0x663f84fd, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xfd7915b6, "i2c_smbus_read_word_data" },
	{ 0x92997ed8, "_printk" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "0E84471F12BD645610E00A9");
