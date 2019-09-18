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


#include <string.h>
#include "NativeInterface.h"

NativeInterface::~NativeInterface() {
    env->DeleteLocalRef(thiz);
    env->DeleteLocalRef(clazz);
}

auto NativeInterface::initWithJobject(jobject obj, JNIEnv *env) -> bool {
    return initWithJobject(obj,env->GetObjectClass(obj),env);
}

auto NativeInterface::initWithJobject(jobject obj, jclass clazz, JNIEnv *env) -> bool {
    this->thiz = obj;
    this->env = env;
    this->clazz = clazz;
    return init();
}

auto NativeInterface::byteArrayToVector(jbyteArray array) -> std::vector<int8_t> {
    auto len = env->GetArrayLength(array);
    auto elems = env->GetByteArrayElements(array,0);
    std::vector<int8_t> data(len);
    memcpy(&data[0],elems,sizeof(jbyte) * len);
    return data;
}
