#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>



//--------------------------------------------------
// BLE includes
//--------------------------------------------------
#include "websocket-to-ble-hid-bridge.h"
#include "websocket-to-ble-hid-bridge-services.h"	// Include pre-generated services header

#include "btstack.h"
#include "ble/gatt-service/battery_service_server.h"
#include "ble/gatt-service/device_information_service_server.h"
#include "ble/gatt-service/hids_device.h"



//--------------------------------------------------
// Websocket includes
//--------------------------------------------------
#include "mongoose.h"




//--------------------------------------------------
// HID variables
//--------------------------------------------------
#define HID_STATE_OFFLINE 0
#define HID_STATE_WAITING_FOR_CONNECTION 1
#define HID_STATE_IDLE 2
#define HID_STATE_BUSY 3
#define HID_STATE_SENDING_FROM_BUFFER 4
#define HID_STATE_SENDING_KEY_UP 5

// Caracter constants
#define HID_CHAR_ILLEGAL 0xff
#define HID_CHAR_RETURN '\n'
#define HID_CHAR_ESCAPE 27
#define HID_CHAR_TAB '\t'
#define HID_CHAR_BACKSPACE 0x7f

static uint8_t hid_state = HID_STATE_OFFLINE;
static btstack_packet_callback_registration_t hci_event_callback_registration;
static btstack_packet_callback_registration_t sm_event_callback_registration;
static hci_con_handle_t con_handle = HCI_CON_HANDLE_INVALID;

static bool hid_has_boot_report = false;
static bool hid_has_input_report = false;

static const uint8_t adv_data[] = {
	// Flags general discoverable, BR/EDR not supported
	0x02, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
	// Name
	0x12, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'W','s', 'T', 'o', 'B', 'l', 'e', ' ', 'i', 'n', 't', 'e', 'r', 'f', 'a', 'c', 'e',
	// 16-bit Service UUIDs
	0x03, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS, ORG_BLUETOOTH_SERVICE_HUMAN_INTERFACE_DEVICE & 0xff, ORG_BLUETOOTH_SERVICE_HUMAN_INTERFACE_DEVICE >> 8,
	// Appearance (remote),
	0x03, 0x19, 0x80, 0x01,
};
static const uint8_t adv_data_len = sizeof(adv_data);

// from USB HID Specification 1.1, Appendix B.1
static const uint8_t hid_descriptor_boot_mode[] = {
	/*
	 Keyboard
	 */
	0x05, 0x01,					// Usage Page (Generic Desktop)
	0x09, 0x06,					// Usage (Keyboard)
	0xa1, 0x01,					// Collection (Application)

	0x85, 0x01,					 // Report ID 1

	// Modifier byte

	0x75, 0x01,					//	 Report Size (1)
	0x95, 0x08,					//	 Report Count (8)
	0x05, 0x07,					//	 Usage Page (Key codes)
	0x19, 0xE0,					//	 Usage Minimum (Keyboard LeftControl)
	0x29, 0xE7,					//	 Usage Maxium (Keyboard Right GUI)
	0x15, 0x00,					//	 Logical Minimum (0)
	0x25, 0x01,					//	 Logical Maximum (1)
	0x81, 0x02,					//	 Input (Data, Variable, Absolute)

	// Reserved byte

	0x75, 0x01,					//	 Report Size (1)
	0x95, 0x08,					//	 Report Count (8)
	0x81, 0x03,					//	 Input (Constant, Variable, Absolute)

	// LED report + padding

	0x95, 0x05,					//	 Report Count (5)
	0x75, 0x01,					//	 Report Size (1)
	0x05, 0x08,					//	 Usage Page (LEDs)
	0x19, 0x01,					//	 Usage Minimum (Num Lock)
	0x29, 0x05,					//	 Usage Maxium (Kana)
	0x91, 0x02,					//	 Output (Data, Variable, Absolute)

	0x95, 0x01,					//	 Report Count (1)
	0x75, 0x03,					//	 Report Size (3)
	0x91, 0x03,					//	 Output (Constant, Variable, Absolute)

	// Keycodes

	0x95, 0x06,					//	 Report Count (6)
	0x75, 0x08,					//	 Report Size (8)
	0x15, 0x00,					//	 Logical Minimum (0)
	0x25, 0xff,					//	 Logical Maximum (1)
	0x05, 0x07,					//	 Usage Page (Key codes)
	0x19, 0x00,					//	 Usage Minimum (Reserved (no event indicated))
	0x29, 0xff,					//	 Usage Maxium (Reserved)
	0x81, 0x00,					//	 Input (Data, Array)

	0xc0,							// End collection
};
static const uint8_t hid_descriptor_boot_mode_len = sizeof(hid_descriptor_boot_mode);

