#include "qcustomdevice.h"

QCustomDevice::QCustomDevice(QObject *parent)
    : QObject{parent}
{
    devLink = new QDevLink(this);
}

QCustomDevice::~QCustomDevice()
{

}

void QCustomDevice::Device_SetComPort(QString com)
{
    devLink->QDevlink_SetComPort(com);
    //connect(devLink,SIGNAL(devLink_CallBackEmit(DevLinkRawData*)),this,SLOT(mesgManage(DevLinkRawData*)));
}

void QCustomDevice::Device_TestConnection(void)
{
    devLink->QDevLink_SendData(0,0,0);
}

void QCustomDevice::Device_StartControl()
{
    devLink->QDevLink_SendData(2,0,0);
}

void QCustomDevice::Device_StopControl()
{
    devLink->QDevLink_SendData(3,0,0);
}

/*template<typename T>
void QCustomDevice::Device_SendTarget(T* data, uint8_t len)
{
    devLink->QDevLink_SendData(1,sizeof(T)*len,data);
}*/

