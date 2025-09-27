/**
 * @file ads1299_driver.h
 * @brief Header file for the ADS1299 EEG AFE driver.
 *
 * This file defines the C/C++ interface for initializing, configuring,
 * and reading data from the Texas Instruments ADS1299 Analog Front-End
 * for EEG applications. It assumes an SPI interface is used for communication.
 */

#ifndef ADS1299_DRIVER_H
#define ADS1299_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

// Number of channels supported by the ADS1299
#define ADS1299_NUM_CHANNELS 8

/**
 * @brief Structure to hold a single sample of EEG data from all channels.
 * Data is represented as 24-bit signed integers.
 */
typedef struct {
    int32_t status; // Status bits from the device
    int32_t channel_data[ADS1299_NUM_CHANNELS]; // EEG data for each channel
} ads1299_sample_t;

/**
 * @brief Initializes the ADS1299 device.
 *
 * This function performs the initial setup sequence for the ADS1299,
 * including resetting the device, sending the SDATAC command, and setting
 * default configurations. It must be called before any other driver function.
 *
 * @param spi_handle A handle or pointer to the platform-specific SPI peripheral.
 * @return true if initialization was successful, false otherwise.
 */
bool ads1299_init(void* spi_handle);

/**
 * @brief Starts continuous data conversion.
 *
 * Sends the START command to the ADS1299 to begin data acquisition.
 * The DRDY (Data Ready) pin will begin to pulse when new data is available.
 *
 * @return true if the command was sent successfully, false otherwise.
 */
bool ads1299_start_conversion(void);

/**
 * @brief Stops data conversion.
 *
 * Sends the STOP command to the ADS1299 to halt data acquisition.
 *
 * @return true if the command was sent successfully, false otherwise.
 */
bool ads1299_stop_conversion(void);

/**
 * @brief Reads a single sample (all channels) from the ADS1299.
 *
 * This function should be called when the DRDY pin indicates that new
 * data is available. It reads the status word and the data for all 8 channels.
 *
 * @param[out] sample A pointer to an ads1299_sample_t struct to store the read data.
 * @return true if data was read successfully, false otherwise.
 */
bool ads1299_read_sample(ads1299_sample_t* sample);

/**
 * @brief Configures a single channel on the ADS1299.
 *
 * @param channel The channel number to configure (1-8).
 * @param gain The gain setting for the channel (e.g., 1, 2, 4, 6, 8, 12, 24).
 * @param input_mux_setting The input multiplexer setting for the channel.
 * @param is_enabled true to power on the channel, false to power it down.
 * @return true if configuration was successful, false otherwise.
 */
bool ads1299_configure_channel(uint8_t channel, uint8_t gain, uint8_t input_mux_setting, bool is_enabled);

#endif // ADS1299_DRIVER_H
