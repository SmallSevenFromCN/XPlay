#include "FFDemux.h"
#include "XLog.h"

extern "C" {
#include <libavformat/avformat.h>
}

//打开文件，或者流媒体  rmtp http rtsp
bool FFDemux::Open(const char *url) {

    XLOGI("Open file %s begin", url);
    int re = avformat_open_input(&ic, url, 0, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGI("FFDemux open %s failed", buf);
        return false;
    }
    XLOGI("FFDemux open %s success", url);

    //读取文件信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGI("avformat_find_stream_info %s failed", buf);
    }

    //duration不一定有的
    this->totalMs = ic->duration / (AV_TIME_BASE / 1000);
    XLOGI("total ms = %d", totalMs);

    return true;
}

//读取一帧数据，数据由调用者清理
XData FFDemux::Read() {
    if (!ic)
        return XData();
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic, pkt);
    if (re != 0) {
        av_packet_free(&pkt);
        return XData();
    }
//    XLOGI("pack size is %d pts %lld", pkt->size,pkt->pts);
    d.data = (unsigned char*)pkt;
    d.size = pkt->size;

    return d;
}

FFDemux::FFDemux() {
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;

        //注册所有解封器
        av_register_all();

        //注册所有的解码器
        avcodec_register_all();

        //初始化网络
        avformat_network_init();
        XLOGI("register ffmpeg!");
    }
}
