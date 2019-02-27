#include "FFDemux.h"
#include "XLog.h"

extern "C" {
#include <libavformat/avformat.h>
}

//分数转为浮点数
static double r2d(AVRational r) {
    return r.num == 0 || r.den == 0 ? 0. : (double) r.num / (double) r.den;
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
    GetVPara();
    GetAPara();
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
    d.data = (unsigned char *) pkt;
    d.size = pkt->size;
    if (pkt->stream_index == audioStream) {
        d.isAudio = true;
    } else if (pkt->stream_index == videoStream) {
        d.isAudio = false;
    } else {
        av_packet_free(&pkt);
        return XData();
    }

    //转换pts
    pkt->pts = pkt->pts * (1000 * r2d(ic->streams[pkt->stream_index]->time_base));
    pkt->dts = pkt->dts * (1000 * r2d(ic->streams[pkt->stream_index]->time_base));

    d.pts = (int)pkt->pts;
//    XLOGE("demux pts %d",d.pts);

    return d;
}

//获取视频参数
XParameter FFDemux::GetVPara() {
    if (!ic) {
        XLOGE("GetVPara failed!  ic  is NULL!");
        return XParameter();
    }
    //获取了视频流索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (re < 0) {
        XLOGE("av_find_best_stream  VPara failed!");
        return XParameter();

    }
    videoStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;

    return para;
}

//获取音频参数
XParameter FFDemux::GetAPara() {
    if (!ic) {
        XLOGE("GetAPara failed!  ic  is NULL!");
        return XParameter();
    }
    //获取了音频流索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (re < 0) {
        XLOGE("av_find_best_stream  APara failed!");
        return XParameter();

    }
    audioStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    para.channels = ic->streams[re]->codecpar->channels;
    para.sample_rate = ic->streams[re]->codecpar->sample_rate;
    return para;
}


//读取一帧数据，数据由调用者清理
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
