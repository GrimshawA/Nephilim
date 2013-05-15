commonSources:= Engine.cpp
LOCAL_PATH:= $(call my-dir)/../../../Source
include $(CLEAR_VARS)
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES:= $(notdir $(wildcard $(LOCAL_PATH)/*.cpp)) 
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../Include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../IncludeExt/
LOCAL_CFLAGS    := -DMINIMAL_BUILD
LOCAL_MODULE:= libnephilim
include $(BUILD_STATIC_LIBRARY)
