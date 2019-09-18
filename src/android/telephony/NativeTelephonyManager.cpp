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
// Created by Prime on 2019/1/17.
//

#include "NativeTelephonyManager.h"
#include <string>
auto NativeTelephonyManager::init() -> bool {
    return true;
}

auto NativeTelephonyManager::getDeviceId() -> const std::string {
    jmethodID getDeviceId = env->GetMethodID(clazz, "getDeviceId", "()Ljava/lang/String;");
    jstring deviceId = static_cast<jstring>(env->CallObjectMethod(thiz, getDeviceId));
    return env->GetStringUTFChars(deviceId, 0);
}
