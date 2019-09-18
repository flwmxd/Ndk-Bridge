# Ndk-Bridge


Ndk-Bridge is desgined for simplifying ndk to java calls. 


you can easily to call java methods in your native apps like game-engine;

## Example
``` cpp

#include <jni.h>
#include <string>
#include "NativeContext.h"
#include "java/security/MessageDigest.h"


auto getSignature(JNIEnv *env, jobject8 /* this */thiz) -> std::string {

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
    return sha;
}

auto getImei(JNIEnv *env, jobject /* this */thiz) -> std::string
{
	NativeContext context(thiz, env);
	return context.getTelephonyManager()->getDeviceId();
}

```

## Compilation

### Use ndk-build
0. add include file in your code

``` cpp
#include <NativeBridge.h>
```


1. add LOCAL_STATIC_LIBRARIES in you app Android.mk
``` c
LOCAL_STATIC_LIBRARIES := .... ndk_bridge
```
2. add import module at last ine in you app Android.mk
``` c
$(call import-module,ndk_bridge)
```

3. build it
``` c 
call ndk-build
```

### Use cmake 
it will be supported in the next version