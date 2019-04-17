# Settings
BTSTACK_DIR = ../assets/btstack/port/libusb
MONGOOSE_DIR = ../assets/mongoose

.DEFAULT_GOAL := websocket-to-ble-hid-bridge

# Include correct Makefile for the required settings
include ${BTSTACK_DIR}/Makefile

# Add the 'port' directory for searching missing stuff
VPATH+= ${BTSTACK_DIR}
CFLAGS+= -I${BTSTACK_DIR}
CFLAGS+= -I${MONGOOSE_DIR}
CFLAGS+= -DMG_ENABLE_FILESYSTEM=1

# Setup sources for dependencies
SOURCES = ${CORE_OBJ} ${COMMON_OBJ} ${ATT_OBJ} ${GATT_SERVER_OBJ} ${SM_OBJ} battery_service_server.o device_information_service_server.o hids_device.o btstack_ring_buffer.o
SOURCES+= ${MONGOOSE_DIR}/mongoose.c
SOURCES+= websocket-to-ble-hid-bridge.c

# Remove flags
CFLAGS:=$(filter-out -Wredundant-decls,${CFLAGS})
CFLAGS:=$(filter-out -Wshadow,${CFLAGS})
CFLAGS:=$(filter-out -Wmissing-prototypes,${CFLAGS})

# define target
websocket-to-ble-hid-bridge = websocket-to-ble-hid-bridge

# Create our target
websocket-to-ble-hid-bridge: $(SOURCES)
	${CC} $^ ${CFLAGS} ${LDFLAGS} -o ../websocket-to-ble-hid-bridge
