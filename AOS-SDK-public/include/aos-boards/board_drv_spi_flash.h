/*!
 * \file board_drv_spi_flash.h
 *
 * \brief SPI flash driver
 */
#pragma once

#include "aos_gpio.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \defgroup board_drv_spi_flash ADC driver
 *
 * \addtogroup board_drv_spi_flash
 * @{
 */

/*!
 * Common definitions
 */
#define SPI_FLASH_PAGE_SIZE					0x100		//!< Page size for all SPI flash
#define SPI_FLASH_SECTOR_SIZE				0x1000		//!< Sector size for all SPI flash
#define SPI_FLASH_BLOCK_SIZE				0x10000		//!< block size for all SPI flash
#define SPI_FLASH_HALF_BLOCK_SIZE			0x8000		//!< Half of block for all SPI flash

/*!
 * \brief Known vendor identifiers
 */
typedef enum {
	board_drv_spi_flash_manuf_id_none = 0,			//!< Unknown
	board_drv_spi_flash_manuf_id_spansion,			//!< SPANSION
	board_drv_spi_flash_manuf_id_fujitsu,			//!< FUJITSU
	board_drv_spi_flash_manuf_id_eon,				//!< EON
	board_drv_spi_flash_manuf_id_atmel,				//!< ATMEL
	board_drv_spi_flash_manuf_id_micron,			//!< MICRON
	board_drv_spi_flash_manuf_id_amic,				//!< AMIC
	board_drv_spi_flash_manuf_id_sanyo,				//!< SANYO
	board_drv_spi_flash_manuf_id_intel,				//!< Intel
	board_drv_spi_flash_manuf_id_issi,				//!< ISSI
	board_drv_spi_flash_manuf_id_fudan,				//!< FUDAN
	board_drv_spi_flash_manuf_id_hunday,			//!< HUNDAY
	board_drv_spi_flash_manuf_id_puya,				//!< PUYA
	board_drv_spi_flash_manuf_id_emst,				//!< EMST
	board_drv_spi_flash_manuf_id_sst,				//!< SST
	board_drv_spi_flash_manuf_id_macronix,			//!< MACRONIX
	board_drv_spi_flash_manuf_id_gigadevice,		//!< GIGABIT
	board_drv_spi_flash_manuf_id_winbond,			//!< WINBOND
	board_drv_spi_flash_manuf_id_count,				//!< Number of known vendors
} board_drv_spi_flash_manuf_id_t;

/*!
 * \brief Supported flash size
 */
typedef enum {
	board_drv_spi_flash_size_none = 0,		//!< Size unknown
	board_drv_spi_flash_size_1mbit,			//!< Size: 128 kB
	board_drv_spi_flash_size_2mbit,			//!< Size: 256 kB
	board_drv_spi_flash_size_4mbit,			//!< Size: 512 kB
	board_drv_spi_flash_size_8mbit,			//!< Size: 1 MB
	board_drv_spi_flash_size_16mbit,		//!< Size: 2 MB
	board_drv_spi_flash_size_32mbit,		//!< Size: 4 MB
	board_drv_spi_flash_size_64mbit,		//!< Size: 8 MB
	board_drv_spi_flash_size_128mbit,		//!< Size: 16 MB
	board_drv_spi_flash_size_count			//!< Number of supported sizes
} board_drv_spi_flash_size_t;

/*!
 * \brief Flash erase action
 */
typedef enum {
	board_drv_spi_erase_type_sector = 0,	//!< Erase a sector (4 k bytes). Address align on 4kB.
	board_drv_spi_erase_type_half_block,	//!< Erase a half of a block (32 k bytes). Address align on 32kB.
	board_drv_spi_erase_type_block,			//!< Erase a block (64 k bytes). Address align on 64kB.
	board_drv_spi_erase_type_chip,			//!< Erase the chip. No address needed
}board_drv_spi_erase_type_t;

/*!
 * \brief Flash information
 */
typedef struct {
	uint8_t manuf_id_raw;							//!< Manufacturer identifier in raw format
	board_drv_spi_flash_manuf_id_t manuf_id;		//!< Manufacturer identifier (known)
	uint8_t dev_id;									//!< Device identifier
	board_drv_spi_flash_size_t size;				//!< flash size
	uint32_t page_count;							//!< Number of pages
	uint32_t sector_count;							//!< Number of sectors
	uint32_t block_count;							//!< Number of block
} board_drv_spi_flash_info_t;

/*!
 * \brief Open the external SPI flash driver
 *
 * \param cs_gpio GPIO acting as chip select (NSS) for the SPI flash
 *
 * \return Result of the operation
 */
aos_result_t board_drv_spi_flash_open(aos_gpio_id_t cs_gpio);

/*!
 * \brief Get information about the external flash
 *
 * \param info Storage area for the information
 *
 * \return Result of the operation
 */
aos_result_t board_drv_spi_flash_get_info(board_drv_spi_flash_info_t* info);

/*!
 * \brief Close the external SPI flash driver
 *
 * \return Result of the operation
 */
aos_result_t board_drv_spi_flash_close(void);

/*!
 * \brief Read data from the flash
 *
 * \param address Flash address (starting at 0)
 * \param data Area to store the result
 * \param size Number of bytes to read
 * \param fast True to do a fast access
 *
 * \return the result of the operation
 */
aos_result_t board_drv_spi_flash_read(uint32_t address, uint8_t *data, uint32_t size, bool fast);

/*!
 * \brief Program data to the flash
 *
 * \param address Flash address (starting at 0)
 * \param data Area containing the data to write
 * \param size Number of bytes to write
 *
 * \return the result of the operation
 *
 * \note
 *  1. The flash area written must fit a single page (256 bytes).
 *     The driver ensures this requirement and returns aos_result_param_error if it is not the case.
 *     So, the user must ensure that the first and the last addresses written are on the same page.
 *  2. The function returns once the data transfer is ended. User has to wait for the actual write.
 *     If this function or the board_drv_spi_flash_erase is called before the end of the actual
 *     completion, the functions will return  aos_result_busy.
 */
aos_result_t board_drv_spi_flash_program(uint32_t address, uint8_t *data, uint32_t size);

/*!
 * \brief Erase the flash
 *
 * \param type Erasing type
 * \param address Flash address (starting at 0)
 *
 * \return the result of the operation
 *
 * \note
 *  1. The function returns once the command has been sent (does not wait for the end of the erase).
 *  2. If the flash is busy (due to a previous erasing or programming), the function fails with aos_result_busy
 *  3. The address must be aligned with the type of erasing:
 *     - type = board_drv_spi_erase_type_sector: Address must be aligned on 4kB.
 *	   - board_drv_spi_erase_type_half_block: Address must be aligned on 32kB.
 *	   - board_drv_spi_erase_type_block: Address must be aligned on 64kB.
 *	   - board_drv_spi_erase_type_chip: No alignment required. Address not used.
 */
aos_result_t board_drv_spi_flash_erase(board_drv_spi_erase_type_t type, uint32_t address);

/*!
 * \brief Read the flash status registers (status 1, 2 and 3).
 *
 * \param status Area where to store the status
 *
 * \return the result of the operation
 *
 * \note
 *  The status calling parameter is formated as: (status3 << 24) | (status2 << 16) | status1,
 *  where status1, status2 and status3 are the actual flash status registers.
 */
aos_result_t board_drv_spi_flash_read_status(uint32_t*status);

/*!
 * \brief Check if the flash is busy
 *
 * \return aos_result_success if not busy (and ready to be used), aos_result_busy if the flash is busy or
 *  an error if the driver is not open.
 */
aos_result_t board_drv_spi_flash_is_busy(void);

/*!
 * \brief Get the manufacturer name in string formant
 *
 * \param id Manufacturer identifier
 *
 * \return The manufacturer name if known, otherwise "unknown"
 */
const char* board_drv_spi_flash_manuf_id_to_str(board_drv_spi_flash_manuf_id_t id);


/*! @}*/
#ifdef __cplusplus
}
#endif
