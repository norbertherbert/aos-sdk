/*!
 * \file srv_ble_connectivity.h
 *
 * \brief BLE connectivity service
 */
#pragma once

/*!
 * \defgroup srv_ble_cnx BLE connectivity service
 *
 * \addtogroup srv_ble_cnx
 * @{
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Start the advertisement for connectivity
 *
 * \return The status of the operation
 */
aos_result_t srv_ble_connectivity_start(void);

/*!
 * \brief Stop the advertisement for connectivity
 *
 * \return The status of the operation
 */
aos_result_t srv_ble_connectivity_stop(void);

/*!
 * \fn uint64_t srv_ble_connectivity_get_power_consumption(void)
 *
 * \brief return connectivity power consumption.
 *
 * \return value of the power consumption in uAh
 */
uint64_t srv_ble_connectivity_get_power_consumption(void);

/*!
 * \fn void srv_ble_connectivity_clear_consumption(void)
 *
 * \brief reset the connectivity power consumption.
 */
void srv_ble_connectivity_clear_consumption(void);

/*! @}*/
#ifdef __cplusplus
}
#endif