/**
 * English (US) - lowercase
 */
static const uint8_t hid_keytable_us [] = {
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/*   0-3 */
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',									/*  4-13 */
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',									/* 14-23 */
	'u', 'v', 'w', 'x', 'y', 'z',														/* 24-29 */
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',									/* 30-39 */
	HID_CHAR_RETURN, HID_CHAR_ESCAPE, HID_CHAR_BACKSPACE, HID_CHAR_TAB, ' ',			/* 40-44 */
	'-', '=', '[', ']', '\\', HID_CHAR_ILLEGAL, ';', '\'', 0x60, ',',					/* 45-54 */
	'.', '/', HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,	/* 55-60 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 61-64 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 65-68 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 69-72 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 73-76 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 77-80 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 81-84 */
	'*', '-', '+', '\n', '1', '2', '3', '4', '5',										/* 85-97 */
	'6', '7', '8', '9', '0', '.', 0xa7,													/* 97-100 */
};
static const uint8_t hid_keytable_us_len = sizeof(hid_keytable_us);

/**
 * English (US) - uppercase
 */
static const uint8_t hid_keytable_us_shift[] = {
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/*  0-3  */
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',									/*  4-13 */
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',									/* 14-23 */
	'U', 'V', 'W', 'X', 'Y', 'Z',														/* 24-29 */
	'!', '@', '#', '$', '%', '^', '&', '*', '(', ')',									/* 30-39 */
	HID_CHAR_RETURN, HID_CHAR_ESCAPE, HID_CHAR_BACKSPACE, HID_CHAR_TAB, ' ',			/* 40-44 */
	'_', '+', '{', '}', '|', HID_CHAR_ILLEGAL, ':', '"', 0x7E, '<',						/* 45-54 */
	'>', '?', HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,	/* 55-60 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 61-64 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 65-68 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 69-72 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 73-76 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 77-80 */
	HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL, HID_CHAR_ILLEGAL,				/* 81-84 */
	'*', '-', '+', '\n', '1', '2', '3', '4', '5',										/* 85-97 */
	'6', '7', '8', '9', '0', '.', 0xb1,													/* 97-100 */
};
static const uint8_t hid_keytable_us_shift_len = sizeof(hid_keytable_us_shift);



//--------------------------------------------------
// Websocket variables
//--------------------------------------------------
#define WS_EVENT_TIMER_INTERVAL 24

static const char *ws_http_port = "8000";
static struct mg_serve_http_opts ws_http_server_opts;
static struct mg_mgr ws_mgr;
static struct mg_connection *ws_nc;

// Timer for polling for websocket events
static btstack_timer_source_t ws_event_timer;

// Buffer for modifiers
static uint8_t ws_storage_modifiers[128];
static btstack_ring_buffer_t ws_buffer_modifiers;

// Buffer for keycodes
static uint8_t ws_storage_keycodes[128];
static btstack_ring_buffer_t ws_buffer_keycodes;



//--------------------------------------------------
// Support functions
//--------------------------------------------------

/**
 * Returns if the needle is in the haystack
 * @param needle The integer we are looking for
 * @param haystack The array of integers to search in
 * @param haystack_length The length of the integer array
 */
static bool in_array(uint8_t needle, uint8_t haystack[], uint8_t haystack_length) {
	uint8_t idx;
	for (idx=0; idx<haystack_length; idx++) {
		if (haystack[idx] == needle)
			return true;
		}
	return false;
}



//--------------------------------------------------
// BLE methods
//--------------------------------------------------

/**
 * Setup method for the peripheral.
 */
