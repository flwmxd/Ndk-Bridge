#include <jni.h>
#include <string>

#include "NativeContext.h"
#include "java/security/MessageDigest.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_oneplus_ndkcall_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */thiz) {

    NativeContext context(thiz,env);
    const char hexcode[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

    std::string package = context.getPackageName();


    auto & pm = context.getPackageManager();
    auto & info = pm->getPackageInfo(package);
    auto & sign = info->signatures[0];

    std::vector<int8_t> array = sign.toByteArray();
    std::vector<int8_t> publicKey = MessageDigest::getInstance(env,"SHA1").digest(array);
    std::string sha;
    for(auto a : publicKey){
        sha.append(1,hexcode[((unsigned char)a) / 16]);
        sha.append(1, hexcode[((unsigned char)a) % 16]);
        sha.append(":");
    }
    return env->NewStringUTF(sha.c_str());
}
