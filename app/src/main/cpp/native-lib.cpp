#include <jni.h>
#include <string>
#include <android/native_window_jni.h>


#include "XLog.h"
#include "FFPlayerBuilder.h"
#include "IPlayerPorxy.h"

static IPlayer *player = NULL;
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res) {
    IPlayerPorxy::Get()->Init(vm);
    return JNI_VERSION_1_4;
}


extern "C" JNIEXPORT jstring
JNICALL
Java_play_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IPlayerPorxy::Get()->Open("/storage/emulated/0/Download/meimei.mp4");
    IPlayerPorxy::Get()->Start();
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_play_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayerPorxy::Get()->InitView(win);
}