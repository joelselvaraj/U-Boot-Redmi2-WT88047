/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Board configuration file for Wingtech WT88047
 *
 * (C) Copyright 2021 Joel Selvaraj <jo@jsfamily.in>
 */

#ifndef __CONFIGS_WT88047_H
#define __CONFIGS_WT88047_H

#include <linux/sizes.h>
#include <asm/arch/sysmap-apq8016.h>

/* Physical Memory Map */
#define PHYS_SDRAM_1			0x80000000
/* 1008 MB (the last ~30Mb are secured for TrustZone by ATF*/
#define PHYS_SDRAM_1_SIZE		0x3da00000
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x7fff0)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x80000)
#define CONFIG_SYS_BOOTM_LEN		SZ_64M

/* UART */

/* Generic Timer Definitions */
#define COUNTER_FREQUENCY		19000000

/* Fixup - in init code we switch from device to host mode,
 * it has to be done after each HCD reset */
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET

/* BOOTP options */
#define CONFIG_BOOTP_BOOTFILESIZE

#define BOOT_TARGET_DEVICES(func) \
	func(USB, usb, 0) \
	func(MMC, mmc, 1) \
	func(MMC, mmc, 0) \
	func(DHCP, dhcp, na)

#include <config_distro_bootcmd.h>

/* Environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x81000000\0" \
	"initrd_high=0xffffffffffffffff\0" \
	"linux_image=Image\0" \
	"kernel_addr_r=0x81000000\0"\
	"fdtfile=qcom/apq8016-sbc.dtb\0" \
	"fdt_addr_r=0x83000000\0"\
	"ramdisk_addr_r=0x84000000\0"\
	"scriptaddr=0x90000000\0"\
	"pxefile_addr_r=0x90100000\0"\
	BOOTENV

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + SZ_8M)

/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE		512	/* Console I/O Buffer Size */
#define CONFIG_SYS_MAXARGS		64	/* max command args */

#endif
