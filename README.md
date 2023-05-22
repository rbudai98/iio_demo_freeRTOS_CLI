# freeRTOS_no_os
Porting freeRTOS to no_os 
### Related no-os branch: https://github.com/analogdevicesinc/no-OS/tree/freeRTOS_support


## To do:
- [x] freeRTOS on MAX78000
- [x] no-os demo on MAX7800
- [x] FreeRTOS config for no-os MAX78000 (some variables still need generic form, see notes)
- [x] Include and Source files
- [x] Makefile rules
- [x] Handling noos platform mimplementations and port.c common parts
- [x] Checking for makefile variables and add freeRTOS as optional
- [ ] Creating task compatible iio_demo implementation
- [x] Add semaphore structure for pheripherals
- [ ] Readme for including
- [x] Port and Test on Max78000
- [ ] Port and Test on STM
- [ ] Port and Test on Intel
- [ ] Port and Test on Xilinx

## Notes:
For build the user has to clone two repositories:
- https://github.com/FreeRTOS/FreeRTOS-Kernel
- https://github.com/FreeRTOS/FreeRTOS (for CLI example)
In CLI example the iio_demo will be implemented as an example task with high priority

FreeRTOSConfig.h:
* configPRIO_BITS: sets the number of priority bits on the target. Usually comes from CMSIS, but needs generalization for other platforms as well
* configCPU_CLOCK_HZ: keeps a global update with current system clock in Hz, also needs generalization in case of different platforms
