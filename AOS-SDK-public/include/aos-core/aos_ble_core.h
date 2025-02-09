/*!
 * \file aos_ble_core.h
 *
 * \brief BLE core related API (connectivity, advertisement, scan ...)
 *
 * \copyright 2022, Abeeway (www.abeeway.com). All Rights Reserved.
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "ble.h"
#include "tl.h"
#include "core_cm4.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "hci_tl.h"
#include "ble_types.h"
#include "stdbool.h"
#include "aos_common.h"
#include "aos_ble_common.h"
#include "task.h"



/*!
 * \defgroup aos_ble_core BLE core
 *
 * \addtogroup aos_ble_core
 * @{
 */

#define AOS_BLE_CORE_TX_POWER_LEVEL_MIN 0			//!< Min index of tx power level
#define AOS_BLE_CORE_TX_POWER_LEVEL_MAX 31			//!< Max index of tx power level

#define ABS(x) ((x)>0? (x):-(x))		            //!< Macro to get the absolute value of the input parameter


/* Exported types ------------------------------------------------------------*/
/*!
 * \struct aos_ble_core_security_params_t
 *
 * \brief security parameters structure.
 */
typedef struct {
	uint8_t io_capability;                 //!< IO capability of the device
	uint8_t mitm_mode;                     //!< Authentication requirement of the device Man In the Middle protection required?
	uint8_t bonding_mode;                  //!< Bonding mode of the device
	uint8_t use_fixed_pin;                 //!< 0 implies use fixed pin and 1 implies request for passkey
	uint8_t encryption_key_size_min;       //!< Minimum encryption key size requirement
	uint8_t encryption_key_size_max;       //!< Maximum encryption key size requirement
	uint32_t fixed_pin;                    //!< Fixed pin to be used in the pairing process if use_fixed_pin is set to 1
	uint8_t sc_support;                    //!< Secure connections support
	uint8_t identity_address_type;         //!< Identity address type, PUBLIC or RANDOM
	uint8_t keypress_notification_support; //!< Keypress notification support
} aos_ble_core_security_params_t;

/*!
 * \typedef void aos_ble_core_notif_callback_t(void *pckt)
 *
 * \brief BLE notification callback type, used to dispatch BLE notifications
 *
 * \param pckt packet received
 */
typedef void (*aos_ble_core_notif_callback_t)(void *pckt);

/* Exported functions ---------------------------------------------*/

/*!
 * \fn void aos_ble_core_app_init(uint8_t ble_role)
 *
 * \brief BLE Initialization API
 *
 * \param ble_role Bitmap, BLE role needed to initialize BLE (observer/peripheral ...)
 */
void aos_ble_core_app_init(uint8_t ble_role);

/*!
 * \fn const uint8_t* aos_ble_core_get_bd_address(void)
 *
 * \brief Get BLE Device address
 *
 * \return pointer to the BLE MAC address
 */
const uint8_t* aos_ble_core_get_bd_address(void);

/*!
 * \fn bool aos_ble_core_set_tx_power_level(uint8_t tx_power_level)
 *
 * \brief Set TX POWER LEVEL,
 *
 * \param tx_power_level: Power amplifier output level. Output power is indicative and
 *        depends on the PCB layout and associated components. Here the values
 *        are given at the STM32WB output.
 *        Values:
 *        - 0x00: -40 dBm	- 0x01: -20.85 dBm	- 0x02: -19.75 dBm	- 0x03: -18.85 dBm	- 0x04: -17.6 dBm
 *        - 0x05: -16.5 dBm	- 0x06: -15.25 dBm	- 0x07: -14.1 dBm	- 0x08: -13.15 dBm	- 0x09: -12.05 dBm
 *        - 0x0A: -10.9 dBm	- 0x0B: -9.9 dBm	- 0x0C: -8.85 dBm	- 0x0D: -7.8 dBm	- 0x0E: -6.9 dBm
 *        - 0x0F: -5.9 dBm	- 0x10: -4.95 dBm	- 0x11: -4 dBm		- 0x12: -3.15 dBm	- 0x13: -2.45 dBm
 *        - 0x14: -1.8 dBm	- 0x15: -1.3 dBm	- 0x16: -0.85 dBm	- 0x17: -0.5 dBm	- 0x18: -0.15 dBm
 *        - 0x19: 0 dBm		- 0x1A: +1 dBm		- 0x1B: +2 dBm		- 0x1C: +3 dBm		- 0x1D: +4 dBm
 *        - 0x1E: +5 dBm	- 0x1F: +6 dBm
 *
 * \return result status true/false
 */
