#ifndef QVISION_H
#define QVISION_H

#include <QObject>
#include <QTimerEvent>
#include <mvs_driver.h>
#include <QMutex>

#include <opencv2/xfeatures2d.hpp>
#include "opencv.hpp"
#include <opencv2/core/cuda.hpp>
#include <opencv2/gapi.hpp>

#include "opencv2/cudaarithm.hpp"

#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>
#include <opencv2/cudawarping.hpp>

#include <QtConcurrent>
#include <QFuture>


class QVision : public QObject
{
    Q_OBJECT
public:
    explicit QVision(QObject *parent = nullptr);

    void QVision_Init(void);
    void QVision_Start(void);
    void QVision_Stop(void);
    void QVision_GframeProcessInit(void);
    void QVision_GframeProcessOnce(void);
    void QVision_GframeFix(void);
    void QVision_ProcessOnce(void);
    void QVision_Process(void);
    void QVision_ProcessInit(void);
    void timerEvent(QTimerEvent* event);

    ~QVision(void);

signals:
    void QVision_NewFrameReady(cv::Mat frame);
public:
    MVS_driver driver;
    cv::Mat frame;
    cv::cuda::GpuMat frame_gpu;
    cv::cuda::GpuMat Gframe_gpu;
    cv::Mat Gframe;
    cv::Mat templ;
    cv::Mat res;
    cv::Rect frameRoi, templRoi;
    cv::Ptr<cv::cuda::SURF_CUDA>detector = new cv::cuda::SURF_CUDA(1000);
    //std::vector<cv::KeyPoint>Gkeypoints;
    //cv::Mat Gdescriptors;
    float dx = 0,dy = 0,x = 0,y = 0;
    float px = -1, py = -1;
    int timerID;
    bool isStart = false;
    bool isShow = false;
    bool newFrame = false;

    QFutureWatcher<void> watcher;

    //QMutex* mutex;
};

#endif // QVISION_H
