//////////////////////////////////////////////////////////////////////////////
// This file is part of the PharaohStroy MMORPG client                      //
// It is desgined for simplifying ndk to java calls                         //
// Copyright ?2016-2017 Prime Zeng                                          //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include <jni.h>
#include <memory>
#include "android/telephony/NativeTelephonyManager.h"
#include "android/content/pm/NativePackageManager.h"
#include "android/content/NativeContentResolver.h"
#include <string>

#define getObject(obj,method,returnType)                        \
        if(obj == nullptr) {                                    \
            obj = std::make_unique<returnType>();               \ 
            auto r = env->CallObjectMethod(javaContext, method);\
            obj->initWithJobject(r,env);                        \
        }                                                       \
        return obj;

class NativeContext
{
  public:
    NativeContext(jobject javaContext, JNIEnv *env);
    auto getPackageManager() -> std::unique_ptr<NativePackageManager> &;
    auto getTelephonyManager() -> std::unique_ptr<NativeTelephonyManager> &;
    auto getContentResolver() -> std::unique_ptr<NativeContentResolver> &;
    auto getPackageName() -> std::string;

    ~NativeContext();

  private:
    jmethodID methodGetPackManager;
    jmethodID methodGetTelephonyManager;
    jmethodID methodGetPackName;
    jmethodID methodGetContentResolver;

  private:
    jobject javaContext;
    jclass contextClass;

  private:
    jstring TELEPHONY_SERVICE;

  private:
    JNIEnv *env;
    std::unique_ptr<NativePackageManager> packageManager;
    std::unique_ptr<NativeTelephonyManager> telephonyManager;
    std::unique_ptr<NativeContentResolver> contentResolver;
};
