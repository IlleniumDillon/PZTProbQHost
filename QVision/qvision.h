#ifndef QVISION_H
#define QVISION_H

#include <QObject>
#include <QTimerEvent>
#include <mvs_driver.h>
#include <QMutex>
#include <opencv2/xfeatures2d.hpp>

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
    cv::Mat Gframe;
    cv::Mat templ;
    cv::Mat res;
    cv::Rect frameRoi, templRoi;
    cv::Ptr<cv::xfeatures2d::SURF>detector = cv::xfeatures2d::SURF::create(1500);
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
