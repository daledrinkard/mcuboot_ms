/***********************************************************************************************************************
 * File Name    : menu.c
 * Description  : Contains menu item implementations
 ***********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
#include "menu.h"
#include "header.h"
#include "comms.h"
#include "xmodem.h"
#include "downloader_thread.h"
#include "header.h"

#include "hal_data.h"
#include "qspi_ep.h"
#include "qspi_operations.h"


flash_result_t blank_check_result = FLASH_RESULT_BLANK;

/*******************************************************************************************************************//**
 * @brief This function provides the user menu to initiate the new image download as well as
 *          the slot information and execution result
 * @param[IN]   none
 * @retval      none
 **********************************************************************************************************************/

void menu(void)
{
    volatile fsp_err_t err = 0;
    uint8_t tx_str[80];
    uint8_t rx_str[20];


    FSP_PARAMETER_NOT_USED(err);

    sprintf((char *)tx_str, "\n\r");
    comms_send(tx_str, strlen((char *)tx_str));
    sprintf((char *)tx_str, "Please select from below menu options:\n\r");
    comms_send(tx_str, strlen((char *)tx_str));

    sprintf((char *)tx_str, "\n\r1 - Display image slot info\n\r");
    comms_send(tx_str, strlen((char *)tx_str));
    sprintf((char *)tx_str, "2 - Download and boot the new image (XModem)\n\r");
    comms_send(tx_str, strlen((char *)tx_str));
    comms_send((uint8_t *)">", 1);

    rx_str[0] = 0;
    uint32_t len = 1;
    err = comms_read(rx_str, &len, portMAX_DELAY);
    if(err != FSP_SUCCESS)
    {
          __BKPT(1);
    }
    comms_send(rx_str, 1);
    comms_send((uint8_t *)"\n\r", 2);

    switch (rx_str[0])
    {
        case '1':
            display_image_slot_info();
        break;

        case '2':

        /* Download a new image in the secondary slot using the XModem protocol */
           /* Erase the secondary slot first */
           /* Check if it needs erasing first */
           sprintf((char *)tx_str, "Blank checking the secondary slot...\r\n");
           comms_send(tx_str, strlen((char *)tx_str));

            bool blank = true;
            uint8_t * p_src;

            blank = true;
            p_src = (uint8_t *) SECONDARY_IMAGE_START_ADDRESS;
            do {
                if (*p_src != 0xFF)
                {
                    blank = false;
                }
                p_src++;
            } while ((blank == true) && (p_src < (uint8_t *)SECONDARY_IMAGE_END_ADDRESS));

            if(1)
            {
                if (true == blank)
                {
                    sprintf((char *)tx_str, "NS Secondary slot blank\r\n");
                    comms_send(tx_str, strlen((char *)tx_str));
                }
                else
                {
                    sprintf((char *)tx_str, "Erasing the secondary slot...\r\n");
                    comms_send(tx_str, strlen((char *)tx_str));
                    ThreadsAndInterrupts(DISABLE);
#if 0
                    err = R_FLASH_HP_Erase(&g_flash0_ctrl, (uint32_t) SECONDARY_IMAGE_START_ADDRESS, SECONDARY_IMAGE_NUM_BLOCKS);
                    if(FSP_SUCCESS == err)
                    {
                        err = R_FLASH_HP_BlankCheck(&g_flash0_ctrl, SECONDARY_IMAGE_START_ADDRESS, SECONDARY_IMAGE_END_ADDRESS - SECONDARY_IMAGE_START_ADDRESS + 1, &blank_check_result);
                        if(FSP_SUCCESS == err)
                        {
                            if (FLASH_RESULT_BLANK != blank_check_result)
                            {
                                sprintf((char *)tx_str, "ERROR: Flash is not blank after erasing\r\n");
                                comms_send(tx_str, strlen((char *)tx_str));
                            }
                        }
                    }
#endif
                    for(int k=0; k<(0xE0000/0x1000);k++)
                    {
                         err = R_QSPI_Erase(&g_qspi0_ctrl, (uint8_t *)SECONDARY_IMAGE_START_ADDRESS+k*4096, 4096);
                         if (FSP_SUCCESS != err)
                         {
                            deinit_qspi(g_qspi0_cfg.spi_protocol);
                         }
                         else
                         {
                            err = get_flash_status();
                            if (FSP_SUCCESS != err)
                            {
                               deinit_qspi(g_qspi0_cfg.spi_protocol);
                            }
                          }
                     }

                    ThreadsAndInterrupts(RE_ENABLE);

                    if(FSP_SUCCESS == err)
                    {
                        sprintf((char *)tx_str, "Secondary slot erased\r\n");
                        comms_send(tx_str, strlen((char *)tx_str));
                    }
                    else
                    {
                        sprintf((char *)tx_str, "ERROR: Erasing the secondary slot\r\n");
                        comms_send(tx_str, strlen((char *)tx_str));

                        break;
                    }
                }

                /* XModem download and flash programming */
                sprintf((char *)tx_str, "Start Xmodem transfer...\r\n");
                comms_send(tx_str, strlen((char *)tx_str));
                sprintf((char *)tx_str, "System will automatically reset after successful download...\r\n");
               comms_send(tx_str, strlen((char *)tx_str));
                unsigned char xm_err = XmodemDownloadAndProgramFlash(SECONDARY_IMAGE_START_ADDRESS);
                if(XM_OK != xm_err)
                {
                    
                    switch(xm_err)
                    {
                        case XM_ADDRESS_ERROR:
                            sprintf((char *)tx_str, "ERROR: Flash address invalid\r\n");
                        break;

                        case XM_TIMEOUT:
                            sprintf((char *)tx_str, "ERROR: Timeout during Xmodem download\r\n");
                        break;

                        case XM_PROG_FAIL:
                            sprintf((char *)tx_str, "ERROR: Flash programming error\r\n");
                        break;

                        default:
                            sprintf((char *)tx_str, "ERROR: unknown (%d)\r\n", xm_err);
                        break;
                    }

                    comms_send(tx_str, strlen((char *)tx_str));
                }
            }
            else
            {
                sprintf((char *)tx_str, "ERROR: Blank checking the secondary slot\r\n");
                comms_send(tx_str, strlen((char *)tx_str));
            }

        break;
        default:
        break;
    }
}

void ThreadsAndInterrupts(enable_disable_t EnableDisable)
{
    static uint32_t control_reg_value;
    static uint32_t old_primask;

    if( DISABLE == EnableDisable )
    {
        /** Store the interrupt state */
        old_primask = __get_PRIMASK();


        /* Disable the SysTick timer */
        control_reg_value = SysTick->CTRL;
        SysTick->CTRL = 0;
        NVIC_DisableIRQ( SysTick_IRQn ); /* Disable the SysTick timer IRQ */
        NVIC_ClearPendingIRQ( SysTick_IRQn ); /* Clear any pending SysTick timer IRQ */

        __disable_irq(); /* Disable interrupts */
    }
    else
    {
        NVIC_EnableIRQ( SysTick_IRQn ); /* Enable the SysTick timer IRQ */
        SysTick->CTRL = control_reg_value; /* Restart the SysTick timer */

        /** Restore the interrupt state */
        __set_PRIMASK( old_primask ); /* Enable interrupts */


    }
}
