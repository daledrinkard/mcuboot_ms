/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_uart_rxi_isr, /* SCI9 RXI (Receive data full) */
            [1] = sci_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [2] = sci_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [3] = sci_uart_eri_isr, /* SCI9 ERI (Receive error) */
            [4] = usbfs_interrupt_handler, /* USBFS INT (USBFS interrupt) */
            [5] = usbfs_resume_handler, /* USBFS RESUME (USBFS resume interrupt) */
            [6] = usbfs_d0fifo_handler, /* USBFS FIFO 0 (DMA transfer request 0) */
            [7] = usbfs_d1fifo_handler, /* USBFS FIFO 1 (DMA transfer request 1) */
            [8] = dmac_int_isr, /* DMAC0 INT (DMAC0 transfer end) */
            [9] = dmac_int_isr, /* DMAC1 INT (DMAC1 transfer end) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI9_RXI,GROUP0), /* SCI9 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TXI,GROUP1), /* SCI9 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TEI,GROUP2), /* SCI9 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI9_ERI,GROUP3), /* SCI9 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_USBFS_INT,GROUP4), /* USBFS INT (USBFS interrupt) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_USBFS_RESUME,GROUP5), /* USBFS RESUME (USBFS resume interrupt) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_USBFS_FIFO_0,GROUP6), /* USBFS FIFO 0 (DMA transfer request 0) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_USBFS_FIFO_1,GROUP7), /* USBFS FIFO 1 (DMA transfer request 1) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_DMAC0_INT,GROUP0), /* DMAC0 INT (DMAC0 transfer end) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_DMAC1_INT,GROUP1), /* DMAC1 INT (DMAC1 transfer end) */
        };
        #endif
        #endif
