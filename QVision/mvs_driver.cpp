#include "mvs_driver.h"
#include "qdebug.h"

MVS_driver::MVS_driver(QObject *parent) : QObject(parent)
{

}

bool MVS_driver::MVS_DeviceList()
{
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet)
    {
        printf("Enum Devices fail! nRet [0x%x]\n", nRet);
        return false;
    }
    for(unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
    {
        QString name = QString((char*)stDeviceList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.chModelName);
        deviceList.append(name);
    }
    return true;
}

bool MVS_driver::MVS_OpenDevice(int indx)
{
    int nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[indx]);
    if (MV_OK != nRet)
    {
        printf("Create Handle fail! nRet [0x%x]\n", nRet);
        return false;
    }

    nRet = MV_CC_OpenDevice(handle);
    if (MV_OK != nRet)
    {
        printf("Open Device fail! nRet [0x%x]\n", nRet);
        return false;
    }

    if (stDeviceList.pDeviceInfo[indx]->nTLayerType == MV_GIGE_DEVICE)
    {
        int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
        if (nPacketSize > 0)
        {
            nRet = MV_CC_SetIntValue(handle,"GevSCPSPacketSize",nPacketSize);
            if(nRet != MV_OK)
            {
                printf("Warning: Set Packet Size fail nRet [0x%x]!", nRet);
            }
        }
        else
        {
            printf("Warning: Get Packet Size fail nRet [0x%x]!", nPacketSize);
        }
    }

    nRet = MV_CC_SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_OFF);
    if (MV_OK != nRet)
    {
        printf("Set Trigger Mode fail! nRet [0x%x]\n", nRet);
        return false;
    }

    nRet = MV_CC_SetIntValue(handle, "Width", Width);
    if (MV_OK != nRet)
    {
        return false;
    }

    nRet = MV_CC_SetIntValue(handle, "Height", Height);
    if (MV_OK != nRet)
    {
        return false;
    }

    nRet = MV_CC_SetEnumValue(handle, "PixelFormat", PixelType_Gvsp_Mono8);
    if (MV_OK != nRet)
    {
        return false;
    }

    /*nRet = MV_CC_SetBoolValue(handle, "ReverseX", true);
    if (MV_OK != nRet)
    {
        return false;
    }*/

    nRet = MV_CC_SetFloatValue(handle, "AcquisitionFrameRate", 10);
    if (MV_OK != nRet)
    {
        return false;
    }

    /*nRet = MV_CC_OpenParamsGUI(handle);
    if (MV_OK != nRet)
    {
        printf("Open Parameters Configuration GUI fail! nRet [0x%x]\n", nRet);
        return false;
    }*/

    nRet = MV_CC_StartGrabbing(handle);
    if (MV_OK != nRet)
    {
        printf("Start Grabbing fail! nRet [0x%x]\n", nRet);
        return false;
    }


    return true;
}

bool MVS_driver::MVS_GetFrame(cv::Mat &frame)
{
    /*int nRet = MV_CC_GetImageBuffer(handle, &stImageInfo, 1000);
    if (nRet == MV_OK)
    {
        frame = cv::Mat(stImageInfo.stFrameInfo.nHeight,stImageInfo.stFrameInfo.nWidth,CV_8UC1,stImageInfo.pBufAddr).clone();
        MV_CC_FreeImageBuffer(handle, &stImageInfo);
    }*/
    int nRet = MV_CC_GetOneFrameTimeout(handle,frame.data,frame.cols*frame.rows,&stImageInfoEx,1);
    return true;
}

bool MVS_driver::MVS_GuiConfig()
{
    int nRet = MV_CC_OpenParamsGUI(handle);
    if (MV_OK != nRet)
    {
        printf("Open Parameters Configuration GUI fail! nRet [0x%x]\n", nRet);
        return false;
    }
    return true;
}

bool MVS_driver::MVS_CloseDevice()
{
    int nRet = MV_CC_StopGrabbing(handle);
    if (MV_OK != nRet)
    {
        printf("Stop Grabbing fail! nRet [0x%x]\n", nRet);
    }
    nRet = MV_CC_CloseDevice(handle);
    if (MV_OK != nRet)
    {
        printf("Close Device fail! nRet [0x%x]\n", nRet);
    }
    return true;
}

MVS_driver::~MVS_driver()
{
    //qDebug()<<"debug";
    int nRet = MV_CC_StopGrabbing(handle);
    if (MV_OK != nRet)
    {
        printf("Stop Grabbing fail! nRet [0x%x]\n", nRet);
    }
    nRet = MV_CC_CloseDevice(handle);
    if (MV_OK != nRet)
    {
        printf("Close Device fail! nRet [0x%x]\n", nRet);
    }
    nRet = MV_CC_DestroyHandle(handle);
    if (MV_OK != nRet)
    {
        printf("Destroy Handle fail! nRet [0x%x]\n", nRet);
    }
}
