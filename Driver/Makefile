# 获取当前运行的内核源码路径
# 如果不存在目录/lib/modules/$(shell uname -r)/build，需要使用如下指令手动安装内核头文件：
# sudo apt install raspberrypi-kernel-headers
KDIR ?= /lib/modules/$(shell uname -r)/build
Driver ?= /home/canyon/Driver

# 额外的CFLAG参数，用于添加自定义头文件目录
EXTRA_CFLAGS += -I$(Driver)/util \
				-I$(Driver)/gpio


MODULE = pin4_drv

obj-m += $(MODULE).o

$(MODULE)-y := pin4_drv/pin4_drv.o
$(MODULE)-y += util/util.o
$(MODULE)-y += gpio/gpio.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

# 可选：加载和卸载模块
load: all
	sudo insmod pin4_drv.ko

unload:
	sudo rmmod pin4_drv