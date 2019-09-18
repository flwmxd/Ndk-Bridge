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

#include "android/content/pm/NativePackageInfo.h"
#include "utils/StringTools.h"
auto NativePackageInfo::init() -> bool
{
    if (flag == 0x40)
    {
        jfieldID fieldId = env->GetFieldID(clazz, "signatures", "[Landroid/content/pm/Signature;");
        jobjectArray objArr = (jobjectArray)env->GetObjectField(thiz, fieldId);
        auto length = env->GetArrayLength(objArr);
        for (int16_t i = 0; i < length; i++)
        {
            auto o = env->GetObjectArrayElement(objArr, i);
            signatures.emplace(signatures.end())->initWithJobject(o, env);
        }
        env->DeleteLocalRef(objArr);
    }
    else
    {
        jfieldID fieldId = env->GetFieldID(clazz, "versionName", "Ljava/lang/String;");
        jstring objVersion = (jstring)env->GetObjectField(thiz, fieldId);
        versionName = StringTools::toString(env, objVersion);
        env->DeleteLocalRef(objVersion);
    }
    return true;
}