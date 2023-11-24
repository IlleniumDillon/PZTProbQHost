#include "qpztdevice.h"
#include "qdebug.h"

QPztDevice::QPztDevice()
{
    //timerID = startTimer(20);
}

void QPztDevice::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == timerID)
    {
        /*static bool flag = false;
        if(flag)
        {
            float data[] = {1,2,0};
            Device_SendTarget<float>(data,3);
        }
        else
        {
            float data[] = {1.2,2.4,0};
            Device_SendTarget<float>(data,3);
        }

        flag = !flag;*/
    }
}

void QPztDevice::mesgManage(DevLinkRawData *data)
{
    switch(data->cmd)
    {
    case 0:
    {
        isConnected = true;
        //qDebug()<<"ok"
        break;
    }
    case 1:
    {
        isDeviceIdle = true;
        break;
    }
    case 2:
    {
        memcpy(&debugData,data->payload,sizeof(PztDebugData));
        //qDebug()<<(float)p[0]/65535.0*3.3<<" "<<(float)p[1]/65535.0*3.3;
        break;
    }
    }
}
