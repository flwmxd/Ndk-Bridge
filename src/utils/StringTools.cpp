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

#include "utils/StringTools.h"
#include <memory.h>
namespace StringTools{

    auto toString(JNIEnv *env, jstring jstr) -> std::string {
        char*   rtn   =   NULL;
        jclass   clsstring   =   env->FindClass("java/lang/String");
        jstring   strencode   =   env->NewStringUTF("UTF-8");
        jmethodID   mid   =   env->GetMethodID(clsstring,   "getBytes",   "(Ljava/lang/String;)[B");
        jbyteArray   barr=   (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
        jsize   alen   =   env->GetArrayLength(barr);
        jbyte*   ba   =   env->GetByteArrayElements(barr,JNI_FALSE);
        if(alen   >   0)
        {
            rtn   = new char[alen+1];
            memcpy(rtn,ba,alen);
            rtn[alen]=0;
        }
        env->ReleaseByteArrayElements(barr,ba,0);
        std::string stemp(rtn);
        delete [] rtn;
        return stemp;
    }

    auto toJString(JNIEnv *env, const std::string &str) -> jstring {
        jclass strClass = (env)->FindClass("Ljava/lang/String;");
        jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
        jbyteArray bytes = (env)->NewByteArray(str.length());
        (env)->SetByteArrayRegion(bytes, 0, str.length(), (jbyte*)str.c_str());
        jstring encoding = (env)->NewStringUTF("UTF-8");
        return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
    }

};

