#include "cyhal.h"
#include "cybsp.h"

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

    while(1)
    {
    }
}
