#!/bin/bash
. setup_env

function device_not_found_error () {
	echo "Given device not found!"
	echo "please check dmesg for verification"
}

function copy_bootloader_binaries () {
	cp $UBOOT_DIR/sd_fuse/bl1.HardKernel $IMAGES_DIR
	cp $UBOOT_DIR/sd_fuse/bl2.HardKernel $IMAGES_DIR
	cp $UBOOT_DIR/sd_fuse/tzsw.HardKernel $IMAGES_DIR
	cp $UBOOT_DIR/sd_fuse/sd_fusing.sh $IMAGES_DIR
}

function create_partition () {
	sudo fdisk /dev/$1 <<END
	n
	p



	w
	q
END
}

function flash_bootloder () {
	cd $IMAGES_DIR
	sudo ./sd_fusing.sh /dev/$1
	sync
}

function copy_emmc_flashing_files () {
	cd $OUTPUT_DIR
	tar -cvf images.tar images
	sudo cp images.tar /mnt/tmp/opt/
}

function flash_kernel_rootfs () {
	echo "partition found"
	sudo umount /dev/$11
	sudo mkfs.ext4 /dev/$11
	sudo mkdir -p /mnt/tmp
	sudo mount /dev/$11 /mnt/tmp
	sudo tar -xf $IMAGES_DIR/rootfs.tar -C /mnt/tmp/
	sudo cp $IMAGES_DIR/zImage.exynos4412-rhomb-expansion /mnt/tmp/zImage
	sudo cp $ROOT_DIR/utils/fw_setenv /mnt/tmp/usr/bin/
	sudo cp $ROOT_DIR/utils/fw_printenv /mnt/tmp/usr/bin/
	sudo cp $UBOOT_DIR/tools/env/fw_env.config /mnt/tmp/etc/
	sudo cp emmc_fusing.sh $IMAGES_DIR
	copy_emmc_flashing_files
	cd $ROOT_DIR
	sync
	sudo umount /dev/$11
	sync
}

if [ -z $1 ]
then
	echo "usage:./prepare_sd.sh <SD Reader's device file>"
	echo "example: sdb, sdd, mmcblk0 etc"
	exit 0
else
	copy_bootloader_binaries
fi

if [ -b "/dev/$11" ]; then
	flash_kernel_rootfs $1
else
	echo "partition not found!"
	if [ -b "/dev/$1" ]; then
		create_partition $1
		flash_kernel_rootfs $1
	else
		device_not_found_error
	fi
fi

if [ -b "/dev/$1" ]; then
	flash_bootloder $1
	cd $ROOT_DIR
	echo "SD card prepared"
	echo "Insert sd card into board and set board in SD card bootmode"
	echo "Power on board"
	echo "Good luck!"
else
	device_not_found_error
	exit 0
fi
