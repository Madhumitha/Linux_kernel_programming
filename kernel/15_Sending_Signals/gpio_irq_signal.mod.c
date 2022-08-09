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
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xad8a16ad, "__register_chrdev" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0xbec1d3bc, "gpiod_to_irq" },
	{ 0x4254e7df, "gpiod_set_debounce" },
	{ 0xfe990052, "gpio_free" },
	{ 0xdbc892f4, "gpiod_direction_input" },
	{ 0xc442bf2a, "gpio_to_desc" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0xd98e4c97, "send_sig_info" },
	{ 0xdcb764ad, "memset" },
	{ 0x92997ed8, "_printk" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E733D61B533E64DA5B9C645");
