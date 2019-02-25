#include <jni.h>
#include <string>

#include "FFDemux.h"
extern "C" JNIEXPORT jstring

JNICALL
Java_play_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IDemux *de = new FFDemux();
    de->Open("/storage/emulated/0/Download/meimei.mp4");

    return env->NewStringUTF(hello.c_str());
}
