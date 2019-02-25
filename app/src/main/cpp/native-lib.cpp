#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "XLog.h"


class TestObs : public IObserver {
public:
    void Update(XData d) {
        XLOGI("TestObs Update data size is %d", d.size);
    }
};


extern "C" JNIEXPORT jstring
JNICALL
Java_play_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    /////////////////////////////////////
    //测试用代码
    TestObs *tobs = new TestObs();
    IDemux *de = new FFDemux();
    de->AddObs(tobs);
    de->Open("/storage/emulated/0/Download/meimei.mp4");
    de->Start();
    XSleep(3000);
    de->Stop();


//    for (;;) {
//        XData d = de->Read();
//        XLOGI("Read data size is %d", d.size);
//
//    }




    return env->NewStringUTF(hello.c_str());
}
