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
	{ 0x72745dbd, "kthread_stop" },
	{ 0x770d705c, "wake_up_process" },
	{ 0x2dc0f430, "kthread_create_on_node" },
	{ 0xf9a482f9, "msleep" },
	{ 0x92997ed8, "_printk" },
	{ 0xb3f7646e, "kthread_should_stop" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "F6BC2662D76BDB2CA3979C5");
