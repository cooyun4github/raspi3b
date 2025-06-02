#include <asm/io.h>

#include "gpio.h"

void select_pin_func(uint8_t pin, GPIO_FUNC_e func)
{
    // 先找到对应GPFSEL的虚拟地址
    unsigned long gpfsel_phys_addr = ADDR_GPFSEL_PIN(pin);
    volatile uint32_t *gpfsel_addr = (volatile uint32_t *)ioremap(gpfsel_phys_addr, BYTE_WIDTH);

    // 每pin占用3bit
    *gpfsel_addr &= ~(0b111 << (pin % 10 * 3));
    *gpfsel_addr |= func << (pin % 10 * 3);

    iounmap(gpfsel_addr);
}

void set_pin(uint8_t pin)
{
    // 先找到对应GPFSET的虚拟地址
    unsigned long gpset_phys_addr = ADDR_GPSET_PIN(pin);
    volatile uint32_t *gpset_addr = (volatile uint32_t *)ioremap(gpset_phys_addr, BYTE_WIDTH);

    // 每pin占用1bit
    *gpset_addr |= 1 << pin;

    iounmap(gpset_addr);
}

void clr_pin(uint8_t pin)
{
    // 先找到对应GPFSEL的虚拟地址
    unsigned long gpclr_phys_addr = ADDR_GPCLR_PIN(pin);
    volatile uint32_t *gpclr_addr = (volatile uint32_t *)ioremap(gpclr_phys_addr, BYTE_WIDTH);

    // 每pin占用1bit
    *gpclr_addr |= 1 << pin;

    iounmap(gpclr_addr);
}