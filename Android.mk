# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ndk_bridge

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/include \
		$(LOCAL_PATH)/src
		
LOCAL_EXPORT_C_INCLUDES := \
	 $(LOCAL_PATH)/include \
	 $(LOCAL_PATH)/src

LOCAL_SRC_FILES :=  \
	src/NativeContext.cpp \
	src/NativeInterface.cpp \
	src/utils/StringTools.cpp \
	src/java/security/MessageDigest.cpp \
	src/android/content/pm/NativePackageInfo.cpp \
	src/android/content/pm/NativePackageManager.cpp \
	src/android/content/pm/NativeSignature.cpp \
	src/android/telephony/NativeTelephonyManager.cpp \
	src/android/content/NativeContentResolver.cpp

						
LOCAL_CFLAGS := -fvisibility=hidden
include $(BUILD_STATIC_LIBRARY)