static void hid_setup(void) {
	l2cap_init();

	// setup le device db
	le_device_db_init();

	// setup SM: Display only
	sm_init();
	sm_set_authentication_requirements(SM_AUTHREQ_SECURE_CONNECTION | SM_AUTHREQ_BONDING);
	sm_set_io_capabilities(IO_CAPABILITY_NO_INPUT_NO_OUTPUT);

	// setup ATT server
	att_server_init(profile_data, NULL, NULL);

	// setup battery service
	battery_service_server_init(100);

	// setup device information service
	device_information_service_server_init();

	// setup HID Device service
	hids_device_init(0, hid_descriptor_boot_mode, hid_descriptor_boot_mode_len);

	// setup advertisements
	uint16_t adv_int_min = 0x0030;
	uint16_t adv_int_max = 0x0030;
	uint8_t adv_type = 0;
	bd_addr_t null_addr;
	memset(null_addr, 0, 6);
	gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0, null_addr, 0x07, 0x00);
	gap_advertisements_set_data(adv_data_len, (uint8_t *)adv_data);
	gap_advertisements_enable(1);

	// register for HCI events
	hci_event_callback_registration.callback = &hid_packet_handler;
	hci_add_event_handler(&hci_event_callback_registration);

	// register for SM events
	sm_event_callback_registration.callback = &hid_packet_handler;
	sm_add_event_handler(&sm_event_callback_registration);

	// register for HIDS
	hids_device_register_packet_handler(hid_packet_handler);
}

/**
 * Changes the peripheral state and logs this change
 * @param new_state The new state the peripheral should take.
 */
static void hid_change_state(int new_state) {
	if (new_state != hid_state) {
		printf("[BLE HID peripheral]: State change from '%d' to '%d'\n", hid_state, new_state);
		hid_state = new_state;
	}
}

/**
 * Used to send data to the peripheral.
 * @param modifier The modifier to send (ALT/CTRL, etc.)
 * @param keycode The keycode in ASCII to send to the peripheral.
 */
static void hid_send(uint8_t modifier, uint8_t keycode) {
	uint8_t report[] = { /* 0xa1, */ modifier, 0, 0, keycode, 0, 0, 0, 0, 0};
	hids_device_send_input_report(con_handle, report, sizeof(report));
}


/**
 * Performs a lookup for a certain character in a provided table and passed back the found keycode.
 * @param character The character to find.
 * @param table The table to look in.
 * @param size The size of the table.
 * @parm keycode The pointer to the keycode to set.
 */
static int hid_lookup_keycode(uint8_t character, const uint8_t * table, int size, uint8_t * keycode) {
	int i;
	for (i=0; i<size; i++) {
		if (table[i] != character) {
			continue;
		}
		*keycode = i;
		return 1;
	}
	return 0;
}

/**
 * Tries to find the modifier and the keycode from a certain character.
 * @param character The character to find.
 * @param keycode The pointer to the keycode to set.
 * @param modifier The pointer to the modifier to set.
 */
static int hid_modifer_and_keycode_from_character(uint8_t character, uint8_t * modifier, uint8_t * keycode) {
	int found;

	// First search lowercase characters
	found = hid_lookup_keycode(character, hid_keytable_us, hid_keytable_us_len, keycode);
	if (found) {
		*modifier = 0;  // none
		return 1;
	}

	// Finally search uppercase characters
	found = hid_lookup_keycode(character, hid_keytable_us_shift, hid_keytable_us_shift_len, keycode);
	if (found) {
		*modifier = 2;  // shift
		return 1;
	}

	return 0;
}

/**
 * Handles received bluetooth packets (callback function).
 * @param packet_type The type of packet we received.
 * @param channel On which channeld did we receive it.
 * @param packet The actual packet.
 * @param size The size of the received packet.
 */
