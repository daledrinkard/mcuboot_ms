/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_sci_uart.h"
#include "r_uart_api.h"
#include "r_qspi.h"
#include "r_spi_flash_api.h"

#include "r_flash_hp.h"
#include "r_flash_api.h"

#include "rm_mcuboot_port.h"
#if defined(MCUBOOT_USE_MBED_TLS)
#include "mbedtls/platform.h"
#endif
FSP_HEADER
/** UART on SCI Instance. */
extern const uart_instance_t g_printf_uart;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_printf_uart_ctrl;
extern const uart_cfg_t g_printf_uart_cfg;
extern const sci_uart_extended_cfg_t g_printf_uart_cfg_extend;

#ifndef printf_uart_callback
void printf_uart_callback(uart_callback_args_t *p_args);
#endif
extern const spi_flash_instance_t g_qspi0;
extern qspi_instance_ctrl_t g_qspi0_ctrl;
extern const spi_flash_cfg_t g_qspi0_cfg;
/* Flash on Flash HP Instance */
extern const flash_instance_t g_flash0;

/** Access the Flash HP instance using these structures when calling API functions directly (::p_api is not used). */
extern flash_hp_instance_ctrl_t g_flash0_ctrl;
extern const flash_cfg_t g_flash0_cfg;

#ifndef NULL
void NULL(flash_callback_args_t *p_args);
#endif
void mcuboot_quick_setup();
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
