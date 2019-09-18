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

//
// Created by Prime on 2018/7/5.
//

#include "android/content/pm/NativePackageManager.h"
#include "android/content/pm/NativePackageInfo.h"
#include "utils/StringTools.h"

auto NativePackageManager::getPackageInfo(const std::string &packageName, int32_t flag) -> std::unique_ptr<NativePackageInfo>
{
    // if(info == nullptr){
    auto info = std::make_unique<NativePackageInfo>();
    auto methodId = env->GetMethodID(clazz, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jstring name = env->NewStringUTF(packageName.c_str()); //StringUtils::toJString(env,packageName);//TODO leak memory
    jobject packageInfo = env->CallObjectMethod(thiz, methodId, name, flag);
    env->DeleteLocalRef(name);
    info->flag = flag;
    info->initWithJobject(packageInfo, env);

    return info;
}

auto NativePackageManager::init() -> bool
{
    return true;
}
