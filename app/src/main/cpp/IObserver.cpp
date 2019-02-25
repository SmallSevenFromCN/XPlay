//
// Created by Administrator on 2019/2/25 0025.
//

#include "IObserver.h"

//观察者接收数据函数
void IObserver::AddObs(IObserver *obs) {
    if (!obs)
        return;
    mux.lock();
    obss.push_back(obs);
    mux.unlock();
}


//主体函数 添加观察者
void IObserver::Notify(XData data) {
    mux.lock();
    for (int i = 0; i < obss.size(); ++i) {
        obss[i]->Update(data);
    }
    mux.unlock();
}