#!/bin/bash
# This is generic build script we generated for our use case.
arg="$1"

function print_help () {
	echo "####################################################"
	echo "To build complete buildroot and generate rootfs.tar"
	echo "sudo ./build.sh"
	echo ""
	echo "To rebuild linux with updated changes"
	echo "sudo ./build.sh linux"
	echo "####################################################"
}

case $arg in
	"linux")
		cd output/build/linux-odroid-4.8.y
		sudo git pull
		cd -
		sudo make linux-rebuild
		sudo make linux-install
	;;
	"all")
		sudo make rhomb_defconfig
		sudo make
	;;
	"help")
		print_help
	;;
	*)
		print_help

	;;
esac


