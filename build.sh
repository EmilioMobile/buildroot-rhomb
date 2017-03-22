#!/bin/bash
# This is generic build script we generated for our use case.
arg="$1"
ROOT_DIR=$PWD
UBOOT_DIR=$ROOT_DIR/output/build/uboot-odroid-v2015.10
KERNEL_DIR=$ROOT_DIR/output/build/linux-odroid-4.8.y

function print_help () {
	echo "####################################################"
	echo "To build complete buildroot and generate rootfs.tar"
	echo "sudo ./build.sh all"
	echo ""
	echo "To rebuild linux with updated changes"
	echo "sudo ./build.sh linux"
	echo ""
	echo "To rebuild uboot with updated changes"
	echo "sudo ./build.sh uboot"
	echo ""
	echo "To generate rootfs.tar"
	echo "sudo ./build.sh rootfs"
	echo ""
	echo "To clean all the directories"
	echo "sudo ./build.sh distclean"
	echo "WARNING: Above command will delete all the " \
	"downlaoded packages and restart all the things from " \
        "scratch"
	echo ""
	echo "To get help of build script commands"
	echo "sudo ./build.sh help"
	echo "####################################################"
}

function apply_buildroot_defconfig () {
	sudo make rhomb_defconfig
}

function linux_build () {
	if [ -d $KERNEL_DIR ];
	then
		cd output/build/linux-odroid-4.8.y
		sudo git pull
		cd -
		sudo make linux-rebuild
		sudo make linux-install
	else
		apply_buildroot_defconfig
		sudo make linux-rebuild
		sudo make linux-install
	fi
}

function uboot_build () {
	if [ -d $UBOOT_DIR ];
	then
		cd $UBOOT_DIR
		sudo git pull
		cd -
		sudo make uboot-rebuild
		sudo make uboot-install
	else
		apply_buildroot_defconfig
		sudo make uboot-rebuild
		sudo make uboot-install
	fi
}

function rootfs_build () {
	apply_buildroot_defconfig
	sudo make
}

function all_dir_clean () {
	sudo make distclean
}

case $arg in
	"linux")
		linux_build
	;;
	"uboot")
		uboot_build
	;;
	"rootfs")
		rootfs_build
	;;
	"all")
		apply_buildroot_defconfig
		uboot_build
		linux_build
		rootfs_build
	;;
	"distclean")
		all_dir_clean
	;;
	"help")
		print_help
	;;
	*)
		print_help

	;;
esac


