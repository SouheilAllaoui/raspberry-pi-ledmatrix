#include <bcm2835.h>
#include <stdio.h>

// Command codes
#define HT1632C_CMD_MODE 0x04
#define HT1632C_WRITE_MODE 0x05
#define HT1632C_READ_MODE 0x06

// Commands (used in CMD_MODE)
#define HT1632C_CMD_SYS_DIS 0x00
#define HT1632C_CMD_SYS_EN 0x01
#define HT1632C_CMD_LED_OFF 0x02
#define HT1632C_CMD_LED_ON 0x03
#define HT1632C_CMD_BLINK_OFF 0x08
#define HT1632C_CMD_BLINK_ON 0x09
#define HT1632C_CMD_SLAVE_MODE 0x10
#define HT1632C_CMD_MASTER_MODE_RC 0x18
#define HT1632C_CMD_MASTER_MODE_EXTCLK 0x1C
#define HT1632C_CMD_COM_OPTION_NMOS_OPENDRAIN_8 0x20
#define HT1632C_CMD_COM_OPTION_NMOS_OPENDRAIN_16 0x24
#define HT1632C_CMD_COM_OPTION_PMOS_OPENDRAIN_8 0x28
#define HT1632C_CMD_COM_OPTION_PMOS_OPENDRAIN_16 0x2C
#define HT1632C_CMD_PWM_DUTY_1_16 0xA0
#define HT1632C_CMD_PWM_DUTY_2_16 0xA1
#define HT1632C_CMD_PWM_DUTY_3_16 0xA2
#define HT1632C_CMD_PWM_DUTY_4_16 0xA3
#define HT1632C_CMD_PWM_DUTY_5_16 0xA4
#define HT1632C_CMD_PWM_DUTY_6_16 0xA5
#define HT1632C_CMD_PWM_DUTY_7_16 0xA6
#define HT1632C_CMD_PWM_DUTY_8_16 0xA7
#define HT1632C_CMD_PWM_DUTY_9_16 0xA8
#define HT1632C_CMD_PWM_DUTY_10_16 0xA9
#define HT1632C_CMD_PWM_DUTY_11_16 0xAA
#define HT1632C_CMD_PWM_DUTY_12_16 0xAB
#define HT1632C_CMD_PWM_DUTY_13_16 0xAC
#define HT1632C_CMD_PWM_DUTY_14_16 0xAD
#define HT1632C_CMD_PWM_DUTY_15_16 0xAE
#define HT1632C_CMD_PWM_DUTY_16_16 0xAF

// Other
#define DEBUG 0

void print_bits(size_t const size, void const * const ptr);
void ht1632c_send_command(uint8_t command);
void ht1632c_init();
void ht1632c_write(uint8_t addr, uint8_t data);


int main(int argc, char **argv)
{
    // Send a byte to the slave and simultaneously read a byte back from the slave
    // If you tie MISO to MOSI, you should read back what was sent

    
    // If you call this, it will not actually access the GPIO
    // Use for testing
    // bcm2835_set_debug(1);
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

    ht1632c_init();
    int t = 0;

    for (int i = 0; i < 96; i++) {
            ht1632c_write(i, 0x00);
    }
   // ht1632c_write(0x23, 0x08);

    bcm2835_spi_end();
    bcm2835_close();
    
    return 0;
}

void ht1632c_init()
{
  ht1632c_send_command(HT1632C_CMD_SYS_DIS);
  ht1632c_send_command(HT1632C_CMD_SYS_EN);
  ht1632c_send_command(HT1632C_CMD_LED_ON);
  ht1632c_send_command(HT1632C_CMD_BLINK_OFF);
  ht1632c_send_command(HT1632C_CMD_MASTER_MODE_RC);
  ht1632c_send_command(HT1632C_CMD_PWM_DUTY_16_16);
}

void ht1632c_send_command(uint8_t command)
{
  uint16_t buf = (HT1632C_CMD_MODE << 13) | (command << 5); // concatenate mode and command bits and fill up to 16 bits with 0's

#ifdef DEBUG
  print_bits(sizeof(buf), &buf);
#endif

  bcm2835_spi_write(buf);


}

void ht1632c_write(uint8_t addr, uint8_t data)
{
  data = data & 0x0F;
  addr = addr & 0x7F;   // force first nibble low
  uint16_t buf = (HT1632C_WRITE_MODE << 13) | (addr << 6);
  buf = buf | (data << 2);

#ifdef DEBUG
  print_bits(sizeof(buf), &buf);
#endif

  bcm2835_spi_write(buf);
}

void print_bits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
