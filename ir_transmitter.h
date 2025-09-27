/**
 * @file ir_transmitter.h
 * @brief Provides a low-level interface for transmitting infrared (IR) commands.
 *
 * This driver is intended to run on the ESP32 microcontroller. It abstracts the
 * complexities of generating the 38 kHz carrier frequency and timing the pulses
 * required for various IR protocols, such as NEC[cite: 433]. It is designed to be
 * controlled by a higher-level system that provides the specific codes to transmit.
 */

#ifndef IR_TRANSMITTER_H
#define IR_TRANSMITTER_H

#include <stdint.h>

/**
 * @brief Initializes the IR transmitter.
 *
 * Configures the specified GPIO pin as an output and sets up the necessary
 * hardware timers and PWM peripherals on the ESP32 to generate the 38 kHz
 * carrier signal[cite: 440]. This must be called before any transmission functions.
 *
 * @param gpio_pin The ESP32 GPIO pin number connected to the IR LED driver circuit.
 */
void ir_transmitter_init(uint8_t gpio_pin);

/**
 * @brief Transmits a 32-bit command using the NEC IR protocol.
 *
 * This function takes a 32-bit hexadecimal code and transmits it according to
 * the NEC protocol specification. It handles the generation of the leader pulse,
 * address and command bits, and the final stop bit[cite: 434, 435].
 *
 * @param nec_code The 32-bit NEC command to be sent (e.g., 0xE0E0E01F for Volume Up)[cite: 429].
 */
void ir_transmitter_send_nec(uint32_t nec_code);

/**
 * @brief Deinitializes the IR transmitter.
 *
 * Releases the GPIO pin and disables the hardware timers used for IR generation.
 * This can be used to free up resources when IR functionality is no longer needed.
 */
void ir_transmitter_deinit(void);

#endif // IR_TRANSMITTER_H