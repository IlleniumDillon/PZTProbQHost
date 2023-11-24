#ifndef MVS_DRIVER_H
#define MVS_DRIVER_H

#include <QObject>
#include "MvCameraControl.h"
#include "opencv.hpp"

class MVS_driver : public QObject
{
    Q_OBJECT
public:
    explicit MVS_driver(QObject *parent = nullptr);
    bool MVS_DeviceList(void);
    bool MVS_OpenDevice(int indx);
    bool MVS_GetFrame(cv::Mat& frame);
    bool MVS_GuiConfig(void);
    bool MVS_CloseDevice(void);
    ~MVS_driver(void);
signals:
    void MVS_DeviceOpened(void);
    void MVS_GotFrame(void);

public:
    void* handle;
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    MV_FRAME_OUT stImageInfo = {0};
    MV_FRAME_OUT_INFO_EX stImageInfoEx = {0};
    QStringList deviceList;
    int indx;
    int Width = 2448;
    int Height = 2048;
};

#endif // MVS_DRIVER_H
