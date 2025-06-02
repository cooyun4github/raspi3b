#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h> // open()
#include <string.h> // strerror()
#include <errno.h>
#include <unistd.h>

#include "util.h"

#define DBG_FMT "PIN4"

int main(int argc, char *argv[])
{
    int32_t pin4_fd;
    uint8_t pin_level;
    ssize_t write_size;

    if (argc != 2) {
        LOGE(DBG_FMT, "only support one input param");
        return 0;
    }

    pin_level = atoi(argv[1]);
    if (pin_level != 0 && pin_level != 1) {
        LOGE(DBG_FMT, "only support set pin4 to 0 or 1");
        return 0;
    }

    LOGI(DBG_FMT, "set pin4 to:%d", pin_level);

    pin4_fd = open("/dev/pin4", O_RDWR);
    if (pin4_fd < 0) {
        perror("open /dev/pin4 fail\n");
        return -1;
    } else {
        LOGI(DBG_FMT, "open pin4 succes\n", strerror(errno));
    }

    write_size = write(pin4_fd, &pin_level, sizeof(uint8_t));
    if (write_size == -1) {
        perror("write /dev/pin4 fail\n");
        return -1;
    }
    LOGI(DBG_FMT, "write %zd size to pin4", write_size);

    return 0;
}