bool aos_ble_core_set_tx_power_level(uint8_t tx_power_level);

/*!
 * \fn bool aos_ble_core_get_tx_power_dbm(uint8_t pow_level, int16_t * pow_dbm)
 *
 * \brief Convert TX POWER from LEVEL to 0.01dBm unit,
 *
 * \param pow_level the tx power level
 *
 * \param pow_dbm The output value of the power in 0.01dBm
 *
 * \return status success/failure
 */
bool aos_ble_core_get_tx_power_dbm(uint8_t pow_level, int16_t * pow_dbm);

/*!
 * \fn void aos_ble_core_hci_notify_asynch_evt(void* pdata)
 *
 * \brief  This callback is called from either
 *          - IPCC RX interrupt context
 *          - hci_user_evt_proc() context.
 *          - hci_resume_flow() context
 *         It requests hci_user_evt_proc() to be executed.
 *
 * \param  pdata Packet or event pointer
 *
 * \return None
 */
void aos_ble_core_hci_notify_asynch_evt(void* pdata);

/*!
 * \fn void aos_ble_core_hci_cmd_resp_release(uint32_t flag)
 *
 * \brief  This function is called when an ACI/HCI command response is received from the CPU2.
 *         A weak implementation is available in hci_tl.c based on polling mechanism
 *         The user may re-implement this function in the application to improve performance :
 *         - It may use UTIL_SEQ_SetEvt() API when using the Sequencer
 *         - It may use a semaphore when using cmsis_os interface
 *
 * \param  flag: Release flag
 *
 * \return None
 */
void aos_ble_core_hci_cmd_resp_release(uint32_t flag);

/*!
 * \fn void aos_ble_core_hci_cmd_resp_wait(uint32_t timeout)
 *
 * \brief  This function is called when an ACI/HCI command is sent to the CPU2 and the response is waited.
 *         It is called from the same context the HCI command has been sent.
 *         It shall not return until the command response notified by aos_ble_core_hci_cmd_resp_release() is received.
 *         A weak implementation is available in hci_tl.c based on polling mechanism
 *         The user may re-implement this function in the application to improve performance :
 *         - It may use UTIL_SEQ_WaitEvt() API when using the Sequencer
 *         - It may use a semaphore when using cmsis_os interface
 *
 * \param  timeout: Waiting timeout
 *
 * \return None
 */
void aos_ble_core_hci_cmd_resp_wait(uint32_t timeout);

/*!
 * \fn void aos_ble_core_get_ble_firmware_version(aos_ble_core_fw_version_t *ble_version)
 *
 * \brief get stack and FUS firmwares version,
 *
 * \param ble_version output the stack and fus version
 *
 */
void aos_ble_core_get_ble_firmware_version(aos_ble_core_fw_version_t *ble_version);

/*!
 * \fn void aos_ble_core_set_scan_callback(aos_ble_core_notif_callback_t cb)
 *
 * \brief Set callback function for scan service
 *
 * \param cb function to set.
 *
 */
void aos_ble_core_set_scan_callback(aos_ble_core_notif_callback_t cb);

/*!
 * \fn void aos_ble_core_set_connectivity_callback(aos_ble_core_notif_callback_t cb)
 *
 * \brief Set callback function for connectivity service
 *
 * \param cb function to set.
 *
 */
void aos_ble_core_set_connectivity_callback(aos_ble_core_notif_callback_t cb);

/*!
 * \fn void aos_ble_core_set_app_callback(aos_ble_core_notif_callback_t cb)
 *
 * \brief Set callback function for application
 *
 * \param cb function to set.
 *
 */
void aos_ble_core_set_app_callback(aos_ble_core_notif_callback_t cb);

/*!
 * \fn bool aos_ble_core_set_authentication_requirement(aos_ble_core_security_params_t ble_security_param)
 *
 * \brief Set BLE authentication requirement,
 * The new Authentication requirement will take effect for new bonded devices,
 * already bonded devices are not removed automatically.
 *
 * \param ble_security_param BLE security parameters.
 *
 * \return success/failure
 *
 */
bool aos_ble_core_set_authentication_requirement(aos_ble_core_security_params_t ble_security_param);

/* USER CODE END EF */

/*! @}*/
#ifdef __cplusplus
}
#endif