static void hid_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size) {
	UNUSED(channel);
	UNUSED(size);

	if (packet_type != HCI_EVENT_PACKET) {
		return;
	}

	uint16_t conn_interval;

	switch (hci_event_packet_get_type(packet)) {
		case BTSTACK_EVENT_STATE: {
			if ((btstack_event_state_get_state(packet) == HCI_STATE_WORKING) && (hid_state == HID_STATE_OFFLINE)) {
				printf("[BLE HID peripheral]: Online\n");

				// Move to 'waiting for connection state', this will disable clients to send data via websockets
				hid_change_state(HID_STATE_WAITING_FOR_CONNECTION);

				// Turn on websocket server
				websocket_setup();
			}

			if ((btstack_event_state_get_state(packet) == HCI_STATE_HALTING) && (hid_state != HID_STATE_OFFLINE)) {
				hid_change_state(HID_STATE_OFFLINE);
				printf("[BLE HID peripheral]: Offline\n");

				// Turn off websocket server
				websocket_teardown();
			}
			break;
		}
		case SM_EVENT_JUST_WORKS_REQUEST: {
			printf("[BLE HID peripheral]: Pairing method 'Just Works' requested\n");
			sm_just_works_confirm(sm_event_just_works_request_get_handle(packet));
			break;
		}
		case SM_EVENT_PAIRING_COMPLETE: {
			// Required for initial pairing, to enable the websocket server
			switch (sm_event_pairing_complete_get_status(packet)) {
				case ERROR_CODE_SUCCESS: {
					printf("[BLE HID peripheral]: Pairing complete, success\n");

					// Set state to 'idle', this will enable clients to send data via websockets
					hid_change_state(HID_STATE_IDLE);
					break;
				}
				case ERROR_CODE_CONNECTION_TIMEOUT: {
					printf("[BLE HID peripheral]: Pairing failed, timeout\n");
					break;
				}
				case ERROR_CODE_REMOTE_USER_TERMINATED_CONNECTION: {
					printf("[BLE HID peripheral]: Pairing faileed, disconnected\n");
					break;
				}
				case ERROR_CODE_AUTHENTICATION_FAILURE: {
					printf("[BLE HID peripheral]: Pairing failed, reason = %u\n", sm_event_pairing_complete_get_reason(packet));
					break;
				}
			}
			break;
		}
		case HCI_EVENT_LE_META: {
			switch (hci_event_le_meta_get_subevent_code(packet)) {
				// Required for connections after pairing completed (e.g. turn off/turn on device)
				case HCI_SUBEVENT_LE_CONNECTION_COMPLETE: {
					con_handle = hids_subevent_input_report_enable_get_con_handle(packet);

					// print connection parameters (without using float operations)
					conn_interval = hci_subevent_le_connection_complete_get_conn_interval(packet);
					printf("[BLE HID peripheral]: Client connection complete:\n");
					printf("[BLE HID peripheral]: - Connection Interval: %u.%02u ms\n", conn_interval * 125 / 100, 25 * (conn_interval & 3));
					printf("[BLE HID peripheral]: - Connection Latency: %u\n", hci_subevent_le_connection_complete_get_conn_latency(packet));

					// request min con interval 15 ms for iOS 11+
					gap_request_connection_parameter_update(con_handle, 12, 12, 0, 0x0048);
					break;
				}
				case HCI_SUBEVENT_LE_CONNECTION_UPDATE_COMPLETE: {
					// print connection parameters (without using float operations)
					conn_interval = hci_subevent_le_connection_update_complete_get_conn_interval(packet);
					printf("[BLE HID peripheral]: Client connection update:\n");
					printf("[BLE HID peripheral]: - Connection Interval: %u.%02u ms\n", conn_interval * 125 / 100, 25 * (conn_interval & 3));
					printf("[BLE HID peripheral]: - Connection Latency: %u\n", hci_subevent_le_connection_update_complete_get_conn_latency(packet));
					break;
				}
			}
			break;
		}
		case HCI_EVENT_HIDS_META: {
			switch (hci_event_hids_meta_get_subevent_code(packet)) {
				case HIDS_SUBEVENT_INPUT_REPORT_ENABLE: {
					if (hid_has_input_report == false) {
						hid_has_input_report = true;

						con_handle = hids_subevent_input_report_enable_get_con_handle(packet);
						printf("[BLE HID peripheral]: Report Characteristic Subscribed %u\n", hids_subevent_input_report_enable_get_enable(packet));

						// Set state to 'idle', this will enable clients to send data via websockets
						hid_change_state(HID_STATE_IDLE);
					}
					break;
				}
				case HIDS_SUBEVENT_BOOT_KEYBOARD_INPUT_REPORT_ENABLE: {
					if (hid_has_boot_report == false) {
						hid_has_boot_report = true;

						con_handle = hids_subevent_boot_keyboard_input_report_enable_get_con_handle(packet);
						printf("[BLE HID peripheral]: Boot Keyboard Characteristic Subscribed %u\n", hids_subevent_boot_keyboard_input_report_enable_get_enable(packet));
					}
					break;
				}
				case HIDS_SUBEVENT_PROTOCOL_MODE: {
					printf("[BLE HID peripheral]: Protocol Mode: %s mode\n", hids_subevent_protocol_mode_get_protocol_mode(packet) ? "Report" : "Boot");
					break;
				}
				case HIDS_SUBEVENT_CAN_SEND_NOW: {
					printf("[BLE HID peripheral]: HIDS event can send now received:\n");
					switch (hid_state) {
						case HID_STATE_BUSY: {
							uint32_t num_bytes_read;
							uint8_t ws_send_modifier = 0;
							uint8_t ws_send_keycode = 0;

							// Try to read modifier from buffer
							btstack_ring_buffer_read(&ws_buffer_modifiers, &ws_send_modifier, 1, &num_bytes_read);
							if (num_bytes_read == 0) {
								hid_change_state(HID_STATE_IDLE);
								break;
							}

							// If that succeeds we also read the keycode to send
							btstack_ring_buffer_read(&ws_buffer_keycodes, &ws_send_keycode, 1, &num_bytes_read);

							// And set the state to 'sending'
							printf("[BLE HID peripheral]: - Sending modifier: %u\n", ws_send_modifier);
							printf("[BLE HID peripheral]: - Sending keycode: %u\n", ws_send_keycode);
							hid_send(ws_send_modifier, ws_send_keycode);

							// Wait for callback to send key-up event
							hid_change_state(HID_STATE_SENDING_KEY_UP);
							hids_device_request_can_send_now_event(con_handle);
							break;
						}
						case HID_STATE_SENDING_KEY_UP: {
							printf("[BLE HID peripheral]: - Sending keyup event\n");
							hid_send(0, 0);

							// In case we have still bytes available, make the call so that we will process the next ones asap.
							if (btstack_ring_buffer_bytes_available(&ws_buffer_modifiers)) {
								hid_change_state(HID_STATE_BUSY);
								hids_device_request_can_send_now_event(con_handle);
							} else {
								hid_change_state(HID_STATE_IDLE);
							}
							break;
						}
					}
					break;
				}
			}
			break;
		}
		case HCI_EVENT_DISCONNECTION_COMPLETE: {
			if (hid_state > HID_STATE_OFFLINE) {
				con_handle = HCI_CON_HANDLE_INVALID;
				printf("[BLE HID peripheral]: Client disconnected\n");

				// Reset HID report
				hid_has_boot_report = false;
				hid_has_input_report = false;

				// Move to 'waiting for connection state', this will disable clients to send data via websockets
				hid_change_state(HID_STATE_WAITING_FOR_CONNECTION);
			}
			break;
		}
	}
}



