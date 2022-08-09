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
	{ 0x61ba7417, "cdev_del" },
	{ 0x87f4283c, "pwm_free" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x89fbe416, "class_destroy" },
	{ 0xf881000e, "device_destroy" },
	{ 0xcee3a79f, "pwm_request" },
	{ 0x280ef9cf, "cdev_add" },
	{ 0x32318926, "cdev_init" },
	{ 0x5dad8514, "device_create" },
	{ 0x663f84fd, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0xdcb764ad, "memset" },
	{ 0xc0cbe749, "pwm_apply_state" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x92997ed8, "_printk" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "361CFA06BBEB32AB2924230");
