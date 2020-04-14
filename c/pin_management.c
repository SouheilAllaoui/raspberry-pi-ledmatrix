#include <bcm2835.h>
#include <stdio.h>

int set_pin_high(int pin);
int set_pin_low(int pin);

int set_pin_high(int pin)
{
  if (!bcm2835_init())
      return 1;
    // Set the pin to be an output
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    
    // Turn it on
    bcm2835_gpio_write(pin, HIGH);
    
    bcm2835_close();

    return 0;
}

int set_pin_low(int pin)
{
  if (!bcm2835_init())
      return 1;
    // Set the pin to be an output
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    
    // Turn it on
    bcm2835_gpio_write(pin, LOW);
    
    bcm2835_close();

    return 0;
}