//--------------------------------------------------
// Websocket functions
//--------------------------------------------------

/**
 * Setup method for the WebSocket server
 */
static void websocket_setup(void) {
	mg_mgr_init(&ws_mgr, NULL);
	ws_nc = mg_bind(&ws_mgr, ws_http_port, websocket_event_handler);
	mg_set_protocol_http_websocket(ws_nc);
	ws_http_server_opts.document_root = "web_debug";	// Serve current directory
	ws_http_server_opts.enable_directory_listing = "yes";

	// Debug
	printf("[WebSocket server]: Started on port %s\n", ws_http_port);

	// Fire once-shot polling timer
	ws_event_timer.process = &websocket_event_poll;
	btstack_run_loop_set_timer(&ws_event_timer, WS_EVENT_TIMER_INTERVAL);
	btstack_run_loop_add_timer(&ws_event_timer);
}

/**
 * Method which handles the websocket connection polling and message handling
 */
static void websocket_event_poll(btstack_timer_source_t * ts) {
	mg_mgr_poll(&ws_mgr, 100);

	// Keep running this timer until we are ready
	btstack_run_loop_set_timer(ts, WS_EVENT_TIMER_INTERVAL);
	btstack_run_loop_add_timer(ts);
}

/**
 * Event handler function, is called when a static file is requested, a client joins, a client sends a message and when a client disconnects.
 * @param mg_connection The connection initiating the event
 * @param ev The event ID
 * @param ev_data The data of the event
 */
