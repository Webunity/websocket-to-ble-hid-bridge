
// websocket-to-ble-hid-bridge-services.h generated from services/websocket-to-ble-hid-bridge-services.gatt for BTstack
// att db format version 1

// binary attribute representation:
// - size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#include <stdint.h>

const uint8_t profile_data[] =
{
    // ATT DB Version
    1,

    // 0x0001 PRIMARY_SERVICE-GAP_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18, 
    // 0x0002 CHARACTERISTIC-GAP_DEVICE_NAME-READ
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a, 
    // 0x0003 VALUE-GAP_DEVICE_NAME-READ-'Neeo Shield driver'
    // READ_ANYBODY
    0x1a, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x2a, 0x4e, 0x65, 0x65, 0x6f, 0x20, 0x53, 0x68, 0x69, 0x65, 0x6c, 0x64, 0x20, 0x64, 0x72, 0x69, 0x76, 0x65, 0x72, 
    // add Battery Service
    // #import <battery_service.gatt> -- BEGIN
    // Specification Type org.bluetooth.service.battery_service
    // https://www.bluetooth.com/api/gatt/xmlfile?xmlFileName=org.bluetooth.service.battery_service.xml
    // Battery Service 180F

    // 0x0004 PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_BATTERY_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x0f, 0x18, 
    // 0x0005 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_BATTERY_LEVEL-DYNAMIC | READ | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x12, 0x06, 0x00, 0x19, 0x2a, 
    // 0x0006 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_BATTERY_LEVEL-DYNAMIC | READ | NOTIFY-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x06, 0x00, 0x19, 0x2a, 
    // 0x0007 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x07, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // #import <battery_service.gatt> -- END
    // add Device ID Service
    // #import <device_information_service.gatt> -- BEGIN
    // Specification Type org.bluetooth.service.device_information
    // https://www.bluetooth.com/api/gatt/xmlfile?xmlFileName=org.bluetooth.service.device_information.xml
    // Device Information 180A

    // 0x0008 PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_DEVICE_INFORMATION
    0x0a, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x28, 0x0a, 0x18, 
    // 0x0009 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MANUFACTURER_NAME_STRING-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x09, 0x00, 0x03, 0x28, 0x02, 0x0a, 0x00, 0x29, 0x2a, 
    // 0x000a VALUE-ORG_BLUETOOTH_CHARACTERISTIC_MANUFACTURER_NAME_STRING-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x0a, 0x00, 0x29, 0x2a, 
    // 0x000b CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_MODEL_NUMBER_STRING-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x0b, 0x00, 0x03, 0x28, 0x02, 0x0c, 0x00, 0x24, 0x2a, 
    // 0x000c VALUE-ORG_BLUETOOTH_CHARACTERISTIC_MODEL_NUMBER_STRING-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x0c, 0x00, 0x24, 0x2a, 
    // 0x000d CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SERIAL_NUMBER_STRING-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x0d, 0x00, 0x03, 0x28, 0x02, 0x0e, 0x00, 0x25, 0x2a, 
    // 0x000e VALUE-ORG_BLUETOOTH_CHARACTERISTIC_SERIAL_NUMBER_STRING-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x0e, 0x00, 0x25, 0x2a, 
    // 0x000f CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_HARDWARE_REVISION_STRING-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x0f, 0x00, 0x03, 0x28, 0x02, 0x10, 0x00, 0x27, 0x2a, 
    // 0x0010 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_HARDWARE_REVISION_STRING-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x10, 0x00, 0x27, 0x2a, 
    // 0x0011 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_FIRMWARE_REVISION_STRING-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x11, 0x00, 0x03, 0x28, 0x02, 0x12, 0x00, 0x26, 0x2a, 
    // 0x0012 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_FIRMWARE_REVISION_STRING-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x12, 0x00, 0x26, 0x2a, 
    // 0x0013 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SOFTWARE_REVISION_STRING-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x13, 0x00, 0x03, 0x28, 0x02, 0x14, 0x00, 0x28, 0x2a, 
    // 0x0014 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_SOFTWARE_REVISION_STRING-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x14, 0x00, 0x28, 0x2a, 
    // 0x0015 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_SYSTEM_ID-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x15, 0x00, 0x03, 0x28, 0x02, 0x16, 0x00, 0x23, 0x2a, 
    // 0x0016 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_SYSTEM_ID-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x16, 0x00, 0x23, 0x2a, 
    // 0x0017 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x17, 0x00, 0x03, 0x28, 0x02, 0x18, 0x00, 0x2a, 0x2a, 
    // 0x0018 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x18, 0x00, 0x2a, 0x2a, 
    // 0x0019 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_PNP_ID-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x19, 0x00, 0x03, 0x28, 0x02, 0x1a, 0x00, 0x50, 0x2a, 
    // 0x001a VALUE-ORG_BLUETOOTH_CHARACTERISTIC_PNP_ID-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x1a, 0x00, 0x50, 0x2a, 
    // #import <device_information_service.gatt> -- END
    // add HID Service
    // #import <hids.gatt> -- BEGIN
    // Specification Type org.bluetooth.service.human_interface_device
    // https://www.bluetooth.com/api/gatt/xmlfile?xmlFileName=org.bluetooth.service.human_interface_device.xml
    // Human Interface Device 1812

    // 0x001b PRIMARY_SERVICE-ORG_BLUETOOTH_SERVICE_HUMAN_INTERFACE_DEVICE
    0x0a, 0x00, 0x02, 0x00, 0x1b, 0x00, 0x00, 0x28, 0x12, 0x18, 
    // 0x001c CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_PROTOCOL_MODE-DYNAMIC | READ | WRITE_WITHOUT_RESPONSE
    0x0d, 0x00, 0x02, 0x00, 0x1c, 0x00, 0x03, 0x28, 0x06, 0x1d, 0x00, 0x4e, 0x2a, 
    // 0x001d VALUE-ORG_BLUETOOTH_CHARACTERISTIC_PROTOCOL_MODE-DYNAMIC | READ | WRITE_WITHOUT_RESPONSE-''
    // READ_ANYBODY, WRITE_ANYBODY
    0x08, 0x00, 0x06, 0x01, 0x1d, 0x00, 0x4e, 0x2a, 
    // 0x001e CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_REPORT-DYNAMIC | READ | WRITE | NOTIFY | ENCRYPTION_KEY_SIZE_16
    0x0d, 0x00, 0x02, 0x00, 0x1e, 0x00, 0x03, 0x28, 0x1a, 0x1f, 0x00, 0x4d, 0x2a, 
    // 0x001f VALUE-ORG_BLUETOOTH_CHARACTERISTIC_REPORT-DYNAMIC | READ | WRITE | NOTIFY | ENCRYPTION_KEY_SIZE_16-''
    // READ_ENCRYPTED, WRITE_ENCRYPTED, ENCRYPTION_KEY_SIZE=16
    0x08, 0x00, 0x0b, 0xf5, 0x1f, 0x00, 0x4d, 0x2a, 
    // 0x0020 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ENCRYPTED, ENCRYPTION_KEY_SIZE=16
    0x0a, 0x00, 0x0f, 0xf1, 0x20, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // fixed report id = 1, type = Input (1)
    // 0x0021 REPORT_REFERENCE-READ-1-1
    0x0a, 0x00, 0x02, 0x00, 0x21, 0x00, 0x08, 0x29, 0x1, 0x1, 
    // 0x0022 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_REPORT-DYNAMIC | READ | WRITE | NOTIFY | ENCRYPTION_KEY_SIZE_16
    0x0d, 0x00, 0x02, 0x00, 0x22, 0x00, 0x03, 0x28, 0x1a, 0x23, 0x00, 0x4d, 0x2a, 
    // 0x0023 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_REPORT-DYNAMIC | READ | WRITE | NOTIFY | ENCRYPTION_KEY_SIZE_16-''
    // READ_ENCRYPTED, WRITE_ENCRYPTED, ENCRYPTION_KEY_SIZE=16
    0x08, 0x00, 0x0b, 0xf5, 0x23, 0x00, 0x4d, 0x2a, 
    // 0x0024 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ENCRYPTED, ENCRYPTION_KEY_SIZE=16
    0x0a, 0x00, 0x0f, 0xf1, 0x24, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // fixed report id = 2, type = Output (2)
    // 0x0025 REPORT_REFERENCE-READ-2-2
    0x0a, 0x00, 0x02, 0x00, 0x25, 0x00, 0x08, 0x29, 0x2, 0x2, 
    // 0x0026 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_REPORT-DYNAMIC | READ | WRITE | NOTIFY | ENCRYPTION_KEY_SIZE_16
    0x0d, 0x00, 0x02, 0x00, 0x26, 0x00, 0x03, 0x28, 0x1a, 0x27, 0x00, 0x4d, 0x2a, 
    // 0x0027 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_REPORT-DYNAMIC | READ | WRITE | NOTIFY | ENCRYPTION_KEY_SIZE_16-''
    // READ_ENCRYPTED, WRITE_ENCRYPTED, ENCRYPTION_KEY_SIZE=16
    0x08, 0x00, 0x0b, 0xf5, 0x27, 0x00, 0x4d, 0x2a, 
    // 0x0028 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ENCRYPTED, ENCRYPTION_KEY_SIZE=16
    0x0a, 0x00, 0x0f, 0xf1, 0x28, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // fixed report id = 3, type = Feature (3)
    // 0x0029 REPORT_REFERENCE-READ-3-3
    0x0a, 0x00, 0x02, 0x00, 0x29, 0x00, 0x08, 0x29, 0x3, 0x3, 
    // 0x002a CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_REPORT_MAP-DYNAMIC | READ
    0x0d, 0x00, 0x02, 0x00, 0x2a, 0x00, 0x03, 0x28, 0x02, 0x2b, 0x00, 0x4b, 0x2a, 
    // 0x002b VALUE-ORG_BLUETOOTH_CHARACTERISTIC_REPORT_MAP-DYNAMIC | READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x01, 0x2b, 0x00, 0x4b, 0x2a, 
    // 0x002c CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT-DYNAMIC | READ | WRITE | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x2c, 0x00, 0x03, 0x28, 0x1a, 0x2d, 0x00, 0x22, 0x2a, 
    // 0x002d VALUE-ORG_BLUETOOTH_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT-DYNAMIC | READ | WRITE | NOTIFY-''
    // READ_ANYBODY, WRITE_ANYBODY
    0x08, 0x00, 0x0a, 0x01, 0x2d, 0x00, 0x22, 0x2a, 
    // 0x002e CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x2e, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // 0x002f CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT-DYNAMIC | READ | WRITE | WRITE_WITHOUT_RESPONSE
    0x0d, 0x00, 0x02, 0x00, 0x2f, 0x00, 0x03, 0x28, 0x0e, 0x30, 0x00, 0x32, 0x2a, 
    // 0x0030 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT-DYNAMIC | READ | WRITE | WRITE_WITHOUT_RESPONSE-''
    // READ_ANYBODY, WRITE_ANYBODY
    0x08, 0x00, 0x0e, 0x01, 0x30, 0x00, 0x32, 0x2a, 
    // 0x0031 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT-DYNAMIC | READ | WRITE | NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x31, 0x00, 0x03, 0x28, 0x1a, 0x32, 0x00, 0x33, 0x2a, 
    // 0x0032 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT-DYNAMIC | READ | WRITE | NOTIFY-''
    // READ_ANYBODY, WRITE_ANYBODY
    0x08, 0x00, 0x0a, 0x01, 0x32, 0x00, 0x33, 0x2a, 
    // 0x0033 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x33, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // bcdHID = 0x101 (v1.0.1), bCountryCode 0, remote wakeable = 0 | normally connectable 2
    // 0x0034 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_HID_INFORMATION-READ
    0x0d, 0x00, 0x02, 0x00, 0x34, 0x00, 0x03, 0x28, 0x02, 0x35, 0x00, 0x4a, 0x2a, 
    // 0x0035 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_HID_INFORMATION-READ-'01 01 00 02'
    // READ_ANYBODY
    0x0c, 0x00, 0x02, 0x00, 0x35, 0x00, 0x4a, 0x2a, 0x01, 0x01, 0x00, 0x02, 
    // 0x0036 CHARACTERISTIC-ORG_BLUETOOTH_CHARACTERISTIC_HID_CONTROL_POINT-DYNAMIC | WRITE_WITHOUT_RESPONSE
    0x0d, 0x00, 0x02, 0x00, 0x36, 0x00, 0x03, 0x28, 0x04, 0x37, 0x00, 0x4c, 0x2a, 
    // 0x0037 VALUE-ORG_BLUETOOTH_CHARACTERISTIC_HID_CONTROL_POINT-DYNAMIC | WRITE_WITHOUT_RESPONSE-''
    // WRITE_ANYBODY
    0x08, 0x00, 0x04, 0x01, 0x37, 0x00, 0x4c, 0x2a, 
    // #import <hids.gatt> -- END

    // 0x0038 PRIMARY_SERVICE-GATT_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x38, 0x00, 0x00, 0x28, 0x01, 0x18, 
    // 0x0039 CHARACTERISTIC-GATT_SERVICE_CHANGED-READ
    0x0d, 0x00, 0x02, 0x00, 0x39, 0x00, 0x03, 0x28, 0x02, 0x3a, 0x00, 0x05, 0x2a, 
    // 0x003a VALUE-GATT_SERVICE_CHANGED-READ-''
    // READ_ANYBODY
    0x08, 0x00, 0x02, 0x00, 0x3a, 0x00, 0x05, 0x2a, 

    // END
    0x00, 0x00, 
}; // total size 338 bytes 


