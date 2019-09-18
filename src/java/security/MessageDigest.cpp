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

#include "java/security/MessageDigest.h"
#include <string>

auto MessageDigest::getInstance(JNIEnv *env,const std::string & str) -> MessageDigest & {
    static MessageDigest digest;
    auto clazz = env->FindClass("java/security/MessageDigest");
    auto method = env->GetStaticMethodID(clazz, "getInstance", "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jstring paramString = env->NewStringUTF(str.c_str());
    jobject obj = env->CallStaticObjectMethod(clazz, method, paramString);
    digest.initWithJobject(obj,clazz,env);
    env->DeleteLocalRef(paramString);
    return digest;
}

auto MessageDigest::digest(const std::vector<int8_t> & data) -> std::vector<int8_t> {
    auto method = env->GetMethodID(clazz, "digest", "([B)[B");
    jbyteArray jarray = env->NewByteArray(data.size());
    env->SetByteArrayRegion(jarray,0,data.size(),data.data());
    jbyteArray array = (jbyteArray)env->CallObjectMethod(thiz,method,jarray);
    std::vector<int8_t> arr =  byteArrayToVector(array);
    env->DeleteLocalRef(array);
    env->DeleteLocalRef(jarray);
    return arr;
}

auto MessageDigest::init() -> bool {
    return false;
}
