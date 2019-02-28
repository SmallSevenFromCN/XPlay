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


extern "C"
JNIEXPORT void JNICALL
Java_play_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayerPorxy::Get()->InitView(win);
}


extern "C"
JNIEXPORT void JNICALL
Java_play_xplay_OpenUrlActivity_Open(JNIEnv *env, jobject instance, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);
    IPlayerPorxy::Get()->Open(path);
    IPlayerPorxy::Get()->Start();
    env->ReleaseStringUTFChars(path_, path);
}