#/bin/bash
if [ -z $1 ]
then
	echo "usage:./prepare_sd.sh <SD Reader's device file>"
	echo "example: sdb, sdd, mmcblk0 etc"
	exit 0
fi

cd output/build/uboot-odroid-v2015.10/sd_fuse
sudo ./sd_fusing.sh /dev/$1
sync
cd -
if [ -b "/dev/$11" ]; then
	echo "partition found"
	sudo umount /dev/$11
	sudo mkfs.ext4 /dev/$11
	sudo mkdir -p /mnt/tmp
	sudo mount /dev/sdb1 /mnt/tmp
	sudo tar -xf output/images/rootfs.tar -C /mnt/tmp/
	sudo cp output/images/zImage.exynos4412-rhomb-expansion /mnt/tmp/zImage
	sync
	sudo umount /dev/$11
	echo "SD card prepared"
	echo "Insert sd card into board"
	echo "Set below bootcmd at bootlaoder prompt"
	echo "setenv bootcmd 'ext4load mmc 0:1 0x40008000 zImage;bootm 0x40008000'"
	echo "Set below bootargs at bootloader prompt and then boot"
	echo "setenv bootargs 'console=tty1 console=ttySAC1,115200 mem=1023M root=/dev/mmcblk0p1 rootwait rw'"
	echo "Good luck!"
else
	echo "partition not found please check in /dev/<> directory"
	echo "please check dmesg for verification"
fi

