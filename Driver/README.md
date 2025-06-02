# raspi3b

# open a new terminal and check dmesg log
dmesg -w

# insmod
cd Driver
make
sudo insmod pin4_drv.ko

# rmmod
sudo rmmod pin4_drv

# set pin4 level in user space
cd UserCode
mkdir build
cmake ..
make
sudo chmod 666 /dev/pin4
./pin4 1
./pin4 0