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

#include <string.h>
#include "android/content/pm/NativeSignature.h"

auto NativeSignature::init() -> bool {

    return true;
}

auto NativeSignature::toByteArray() -> std::vector<int8_t> {
    auto methodId = env->GetMethodID(clazz, "toByteArray", "()[B");
    jbyteArray bytes = (jbyteArray)env->CallObjectMethod(thiz, methodId);
    auto len = env->GetArrayLength(bytes);
    auto elems = env->GetByteArrayElements(bytes,0);
    std::vector<int8_t> data(len);
    memcpy(&data[0],elems,sizeof(jbyte) * len);
    env->DeleteLocalRef(bytes);
    return data;
}
