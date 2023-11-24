#ifndef QDEVLINK_H
#define QDEVLINK_H

#include <QObject>
#include <QSerialPort>
#include <stdint.h>

#define DEVLINK_PACK_MAX_LEN (64)

#define DEVLINK_FRAMEHEAD1 (0X5A)
#define DEVLINK_FRAMEHEAD2 (0XA5)
#define DEVLINK_FRAMETAIL (0XFF)

typedef struct devlinkdata
{
    uint8_t cmd;
    uint8_t payloadLen;
    uint8_t payload[DEVLINK_PACK_MAX_LEN];
}DevLinkData;

typedef struct devlinkrawdata
{
    uint8_t frameHead1;
    uint8_t frameHead2;
    uint8_t cmd;
    uint8_t payloadLen;
    uint8_t* payload;
    uint8_t check;
    uint8_t frameTail;
}DevLinkRawData;

typedef void (*DevLink_CallBack)(void*);

inline static void DevLink_InitRawData(DevLinkRawData* data);
inline static void DevLink_GetCheckNum(DevLinkRawData* data);

inline void DevLink_InitRawData(DevLinkRawData* data)
{
    data->frameHead1 = DEVLINK_FRAMEHEAD1;
    data->frameHead2 = DEVLINK_FRAMEHEAD2;
    data->check = 0;
    data->frameTail = DEVLINK_FRAMETAIL;
}

inline void DevLink_GetCheckNum(DevLinkRawData* data)
{
    //data->check = data->frameHead1;
    //data->check = data->check ^ data->frameHead2;
    data->check = data->cmd;
    data->check = data->check ^ data->payloadLen;
    for (uint8_t i = 0; i < data->payloadLen; i++)
    {
        data->check = data->check ^ data->payload[i];
    }
    //data->check = data->check ^ data->frameTail;
}

class QDevLink : public QObject
{
    Q_OBJECT
public:
    explicit QDevLink(void* ptr,QObject *parent = nullptr);

    ~QDevLink();

    void QDevlink_SetComPort(QString com);

    //void QDevLink_RegCallBack(uint8_t indx, DevLink_CallBack fun);

    void QDevLink_RecvAll(uint8_t len);

    void QDevLink_SendData(uint8_t cmd, uint8_t payloadLen, uint8_t* payload);

public slots:
    void readAll();
signals:
    void devLink_CallBackEmit(DevLinkRawData* data);
private:
    QSerialPort serial;

    QByteArray DevLink_TxBuffer;
    QByteArray DevLink_RxBuffer;

    DevLinkRawData rawRxData;
    DevLinkRawData rawTxData;

    void* devicePtr;

    bool inProcess = false;

public:
    //DevLink_CallBack devLink_CallBackList[255];


};


#endif // QDEVLINK_H
