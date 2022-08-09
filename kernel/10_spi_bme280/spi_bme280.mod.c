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
	{ 0x1eff68e2, "spi_write_then_read" },
	{ 0xc880ec66, "spi_unregister_device" },
	{ 0x971cc567, "spi_setup" },
	{ 0xad473a5d, "spi_new_device" },
	{ 0x92997ed8, "_printk" },
	{ 0xf7456868, "spi_busnum_to_master" },
	{ 0xdcb764ad, "memset" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0x865d3282, "spi_sync" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "6C73430BAF42800CE0C32C1");
