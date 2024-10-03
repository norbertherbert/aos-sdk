/*!
 * \file aos_otp.h - One-Time Programmable memory interface.
 *
 * \brief This file implements the API for reading and writing the OTP memory.
 *
 * Copyright (C) 2023, Abeeway (www.abeeway.com). All Rights Reserved.
 *
 */
#pragma once

#include <sys/_stdint.h>

/*!
 * \brief Define the supported data type
 */
typedef enum {
    aos_otp_type_raw_data,      //!< 6 bytes, user defined data
    aos_otp_type_hse_trim,      //!< HSE trim value (6 bits)
    aos_otp_type_mac_address_1,	//!< A MAC address (ie, for storing the BLE address)
	aos_otp_type_mac_address_2,	//!< Another MAC address
	aos_otp_type_hw_version,    //!< Module hardware version
}  aos_otp_type_t;

/*!
 * \brief Data stored in the OTP memory
 */
typedef union {
    uint8_t raw_data[6];			//!< User defined data (6 bytes)
    uint8_t hse_trim:6;				//!< HSE trim value (6 bits). Set by the module provider.
    uint8_t mac_address[6];			//!< MAC address (6 bytes)
    uint8_t hw_version;				//!< Module hardware version. Set by the module provider.
} __attribute__((packed)) aos_otp_data_t;

/*!
 * \fn int aos_otp_read(const aos_otp_type_t type, aos_otp_data_t *data);
 *
 * \brief Read an aos_otp_data_t value from OTP memory.
 *
 * \param type - enumerated value indicating the value type
 * \param data - pointer to an aos_otp_data_t storage location.
 *
 * \return 0 on success, negative value on error (ie, no such value stored).
 *
 * \note If a same variable type has been written several time, the function returns
 * the last value written.
 *
 */
int aos_otp_read(const aos_otp_type_t type, aos_otp_data_t *data);

/*!
 * \fn int aos_otp_write(const aos_otp_type_t type, const aos_otp_data_t *data);
 *
 * \brief Write an aos_otp_data_t value to OTP memory.
 *
 * \param type - enumerated value indicating the value type
 * \param data - pointer to an aos_otp_data_t storage location.
 *
 * \return 0 on success, negative value on error (ie, OTP storage exhausted).
 *
 * \note It is possible to write a value with the same type several times.
 * In this case, a new OTP location is written. Note that the max value
 * of OTP elements is 128.
 */
int aos_otp_write(const aos_otp_type_t type, const aos_otp_data_t *data);

/*!
 * \fn int int aos_otp_free_entries(void);
 *
 * \brief Check the number of free OTP entries.
 *
 * \return the number of available OTP entries.
 *
 */
int aos_otp_free_entries(void);

