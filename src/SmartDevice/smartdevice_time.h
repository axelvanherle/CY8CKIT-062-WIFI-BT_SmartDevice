/*
 * smartdevice_time.h
 *
 *  Created on: May 20, 2023
 *      Author: xel
 */

#ifndef SMARTDEVICE_TIME_H_
#define SMARTDEVICE_TIME_H_

#define TM_YEAR_BASE (1900u)

cy_rslt_t result;

// For RTC
cyhal_rtc_t my_rtc;
char bufMinHour[8];
char bufSec[4];
char bufDate[32];
struct tm new_date_time = {0};
struct tm current_date_time = {0};

int seconds = 10;
int minutes = 10;
int hours = 8;
int mday = 3;
int month = 3;
int year = 2020;
int wday = 3;
int dst = 0;

// Timer object used
cyhal_timer_t timer_obj;
bool timer_interrupt_flag = false;

static void isr_timer(void* callback_arg, cyhal_timer_event_t event)
{
    (void)callback_arg;
    (void)event;

    // Set the interrupt flag and process it from the application
    timer_interrupt_flag = true;

	cyhal_rtc_read(&my_rtc, &current_date_time);
	strftime(bufMinHour, sizeof(bufMinHour), "%H:%M", &current_date_time);
	strftime(bufSec, sizeof(bufSec), "%S", &current_date_time);
	strftime(bufDate, sizeof(bufDate), "%A, %d %b %Y", &current_date_time);
	printf("%s - %s\n\r",bufMinHour,bufSec);

    int xPos = 10;
    int yPos = 10;
    GUI_SetFont(&GUI_FontD64);
    GUI_DispStringAt(bufMinHour, xPos, yPos);

    // Display seconds with smaller font to the right
    xPos += GUI_GetStringDistX(bufMinHour)+10;
    yPos += 16;
    GUI_SetFont(&GUI_FontD48);
    GUI_DispStringAt(bufSec, xPos, yPos);

    GUI_SetFont(&GUI_Font32_ASCII);
    xPos = (LCD_GetXSize() - GUI_GetStringDistX(bufDate)) / 2; // get xpos in the middle
    yPos += 52;
    GUI_DispStringAt(bufDate, xPos, yPos);
}


cy_rslt_t snippet_cyhal_timer_event_interrupt()
{
    const cyhal_timer_cfg_t timer_cfg =
    {
        .compare_value = 0,                  // Timer compare value, not used
        .period        = 9999,               // Defines the timer period
        .direction     = CYHAL_TIMER_DIR_UP, // Timer counts up
        .is_compare    = false,              // Don't use compare mode
        .is_continuous = true,               // Run the timer indefinitely
        .value         = 0                   // Initial value of counter
    };

    // Initialize the timer object. Does not use pin output ('pin' is NC) and does not use a
    // pre-configured clock source ('clk' is NULL).
    result = cyhal_timer_init(&timer_obj, NC, NULL);

    // Apply timer configuration such as period, count direction, run mode, etc.
    if (CY_RSLT_SUCCESS == result)
    {
    	result = cyhal_timer_configure(&timer_obj, &timer_cfg);
    }

    // Set the frequency of timer to 10000 Hz
    if (CY_RSLT_SUCCESS == result)
    {
    	result = cyhal_timer_set_frequency(&timer_obj, 10000);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        // Assign the ISR to execute on timer interrupt
        cyhal_timer_register_callback(&timer_obj, isr_timer, NULL);

        // Set the event on which timer interrupt occurs and enable it
        cyhal_timer_enable_event(&timer_obj, CYHAL_TIMER_IRQ_TERMINAL_COUNT, 3, true);

        // Start the timer with the configured settings
        result = cyhal_timer_start(&timer_obj);
    }

    // Assign values to global variables
    new_date_time.tm_sec = seconds;
    new_date_time.tm_min = minutes;
    new_date_time.tm_hour = hours;
    new_date_time.tm_mday = mday;
    new_date_time.tm_mon = month - 1;
    new_date_time.tm_year = year - TM_YEAR_BASE;
    new_date_time.tm_wday = wday;
    new_date_time.tm_isdst = dst;

    result = cyhal_rtc_init(&my_rtc);
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    result = cyhal_rtc_write(&my_rtc, &new_date_time);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    return result;
}

void initSmartdeviceTime(void)
{
	bool debug = false;
	if(debug == false)
	{
	    printf("What is the current year?\r\n");
	    scanf("%d",&year);
	    printf("What is the current Month?\r\n");
	    scanf("%d",&month);
	    printf("What is the current Day?\r\n");
	    scanf("%d",&mday);
	    printf("What is the current Hour?\r\n");
	    scanf("%d",&hours);
	    printf("What is the current Minute?\r\n");
	    scanf("%d",&minutes);
	    printf("What is the current Second?\r\n");
	    scanf("%d",&seconds);
	}

    result = snippet_cyhal_timer_event_interrupt();
    CY_ASSERT(result == CY_RSLT_SUCCESS);
}




#endif /* SMARTDEVICE_TIME_H_ */
