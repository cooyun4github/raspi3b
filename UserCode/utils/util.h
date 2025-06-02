#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>

typedef enum {
    LOG_FATAL,
    LOG_ERROR,
    LOG_INFO,
    LOG_TRACE,
} LOG_LEVEL_e;

#define LOGI(DBG_FMT, format, ...) printf("[I] %s:%d %s [%s] " format "\n", __FILE__, __LINE__, __func__, DBG_FMT, ##__VA_ARGS__)
#define LOGE(DBG_FMT, format, ...) printf("[E] %s:%d %s [%s] " format "\n", __FILE__, __LINE__, __func__, DBG_FMT, ##__VA_ARGS__)


#endif