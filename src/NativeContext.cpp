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

#include "NativeContext.h"
#include "utils/StringTools.h"
#include "android/content/pm/NativePackageManager.h"
#include "android/telephony/NativeTelephonyManager.h"

NativeContext::NativeContext(jobject javaContext, JNIEnv *env)
    : javaContext(javaContext), env(env)
{

    contextClass = env->FindClass("android/content/Context");
    methodGetPackManager = env->GetMethodID(contextClass, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    methodGetPackName = env->GetMethodID(contextClass, "getPackageName", "()Ljava/lang/String;");
    methodGetTelephonyManager = env->GetMethodID(contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    methodGetContentResolver =  env->GetMethodID(contextClass, "getContentResolver", "()Landroid/content/ContentResolver;");
    
    auto field = env->GetStaticFieldID(contextClass, "TELEPHONY_SERVICE", "Ljava/lang/String;");
    TELEPHONY_SERVICE = static_cast<jstring>(env->GetStaticObjectField(contextClass, field));
}

NativeContext::~NativeContext()
{
    env->DeleteLocalRef(TELEPHONY_SERVICE);
}

auto NativeContext::getPackageName() -> std::string
{
    jstring packageName = (jstring)env->CallObjectMethod(javaContext, methodGetPackName);
    auto str = StringTools::toString(env, packageName);
    env->DeleteLocalRef(packageName);
    return str;
}

auto NativeContext::getPackageManager() -> std::unique_ptr<NativePackageManager> &
{
    if (packageManager == nullptr)
    {
        packageManager = std::make_unique<NativePackageManager>();
        auto jPackageManager = env->CallObjectMethod(javaContext, methodGetPackManager);
        packageManager->initWithJobject(jPackageManager, env);
    }
    return packageManager;
}

auto NativeContext::getContentResolver() -> std::unique_ptr<NativeContentResolver> &
{
    getObject(contentResolver,methodGetContentResolver,NativeContentResolver);
}

auto NativeContext::getTelephonyManager() -> std::unique_ptr<NativeTelephonyManager> &
{
    if (telephonyManager == nullptr)
    {
        telephonyManager = std::make_unique<NativeTelephonyManager>();
        auto jTelephonyManager = env->CallObjectMethod(javaContext, methodGetTelephonyManager, TELEPHONY_SERVICE);
        telephonyManager->initWithJobject(jTelephonyManager, env->FindClass("android/telephony/TelephonyManager"), env);
    }
    return telephonyManager;
}
