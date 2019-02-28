//
// Created by Administrator on 2019/2/27 0027.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "IResample.h"
#include "XLog.h"

IPlayer *IPlayer::Get(unsigned char index) {
    static IPlayer p[256];
    return &p[index];
}

void IPlayer::Main() {
    while (!isExit) {
        mux.lock();
        if (!audioPlay || !vdecode) {
            mux.unlock();
            XSleep(2);
            continue;
        }
        //同步
        //获取视频的pts  告诉视频
        int apts = audioPlay->pts;
//        XLOGE("IPlayer pts %d", apts);
        vdecode->synPts = apts;
        mux.unlock();
        XSleep(2);
    }
}

void IPlayer::Close() {
    mux.lock();
    //先关闭主体线程，再清理观察者
    //同步线程
    XThread::Stop();
    //解封装
    if (demux)
        demux->Stop();
    //解码
    if (vdecode)
        vdecode->Stop();
    if (adecode)
        adecode->Stop();
    if(audioPlay)
        audioPlay->Stop();

    //清理缓冲队列
    if (vdecode)
        vdecode->Clear();
    if (adecode)
        adecode->Clear();
    if (audioPlay)
        audioPlay->Clear();
    //清理资源
    if (audioPlay)
        audioPlay->Close();
    if (videoView)
        videoView->Close();
    if (vdecode)
        vdecode->Close();
    if (adecode)
        adecode->Close();
    if (demux)
        demux->Close();
    mux.unlock();
}

double IPlayer::PlayPos() {
    double pos = 0.0;
    mux.lock();
    int total = 0;
    if (demux)
        total = demux->totalMs;

    if (total > 0) {
        if (vdecode) {
            pos = vdecode->pts / (double) total;
        }
    }
    mux.unlock();
    return pos;
}

void IPlayer::SetPause(bool isP){
    mux.lock();
    XThread::SetPause(isP);
    if(demux)
        demux->SetPause(isP);
    if(vdecode)
        vdecode->SetPause(isP);
    if(adecode)
        adecode->SetPause(isP);
    if(audioPlay)
        audioPlay->SetPause(isP);
    mux.unlock();
}

bool IPlayer::Seek(double pos) {
    bool re = false;
    mux.lock();
    //暂停所有线程
    if (demux)
        re = demux->Seek(pos);
    mux.unlock();
    return re;
}


bool IPlayer::Open(const char *path) {
    Close();
    mux.lock();
    //解封装
    if (!demux || !demux->Open(path)) {
        mux.unlock();
        XLOGE("demux->Open %s failed!", path);
        return false;
    }

    //解码  解码可能不需要，如果是解封之后就是原始数据
    if (!vdecode || !vdecode->Open(demux->GetVPara(), isHardDecode)) {
        XLOGE("vdecode->Open %s failed!", path);
        //return false;
    }
    if (!adecode || !adecode->Open(demux->GetAPara())) {
        XLOGE("adecode->Open %s failed!", path);
        //return false;
    }

    //重采样 有可能不需要，解码后或者解封装后可能是直接能播放的数据
//    if (outPara.sample_rate <= 0)
    outPara = demux->GetAPara();
    if (!resample || !resample->Open(demux->GetAPara(), outPara)) {
        XLOGE("resample->Open %s failed!", path);
        //return false;
    }
    mux.unlock();
    return true;
}

bool IPlayer::Start() {
    mux.lock();
    if (audioPlay)
        audioPlay->StartPlay(outPara);
    if (vdecode)
        vdecode->Start();
    if (adecode)
        adecode->Start();
    if (!demux || !demux->Start()) {
        mux.unlock();
        XLOGE("demux->Start failed!");
        return false;
    }
    XThread::Start();
    mux.unlock();
    return true;
}

void IPlayer::InitView(void *win) {
    if (videoView) {
        videoView->Close();
        videoView->SetRender(win);
    }
}