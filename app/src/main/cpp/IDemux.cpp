//
// Created by Administrator on 2019/2/24 0024.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {
    while (!isExit){
        if(IsPause()){
            XSleep(2);
            continue;
        }
        XData d = Read();
        if (d.size>0)
            Notify(d);
        else
            XSleep(2);
//        XLOGI("IDemux Read %d", d.size);
    }

}