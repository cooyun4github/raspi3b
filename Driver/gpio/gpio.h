#ifndef _GPIO_H_
#define _GPIO_H_

/*
 * 32位系统，地址位宽4bytes
 */
#define BYTE_WIDTH         4

/*
 * IO base addr: 0x3f00 0000, GPIO offset: 0x0020 0000, GPFSEL
 * 一共54个pin，3个bit描述一个PIN的GPFSEL，每个GPFSELn(32bit)可以描述10个pin
 * 因此 0 <= n <= 5
 */
#define ADDR_GPIO_START         0x3f200000
#define ADDR_GPFSEL(n)          (ADDR_GPIO_START + n * BYTE_WIDTH)
#define ADDR_GPFSEL_PIN(pin)    ADDR_GPFSEL(pin / 10)

/*
 * 可以设置的PIN的功能值
 */
typedef enum {
    GPIO_FUNC_INPUT,
    GPIO_FUNC_OUTPUT,
} GPIO_FUNC_e;

/*
 * 每个bit描述一个PIN的GPSET，每个GPSETn(32bit)可以描述32pin
 */
#define ADDR_GPSET_START        0x3f20001c
#define ADDR_GPSET(n)           (ADDR_GPSET_START + n * BYTE_WIDTH)
#define ADDR_GPSET_PIN(pin)     ADDR_GPSET(pin / 32)

/*
 * 每个bit描述一个PIN的GPCLR，每个GPCLRn(32bit)可以描述32pin
 */
#define ADDR_GPCLR_START        0x3f20001c
#define ADDR_GPCLR(n)           (ADDR_GPCLR_START + n * BYTE_WIDTH)
#define ADDR_GPCLR_PIN(pin)     ADDR_GPCLR(pin / 32)


void select_pin_func(uint8_t pin, GPIO_FUNC_e func);
void set_pin(uint8_t pin);
void clr_pin(uint8_t pin);


#endif