//
// list service handle ranges
//
#define ATT_SERVICE_GAP_SERVICE_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_END_HANDLE 0x0003
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_BATTERY_SERVICE_START_HANDLE 0x0004
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_BATTERY_SERVICE_END_HANDLE 0x0007
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_DEVICE_INFORMATION_START_HANDLE 0x0008
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_DEVICE_INFORMATION_END_HANDLE 0x001a
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_HUMAN_INTERFACE_DEVICE_START_HANDLE 0x001b
#define ATT_SERVICE_ORG_BLUETOOTH_SERVICE_HUMAN_INTERFACE_DEVICE_END_HANDLE 0x0037
#define ATT_SERVICE_GATT_SERVICE_START_HANDLE 0x0038
#define ATT_SERVICE_GATT_SERVICE_END_HANDLE 0x003a

//
// list mapping between characteristics and handles
//
#define ATT_CHARACTERISTIC_GAP_DEVICE_NAME_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BATTERY_LEVEL_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BATTERY_LEVEL_01_CLIENT_CONFIGURATION_HANDLE 0x0007
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MANUFACTURER_NAME_STRING_01_VALUE_HANDLE 0x000a
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_MODEL_NUMBER_STRING_01_VALUE_HANDLE 0x000c
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_SERIAL_NUMBER_STRING_01_VALUE_HANDLE 0x000e
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HARDWARE_REVISION_STRING_01_VALUE_HANDLE 0x0010
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_FIRMWARE_REVISION_STRING_01_VALUE_HANDLE 0x0012
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_SOFTWARE_REVISION_STRING_01_VALUE_HANDLE 0x0014
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_SYSTEM_ID_01_VALUE_HANDLE 0x0016
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_IEEE_11073_20601_REGULATORY_CERTIFICATION_DATA_LIST_01_VALUE_HANDLE 0x0018
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_PNP_ID_01_VALUE_HANDLE 0x001a
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_PROTOCOL_MODE_01_VALUE_HANDLE 0x001d
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_REPORT_01_VALUE_HANDLE 0x001f
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_REPORT_01_CLIENT_CONFIGURATION_HANDLE 0x0020
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_REPORT_02_VALUE_HANDLE 0x0023
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_REPORT_02_CLIENT_CONFIGURATION_HANDLE 0x0024
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_REPORT_03_VALUE_HANDLE 0x0027
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_REPORT_03_CLIENT_CONFIGURATION_HANDLE 0x0028
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_REPORT_MAP_01_VALUE_HANDLE 0x002b
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_01_VALUE_HANDLE 0x002d
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BOOT_KEYBOARD_INPUT_REPORT_01_CLIENT_CONFIGURATION_HANDLE 0x002e
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BOOT_KEYBOARD_OUTPUT_REPORT_01_VALUE_HANDLE 0x0030
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT_01_VALUE_HANDLE 0x0032
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_BOOT_MOUSE_INPUT_REPORT_01_CLIENT_CONFIGURATION_HANDLE 0x0033
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HID_INFORMATION_01_VALUE_HANDLE 0x0035
#define ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_HID_CONTROL_POINT_01_VALUE_HANDLE 0x0037
#define ATT_CHARACTERISTIC_GATT_SERVICE_CHANGED_01_VALUE_HANDLE 0x003a
