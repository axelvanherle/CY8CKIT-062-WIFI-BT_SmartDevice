// Standard includes
#include "cyhal.h"
#include "cybsp.h"

// For printing over UART
#include "cy_retarget_io.h"

// For display
#include "smartdevice_display.h"

// For time
#include "smartdevice_time.h"

int main(void)
{
	cy_rslt_t result;

    // Initialize the device and board peripherals
    result = cybsp_init();

    // Board init failed. Stop program execution
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    // Enable global interrupts
    __enable_irq();

    // Initialize uart
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);
    // Ascii sequence to clear the screen
    printf("\x1b[2J\x1b[;H");
    printf("Hello\r\n");

    // Initialize the display controller
    result = mtb_st7789v_init8(&tft_pins);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    GUI_Init();
    GUI_SetBkColor(GUI_DARKCYAN);
    GUI_Clear();

    initUserButtonModeSelect();
    initSmartdeviceTime();

    while(1)
    {
    }
}
