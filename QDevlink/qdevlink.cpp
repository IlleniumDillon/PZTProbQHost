#include "qdevlink.h"
#include "qcustomdevice.h"
#include "qdebug.h"

QDevLink::QDevLink(void* ptr,QObject *parent)
    : QObject{parent}
{
    DevLink_TxBuffer.resize(2048);
    DevLink_RxBuffer.resize(2048);

    DevLink_InitRawData(&rawTxData);

    devicePtr = ptr;
}

QDevLink::~QDevLink()
{
    serial.close();
    disconnect(&serial,SIGNAL(readyRead()),this,SLOT(readAll()));
}

void QDevLink::QDevlink_SetComPort(QString com)
{
    if(serial.isOpen())
    {
        serial.close();
    }
    serial.setPortName(com);
    serial.open(QIODeviceBase::ReadWrite);
    connect(&serial,SIGNAL(readyRead()),this,SLOT(readAll()));
}

/*void QDevLink::QDevLink_RegCallBack(uint8_t indx, DevLink_CallBack fun)
{
    devLink_CallBackList[indx] = fun;
}*/

void QDevLink::QDevLink_RecvAll(uint8_t len)
{
    uint8_t indx = 0;
    uint8_t state = 0;

    for( ; indx < len; indx++)
    {
        if((uint8_t)DevLink_RxBuffer[indx] == DEVLINK_FRAMEHEAD1)
        {
            state = 1;
            indx++;
            break;
        }
    }
    if(state == 0) return;
    if(indx >= len || (uint8_t)DevLink_RxBuffer[indx++] != DEVLINK_FRAMEHEAD2) return;

    if(indx >= len) return;
    rawRxData.cmd = (uint8_t)DevLink_RxBuffer[indx++];
    if(indx >= len) return;
    rawRxData.payloadLen = (uint8_t)DevLink_RxBuffer[indx++];
    if(indx >= len) return;
    rawRxData.payload = (uint8_t*)&DevLink_RxBuffer[indx];
    if(indx+1+rawRxData.payloadLen >= len) return;
    if((uint8_t)DevLink_RxBuffer[indx+1+rawRxData.payloadLen] != DEVLINK_FRAMETAIL) return;

    //DevLink_GetCheckNum(&rawRxData);

    //if((uint8_t)DevLink_RxBuffer[indx+rawRxData.payloadLen] != rawRxData.check) return;


    //devLink_CallBackList[rawRxData.cmd](&rawRxData);
    //emit devLink_CallBackEmit(&rawRxData);
    ((QCustomDevice*)devicePtr)->mesgManage(&rawRxData);
}

void QDevLink::QDevLink_SendData(uint8_t cmd, uint8_t payloadLen, uint8_t *payload)
{
    rawTxData.cmd = cmd;
    rawTxData.payloadLen = payloadLen;
    rawTxData.payload = payload;
    DevLink_GetCheckNum(&rawTxData);

    DevLink_TxBuffer[0] = rawTxData.frameHead1;
    DevLink_TxBuffer[1] = rawTxData.frameHead2;
    DevLink_TxBuffer[2] = rawTxData.cmd;
    DevLink_TxBuffer[3] = rawTxData.payloadLen;
    for(uint8_t i = 0; i < payloadLen; i++)
    {
        DevLink_TxBuffer[4+i] = rawTxData.payload[i];
    }
    DevLink_TxBuffer[4+payloadLen] = rawTxData.check;
    DevLink_TxBuffer[5+payloadLen] = rawTxData.frameTail;

    serial.write(DevLink_TxBuffer,6+payloadLen);
    //_DevLink_If_Write(NULL,NULL,6+payloadLen);
}

void QDevLink::readAll()
{
    if(inProcess) return;
    inProcess = true;
    DevLink_RxBuffer = serial.readAll();
    QDevLink_RecvAll(DevLink_RxBuffer.length());
    serial.flush();
    inProcess = false;
}


