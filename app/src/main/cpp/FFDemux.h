//
// Created by Administrator on 2019/2/24 0024.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H



#include "XData.h"
struct AVFormatContext;

#include "IDemux.h"

class FFDemux : public IDemux {
public:
    //打开文件，或者流媒体  rmtp http rtsp
    virtual bool Open(const char *url);

    //seek位置 pos 0.0~1.0
    virtual bool Seek(double pos);

    virtual void Close();

    //获取视频参数
    virtual XParameter GetVPara();

    //获取音频参数
    virtual XParameter GetAPara();

    //读取一帧数据，数据由调用者清理
    virtual XData Read();



    FFDemux();


private:
    AVFormatContext *ic = 0;        //只能是构造是无参中才能这样赋初始值为零
    std::mutex mux;
    int audioStream = 1;
    int videoStream = 0;

};


#endif //XPLAY_FFDEMUX_H
