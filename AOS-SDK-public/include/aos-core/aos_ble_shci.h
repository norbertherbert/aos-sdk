/*
 * \file aos_ble_shci.h
 *
 * \brief BLE Control transport access (SHCI)
 */
#pragma once


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \defgroup aos_ble_shci BLE Control transport access
 *
 * \addtogroup aos_ble_shci
 * @{
 */

/*!
 * \enum aos_ble_c2_clock_t
 *
 * \brief System clock switch type to be done by the CPU2
 */
typedef enum {
	aos_ble_c2_clock_hse_to_pll = 0,			//!< Switch from HSE to PLL
	aos_ble_c2_clock_pll_on_to_hse  = 1,		//!< Switch from PLL to HSE and keep PLL on
	aos_ble_c2_clock_pll_off_to_hse =2,			//!< Switch from PLL to HSE and shutdown the PLL
} aos_ble_c2_clock_t;

/*!
 * \fn  void aos_ble_shci_init(void)
 *
 * \brief Initialize the control transport with the M0+
 *
 * \note Called by AOS only
 */
void aos_ble_shci_init( void );

/*!
 * \fn bool aos_ble_shci_set_c2_clock(aos_ble_c2_clock_t clock)
 *
 * \brief Instruct the CPU2 to switch the system clock
 *
 * \param clock Clock type to switch to
 *
 * \return True is correct completion, false otherwise
 *
 * \note Called by AOS only
 */
bool aos_ble_shci_set_c2_clock(aos_ble_c2_clock_t clock);

/*!
 * \fn bool aos_ble_shci_cpu2_started(void);
 *
 * \brief Check whether the CPU has started.
 *
 * \return True if the CPU has started,
 *
 * \note Called by AOS only
 */
bool aos_ble_shci_cpu2_started(void);

/*! @}*/
#ifdef __cplusplus
}
#endif
