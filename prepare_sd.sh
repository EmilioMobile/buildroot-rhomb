#/bin/bash
echo "Enter mounted partition of sd card node name"
echo "example: /dev/sdb1, /dev/mmcblk0p1"
echo "         Just give parition name \"sdb1\", \"mmcblk0p1\" etc"
read node
if [ -b "/dev/$node" ]; then
	echo "node found"
	sudo umount /dev/$node
	sudo mkfs.ext4 /dev/$node
	sudo mkdir -p /mnt/tmp
	sudo mount /dev/sdb1 /mnt/tmp
	sudo tar -xf output/images/rootfs.tar -C /mnt/tmp/
	sudo cp output/images/zImage.exynos4412-rhomb-expansion /mnt/tmp/zImage
	sync
	sudo umount /dev/$node
	echo "SD card prepared"
	echo "Insert sd card into board"
	echo "Set below bootargs in board and bootloader prompt and then boot"
	echo "setenv bootargs 'console=tty1 console=ttySAC1,115200 mem=1023M root=/dev/mmcblk0p1 rootwait rw'"
	echo "Good luck!"
else
	echo "node not found please check in /dev/<> directory"
	echo "please check dmesg for verification"
fi

