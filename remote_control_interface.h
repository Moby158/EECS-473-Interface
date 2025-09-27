/**
 * @file remote_control_interface.h
 * @brief High-level interface for sending remote control commands to the IR transmitter module.
 *
 * This interface runs on the host processor (Raspberry Pi CM5) and communicates
 * with the dedicated IR transmitter microcontroller (ESP32). It provides a simple,
 * abstract way to send commands like "Volume Up" without dealing with the
 * low-level communication protocol (e.g., UART) or the specific IR codes[cite: 496, 500].
 */

#ifndef REMOTE_CONTROL_INTERFACE_H
#define REMOTE_CONTROL_INTERFACE_H

#include <stdbool.h>

/**
 * @brief Enumeration of supported television commands.
 * These abstract commands will be translated into specific IR codes by the ESP32.
 */
typedef enum {
    TV_CMD_VOLUME_UP,
    TV_CMD_VOLUME_DOWN,
    TV_CMD_CHANNEL_UP,
    TV_CMD_CHANNEL_DOWN,
    TV_CMD_SELECT,
    TV_CMD_IDLE // Represents no action
} tv_command_t;

/**
 * @brief Initializes the communication channel to the IR transmitter module.
 *
 * Opens and configures the specified serial port (e.g., UART) for communication
 * with the ESP32. This must be called before sending any commands.
 *
 * @param device_path A string representing the path to the serial device
 * (e.g., "/dev/ttyS0").
 * @return true on successful initialization, false otherwise.
 */
bool remote_init(const char* device_path);

/**
 * @brief Sends a command to the IR transmitter module.
 *
 * Takes a high-level command from the tv_command_t enum, translates it into
 * a byte or message format understood by the ESP32, and sends it over the
 * initialized communication channel.
 *
 * @param command The command to send (e.g., TV_CMD_VOLUME_UP).
 * @return true if the command was sent successfully, false otherwise.
 */
bool remote_send_command(tv_command_t command);

/**
 * @brief Closes the communication channel.
 *
 * Releases the handle to the serial port. Should be called upon application exit.
 */
void remote_close(void);

#endif // REMOTE_CONTROL_INTERFACE_H