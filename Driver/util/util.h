#ifndef __UTIL_H__
#define __UTIL_H__

#define SUCCESS 0


// LOG
#define DRV_LOGE(fmt, ...) \
    printk(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)

#define DRV_LOGI(fmt, ...) \
    printk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)

#define DRV_LOGT(fmt, ...) \
    printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)


#endif