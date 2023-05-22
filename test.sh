rm -rf build
export FREERTOS=y
export MAXIM_LIBRARIES=/home/robi/Desktop/MaximSDK/MaximSDK/Libraries
export FREERTOS_PLUS=/home/robi/Workspace_no-os/FreeRTOS/FreeRTOS-Plus
export FREERTOS_KERNEL=/home/robi/Workspace_no-os/FreeRTOS-Kernel

make PLATFORM=maxim TARGET=max78000
# make PLATFORM=maxim TARGET=max78000 run
