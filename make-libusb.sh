#!/bin/bash


echo '------------------------------------------'
echo 'Setting up: websocket-to-ble-hid-bridge'
echo '------------------------------------------'
echo
echo 'Please note: this setup script is tested on a Pi 3B with attached USB BLE adapter..'
echo
echo 'Starting with setup in 5 seconds...'
echo
sleep 5

SETUP_DIR=`pwd`
export BTSTACK_ROOT="${SETUP_DIR}/assets/btstack"

if [ ! -d "assets" ]; then
	mkdir assets
	sudo apt-get install git gcc libusb-1.0 pkg-config
fi

if [ ! -d "assets/btstack" ]; then
	echo '- Cloning "btstack" library ...'
	git clone -b develop --single-branch --depth 1 --quiet https://github.com/bluekitchen/btstack assets/btstack
	if [ $? == 1 ]; then
		echo '  - Error running GIT command, exiting!'
		exit 1
	fi

	echo '- Compiling "btstack" library ...'
	cd ./assets/btstack/port/libusb && make
	if [ $? == 1 ]; then
		echo '  - Error building btstack, exiting!'
		exit 1
	fi
fi

if [ ! -d "assets/mongoose" ]; then
	echo '- Cloning "mongoose" library ...'
	git clone --single-branch --depth 1 --quiet https://github.com/cesanta/mongoose assets/mongoose
	if [ $? == 1 ]; then
		echo '  - Error running GIT command, exiting!'
		exit 1
	fi
fi

echo '- (re)Compiling ...'
echo
cd "${SETUP_DIR}/libusb" && make
if [ $? == 1 ]; then
	echo '  - Error building btstack, exiting!'
	exit 1
else
	echo '  - All done!'
fi
