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

    //读取一帧数据，数据由调用者清理
    virtual XData Read();

    //总时长（毫秒）
    int totalMs = 0;

    FFDemux();


private:
    AVFormatContext *ic = 0;        //只能是构造是无参中才能这样赋初始值为零

};


#endif //XPLAY_FFDEMUX_H
