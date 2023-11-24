#ifndef QCUSTOMDEVICE_H
#define QCUSTOMDEVICE_H

#include <QObject>
#include <QTimerEvent>
#include "qdevlink.h"

class QCustomDevice : public QObject
{
    typedef void (QCustomDevice::* DeviceCallBack)(DevLinkRawData* p);
    Q_OBJECT
public:
    explicit QCustomDevice(QObject *parent = nullptr);
    ~QCustomDevice();

    void Device_SetComPort(QString com);

    void Device_TestConnection(void);

    template <typename T>
    void Device_SendTarget(T* data, uint8_t len)
    {
        devLink->QDevLink_SendData(1,sizeof(T)*len,(uint8_t*)data);
    }

    void Device_StartControl(void);

    void Device_StopControl(void);

    int timerID;

signals:

public slots:
    virtual void mesgManage(DevLinkRawData* data)
    {
        switch(data->cmd)
        {
        case 0:
        {
            isConnected = true;
            break;
        }
        case 1:
        {
            isDeviceIdle = true;
            break;
        }
        case 2:
        {
            break;
        }
        }
    }


public:
    QDevLink* devLink;

    bool isConnected = false;
    bool isDeviceIdle = true;
};



//void temp_callback00(DevLinkRawData* p);

#endif // QCUSTOMDEVICE_H
