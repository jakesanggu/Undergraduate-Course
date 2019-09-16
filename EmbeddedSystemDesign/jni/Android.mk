LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := calculate
LOCAL_SRC_FILES := textlcd.c gpio.c device_interface.c stack.c math_express.c service.c queue.c push_button.c fnd.c 


include $(BUILD_SHARED_LIBRARY)
