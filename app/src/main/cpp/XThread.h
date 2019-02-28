//
// Created by Administrator on 2019/2/25 0025.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H

//sleep 毫秒
void XSleep(int ms);


//c++ 11 线程库
class XThread {
public:
    //启动线程
    virtual bool Start();
    //通过控制isExit安全停止线程（不一定成功）
    virtual void Stop();

    virtual void SetPause(bool isP);

    virtual bool IsPause(){
        isPausing = isPause;
        return isPause;
    }

    //入口主函数
    virtual void Main(){}

protected:
    bool isExit = false;
    bool isRunning = false;
    bool isPause = false;
    bool isPausing = false;

private:
    void ThreadMain();

};


#endif //XPLAY_XTHREAD_H
