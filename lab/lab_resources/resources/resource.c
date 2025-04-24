/*
 * resource.c
 *
 *  Created on: Mar 25, 2025
 *      Author: daled
 */

#include "hal_data.h"
#include "resource.h"
const res_t resources BSP_PLACE_IN_SECTION(".qspi_flash") = {
  .header = {0}, /* the header is built by the signing tool, here we just carve out space for it */
  .data = "\r\nRESOURCE FILE FOR PRIMARY\r\n"
};
