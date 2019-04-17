# Websocket-to-ble-hid-bridge
This is a bluetooth peripheral which acts as a 'keyboard' using a plugged in bluetooth USB adapter. It can be used for example to control [using my NVidia Shield driver](https://github.com/Webunity/neeo-driver-nvidia-shield) for the Neeo remote.
Please make sure you have a Bluetooth hardware dongle attached to your Raspberry Pi before attempting to install/run this driver.

![how-it-works](./assets/websocket-to-ble-hid-bridge.png?raw=true)
  
> This is a 'works-on-my-machine' repository; i really don't have time to support 'compile' issues.

## Debug console
The web_debug folder is served by the websocket webserver, running on the HID peripheral. This page has an auto-reconnecting websocket implementation and 2 possiblities to send data to the peripheral.

The peripheral makes use of the the following dependencies:
- https://github.com/cesanta/mongoose
- https://github.com/bluekitchen/btstack

> Note: This website uses an external jQuery library, served from a CDN. If you want to run this sample on a device which doesn't have access to the internet, you need to modify the index.html yourself.

### Option 1 - send a modifier and keycode.
In case you already know the modifier and keycode, you can send them using the box on the left. The format is "<modifier>,<keycode>", where modifier is one of these codes:
  - 0: no modifier
  - 1: Left Ctrl
  - 2: Left Shift
  - 4: Left Alt
  - 8: Left GUI key (Windows key / Command key)
  - 16: Right Ctrl
  - 32: Right Shift
  - 64: Right Alt
  - 128: Right GUI key (Windows key / Command key)

The keycode is an numeric representation of a keycode between 1 and 255; for inspiration, take a look at this online page [USB HID Keyboard Scan Codes](https://serverhelfer.de/usb-hid-keyboard-scan-codes/) (remember to convert the HEX value to the numerical representation).

As an alternative, keycodes can be found in the sourcecode of the peripheral, e.g. an 'a' is "0,4" (no modifier, key is 4) and an 'A' is "2,4" (shift modifier, key is 4).

### Option 2 - send a text string
With the box on the right of the page you can send a string. This is not implemented in the Neeo driver itself but it is supported by the BLE HID peripheral. Each character will be sent 'as-is'; the peripheral finds out which modifier and keycode are needed to be put in the buffer before it is sent to the paired BLE device.