static void websocket_event_handler(struct mg_connection *nc, int ev, void *ev_data) {
	// In case we get an HTTP request, we always serve it
	if (ev == MG_EV_HTTP_REQUEST) {
		mg_serve_http(nc, (struct http_message *) ev_data, ws_http_server_opts);
		return;
	}

	// In all other cases it should be a websocket connection
	bool isWsMessage = (nc->flags & MG_F_IS_WEBSOCKET);
	if (!isWsMessage) {
		return;
	}

	switch (ev) {
		case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
			// Client connected, tell everybody.
			websocket_broadcast(nc, mg_mk_str("connected."), true);
			break;
		}
		case MG_EV_WEBSOCKET_FRAME: {
			struct websocket_message *wm = (struct websocket_message *) ev_data;
			char buffer[wm->size];
			sprintf(buffer, "%.*s", (uint8_t) wm->size, (char *) wm->data);

			// Broadcast what we recieved
			char debug[512];
			sprintf(debug, "sent: '%s'", buffer);
			websocket_broadcast(nc, mg_mk_str(debug), true);

			// Initialize variables
			bool valid_input = false;
			int modifier = 0;
			int keycode = 0;
			uint8_t modifier_ = 0;
			uint8_t keycode_ = 0;

			// In case we received just 1 char
			if (strlen(buffer) == 1) {
				// Try to lookup the character int they keymap(s).
				if (hid_modifer_and_keycode_from_character(buffer[0], &modifier_, &keycode_) == 1) {
					valid_input = true;
				}
			} else {
				// In other cases we allow a max length of 7 (<modifier:3>,<keycode:3>)
				if (strlen(buffer) <= 7) {
					// Is there a comma present?
					if (strchr(buffer, ',') != NULL) {
						// Parse modifier & keycode
						valid_input = (sscanf(buffer, "%d,%d", &modifier, &keycode) == 2);

						// Check if the modifier was valid
						uint8_t allowed_modifiers[9] = {0, 1, 2, 4, 8, 16, 32, 64, 128};
						if (valid_input && !in_array(modifier, allowed_modifiers, 9)) {
							valid_input = false;
						}
					} else {
						// Parse modifier & keycode
						valid_input = (sscanf(buffer, "%d", &keycode) == 1);
					}

					// Check keycode
					if (keycode > 255) {
						valid_input = false;
					}

					if (valid_input) {
						modifier_ = modifier;
						keycode_ = keycode;
					}
				}
			}

			// Check to see if we have valid input
			if (!valid_input) {
				websocket_broadcast(nc, mg_mk_str("- Hold up! Invalid message detected, please check the documentation."), false);
			} else {
				// Broadcast
				sprintf(debug, "- Found modifier '%d' and keycode '%d'.", modifier_, keycode_);
				websocket_broadcast(nc, mg_mk_str(debug), false);

				if (hid_state == HID_STATE_WAITING_FOR_CONNECTION) {
					websocket_broadcast(nc, mg_mk_str("- Hold up! No client is currently paired, please check the documentation."), false);
				} else {
					// Write data to buffers
					btstack_ring_buffer_write(&ws_buffer_modifiers, &modifier_, 1);
					btstack_ring_buffer_write(&ws_buffer_keycodes, &keycode_, 1);

					// Call event to send data
					if (hid_state == HID_STATE_IDLE) {
						// We have a winner!
						hid_change_state(HID_STATE_BUSY);

						// Send the key as soon as possible.
						hids_device_request_can_send_now_event(con_handle);
					}
				}
			}
			break;
		}
		case MG_EV_CLOSE: {
			// Client disconnected, tell everybody.
			websocket_broadcast(nc, mg_mk_str("disconnected."), true);
			break;
		}
	}
}

/**
 * Broadcast a message to all connected clients. This is mainly used for debug logging.
 * @param mg_connection The connection initiating the broadcast
 * @param mg_str The message we want to broadcast
 * @param send_to_all If false, only sends to the originating client
 */
static void websocket_broadcast(struct mg_connection *nc, const struct mg_str msg, bool send_to_all) {
	char addr[32];
	mg_sock_addr_to_str(&nc->sa, addr, sizeof(addr), MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);

	// Create string to send
	char buf[1024];
	snprintf(buf, sizeof(buf), "%s %.*s", addr, (uint8_t) msg.len, msg.p);

	// Local echo
	printf("[WebSocket server]: %s\n", buf);

	// Send to all connected clients
	struct mg_connection *c;
	for (c = mg_next(nc->mgr, NULL); c != NULL; c = mg_next(nc->mgr, c)) {
		// If we are just sending a reply to one client, don't send it to all.
		if ((send_to_all == false) && (c != nc)) {
			continue;
		}
		mg_send_websocket_frame(c, WEBSOCKET_OP_TEXT, buf, strlen(buf));
	}
}

/**
 * Destructor for the WebSocket server
 */
static void websocket_teardown(void) {
	websocket_broadcast(ws_nc, mg_mk_str("Server going down!"), true);
	mg_mgr_free(&ws_mgr);
	printf("[WebSocket server]: Stopped.\n");
}



//--------------------------------------------------
// Main method
//--------------------------------------------------
uint8_t btstack_main(void) {
	// Setup BLE peripheral
	hid_setup();

	// Initialize ringbuffers
	btstack_ring_buffer_init(&ws_buffer_modifiers, ws_storage_modifiers, sizeof(ws_storage_modifiers));
	btstack_ring_buffer_init(&ws_buffer_keycodes, ws_storage_keycodes, sizeof(ws_storage_keycodes));

	// Turn on Bluetooth Radio
	hci_power_control(HCI_POWER_ON);

	return 0;
}
