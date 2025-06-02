#include <linux/fs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/types.h>

#include "pin4_drv.h"
#include "gpio.h"
#include "util.h"

#define PIN_ID 4
#define PIN4_MODULE_NAME "pin4"
#define PIN4_MAJOR 200
#define PIN4_MINOR 0

static struct class *pin4_class;
static struct device *pin4_device;
static dev_t pin4_devno;

static int pin4_open(struct inode *inode, struct file *file)
{
    DRV_LOGI("pin4_open start\n");
    select_pin_func(PIN_ID, GPIO_FUNC_OUTPUT);
    DRV_LOGI("pin4_open finish\n");

    return 0;
}

static ssize_t pin4_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    uint8_t pin_level;
    uint32_t bytes_not_copied;

    DRV_LOGI("pin4_write start\n");

    bytes_not_copied = copy_from_user(&pin_level, buf, count);
    // 如果 bytes_not_copied 不为 0，表示有部分数据未被成功复制
    if (bytes_not_copied != 0) {
        DRV_LOGE("Failed to copy from user space, left:%u\n", bytes_not_copied);
        return -1;
    }

    if (pin_level == PIN_LEVEL_LOW) {
        clr_pin(PIN_ID);
    } else {
        set_pin(PIN_ID);
    }
    DRV_LOGI("pin4 write %d finish\n", pin_level);

    return 0;
}

static struct file_operations pin4_fops = {
    .owner = THIS_MODULE,
    .open  = pin4_open,
    .write = pin4_write,
};

int __init pin4_drv_init(void)
{
    int ret;

    DRV_LOGI("pint4_drv_init start");

    pin4_devno = MKDEV(PIN4_MAJOR, PIN4_MINOR);
    ret = register_chrdev(PIN4_MAJOR, PIN4_MODULE_NAME, &pin4_fops);
    if (ret != 0) {
        DRV_LOGI("pint4_drv_init fail, ret:%d\n", ret);
    }

    pin4_class = class_create(THIS_MODULE, "canyon pin4");
    pin4_device = device_create(pin4_class, NULL, pin4_devno, NULL, PIN4_MODULE_NAME);

    DRV_LOGI("pint4_drv_init finish");

    return 0;
}

void __exit pin4_drv_exit(void)
{
    DRV_LOGI("pin4_drv_exit start");

    device_destroy(pin4_class, pin4_devno);
    class_destroy(pin4_class);
    unregister_chrdev(PIN4_MAJOR, PIN4_MODULE_NAME);

    DRV_LOGI("pin4_drv_exit finish");
}


module_init(pin4_drv_init);
module_exit(pin4_drv_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("canyon");
MODULE_DESCRIPTION("pin4 driver for raspi3b of canyon");
MODULE_VERSION("1.0");