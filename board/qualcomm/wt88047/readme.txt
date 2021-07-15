# SPDX-License-Identifier: GPL-2.0+
#
# (C) Copyright 2021 Joel Selvaraj <jo@jsfamily.in>

Build & Run instructions:

1) Install mkbootimg and dtbTool from
   git://codeaurora.org/quic/kernel/skales (15ece94f09 worked for me)
2) Setup CROSS_COMPILE to aarch64 compiler
3) make wt88047_config
4) make
5) generate fake, empty ramdisk (can have 0 bytes)
$ touch rd

6) Generate qualcomm device tree table with dtbTool [1]
$ dtbTool -o dt.img arch/arm/dts

7) Generate Android boot image with mkbootimg [2]:
$ mkbootimg --kernel=u-boot-dtb.bin --output=u-boot.img --dt=dt.img  \
  --pagesize 2048 --base 0x80000000 --ramdisk=rd --cmdline=""

8) Enter fastboot (reboot board with vol- button pressed)

9) Boot it:
$ fastboot boot u-boot.img
or flash as kernel:
$ fastboot flash boot u-boot.img
$ fastboot reboot


What is working:
- UART
- GPIO (SoC)
- SD
- eMMC
- Reset
- USB in EHCI mode (usb starts does switch device->host, usb stop does the opposite)
- PMIC GPIOS (but not in generic subsystem)
- PMIC "special" buttons (power, vol-)

What is not working / known bugs:
- SDHCI is slow (~2.5MiB/s for SD and eMMC)

[1] To boot any kernel image, Little Kernel requires valid device tree for the
platform it runs on. dtbTool creates device tree table that Little Kernel scans.
Later on proper device tree is passed to next boot stage.
Full device tree is not required to boot u-boot. Enough would be:
/dts-v1/;

/ {
	model = "Qualcomm Technologies, Inc. MSM8916";
	compatible = "qcom,msm8916-qrd-wt88047", "qcom,msm8916-qrd", "qcom,msm8916", "qcom,qrd";
	qcom,msm-id =	<206 0>, <248 0>, <249 0>, <250 0>;
    qcom,board-id = <0x1000b 7>, <0x1010b 7>, <0x3010b 7>, <0x1000b 12>, <0x1010b 12>, <0x3010b 12>;
	
	#address-cells = <0x2>;
	#size-cells = <0x2>;

	memory {
		device_type = "memory";
		reg = <0 0x80000000 0 0x3da00000>;
	};
};

but for simplicity (and because size of image is not that critical) we use
existing Qualcomm device trees.

[2] Note that ramdisk is required, even if it is unused.
