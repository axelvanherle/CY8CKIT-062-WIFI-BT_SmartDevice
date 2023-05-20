/*
 * smartdevice_display.h
 *
 *  Created on: May 19, 2023
 *      Author: xel
 */

#ifndef SMARTDEVICE_DISPLAY_H_
#define SMARTDEVICE_DISPLAY_H_

// For display tft
#include "cy_pdl.h"
#include "GUI.h"
#include "mtb_st7789v.h"
#include "cy8ckit_028_tft_pins.h"

/* The pins above are defined by the CY8CKIT-028-TFT library. If the display is being used on different hardware the mappings will be different. */
const mtb_st7789v_pins_t tft_pins =
{
    .db08 = CY8CKIT_028_TFT_PIN_DISPLAY_DB8,
    .db09 = CY8CKIT_028_TFT_PIN_DISPLAY_DB9,
    .db10 = CY8CKIT_028_TFT_PIN_DISPLAY_DB10,
    .db11 = CY8CKIT_028_TFT_PIN_DISPLAY_DB11,
    .db12 = CY8CKIT_028_TFT_PIN_DISPLAY_DB12,
    .db13 = CY8CKIT_028_TFT_PIN_DISPLAY_DB13,
    .db14 = CY8CKIT_028_TFT_PIN_DISPLAY_DB14,
    .db15 = CY8CKIT_028_TFT_PIN_DISPLAY_DB15,
    .nrd  = CY8CKIT_028_TFT_PIN_DISPLAY_NRD,
    .nwr  = CY8CKIT_028_TFT_PIN_DISPLAY_NWR,
    .dc   = CY8CKIT_028_TFT_PIN_DISPLAY_DC,
    .rst  = CY8CKIT_028_TFT_PIN_DISPLAY_RST
};

uint8_t trackColor = 0;

//Interrupt handler
static void button_isr(void *handler_arg, cyhal_gpio_event_t event)
{
    switch (trackColor)
    {
        case 0:  // GUI_BLUE
            GUI_SetBkColor(GUI_BLUE);
            break;
        case 1:  // GUI_GREEN
            GUI_SetBkColor(GUI_GREEN);
            break;
        case 2:  // GUI_RED
            GUI_SetBkColor(GUI_RED);
            break;
        case 3:  // GUI_CYAN
            GUI_SetBkColor(GUI_CYAN);
            break;
        case 4:  // GUI_MAGENTA
            GUI_SetBkColor(GUI_MAGENTA);
            break;
        case 5:  // GUI_YELLOW
            GUI_SetBkColor(GUI_YELLOW);
            break;
        case 6:  // GUI_LIGHTBLUE
            GUI_SetBkColor(GUI_LIGHTBLUE);
            break;
        case 7:  // GUI_LIGHTGREEN
            GUI_SetBkColor(GUI_LIGHTGREEN);
            break;
        case 8:  // GUI_LIGHTRED
            GUI_SetBkColor(GUI_LIGHTRED);
            break;
        case 9:  // GUI_LIGHTCYAN
            GUI_SetBkColor(GUI_LIGHTCYAN);
            break;
        case 10:  // GUI_LIGHTMAGENTA
            GUI_SetBkColor(GUI_LIGHTMAGENTA);
            break;
        case 11:  // GUI_LIGHTYELLOW
            GUI_SetBkColor(GUI_LIGHTYELLOW);
            break;
        case 12:  // GUI_DARKBLUE
            GUI_SetBkColor(GUI_DARKBLUE);
            break;
        case 13:  // GUI_DARKGREEN
            GUI_SetBkColor(GUI_DARKGREEN);
            break;
        case 14:  // GUI_DARKRED
            GUI_SetBkColor(GUI_DARKRED);
            break;
        case 15:  // GUI_DARKCYAN
            GUI_SetBkColor(GUI_DARKCYAN);
            break;
        case 16:  // GUI_DARKMAGENTA
            GUI_SetBkColor(GUI_DARKMAGENTA);
            break;
        case 17:  // GUI_DARKYELLOW
            GUI_SetBkColor(GUI_DARKYELLOW);
            break;
        case 18:  // GUI_WHITE
            GUI_SetBkColor(GUI_WHITE);
            break;
        case 19:  // GUI_LIGHTGRAY
            GUI_SetBkColor(GUI_LIGHTGRAY);
            break;
        case 20:  // GUI_GRAY
            GUI_SetBkColor(GUI_GRAY);
            break;
        case 21:  // GUI_DARKGRAY
            GUI_SetBkColor(GUI_DARKGRAY);
            break;
        case 22:  // GUI_BLACK
            GUI_SetBkColor(GUI_BLACK);
            break;
        case 23:  // GUI_BROWN
            GUI_SetBkColor(GUI_BROWN);
            break;
        case 24:  // GUI_ORANGE
            GUI_SetBkColor(GUI_ORANGE);
            break;
        case 25:  // GUI_TRANSPARENT
            GUI_SetBkColor(GUI_TRANSPARENT);
            break;
    }

    GUI_Clear();
    trackColor++;

    // Reset trackColor when it exceeds the number of colors
    if (trackColor > 25)
    {
        trackColor = 0;
    }
}

// GPIO callback initialization structure
cyhal_gpio_callback_data_t cb_data =
{
	.callback     = button_isr,
	.callback_arg = NULL
};

void initUserButtonModeSelect(void)
{
	cy_rslt_t result;
	result = cyhal_gpio_init(CYBSP_USER_BTN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULLUP, CYBSP_BTN_OFF);
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}
	cyhal_gpio_register_callback(CYBSP_USER_BTN, &cb_data);
	cyhal_gpio_enable_event(CYBSP_USER_BTN, CYHAL_GPIO_IRQ_FALL, 1u, true);
}


#endif /* SMARTDEVICE_DISPLAY_H_ */
