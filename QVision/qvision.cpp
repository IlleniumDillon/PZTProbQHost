#include "qvision.h"
#include "qdebug.h"
#include "vector"

QVision::QVision(QObject *parent)
    : QObject{parent}
{
    frame = cv::Mat(2048,2448,CV_8UC1);
    templ = cv::Mat(2048,2448,CV_8UC3);
    driver.MVS_DeviceList();
    driver.MVS_OpenDevice(0);
    timerID = startTimer(20,Qt::PreciseTimer);
}

void QVision::QVision_Init()
{
    isShow = true;
}

void QVision::QVision_Start()
{
    isStart = true;
}

void QVision::QVision_Stop()
{
    isStart = false;
}

void QVision::QVision_GframeProcessInit()
{
    //templ = frame.clone();
    Gframe = cv::Mat(4000,4000,CV_8UC3,cv::Scalar(0x1F,0x1E,0X33));
    cv::cvtColor(frame,templ,cv::COLOR_GRAY2BGR);
    templ.copyTo(Gframe(cv::Rect(Gframe.cols - templ.cols, Gframe.rows - templ.rows, templ.cols, templ.rows)));
    //templ = Gframe;
    frameRoi = cv::Rect(frame.cols / 8*3, frame.rows / 8*3, frame.cols /4, frame.rows /4);
}

void QVision::QVision_GframeProcessOnce()
{
    cv::cvtColor(frame,templ,cv::COLOR_GRAY2BGR);

    std::vector<cv::KeyPoint>keypoint_Gframe, keypoint_frame;
    cv::Mat descriptor_Gframe, descriptor_frame;
    detector->detectAndCompute(Gframe, cv::Mat(), keypoint_Gframe, descriptor_Gframe);
    detector->detectAndCompute(templ, cv::Mat(), keypoint_frame, descriptor_frame);

    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch>matches;
    matcher.match(descriptor_Gframe, descriptor_frame, matches);

    double Max = 0.0;
    for (int i = 0; i < matches.size(); i++)
    {
        //float distance –>代表这一对匹配的特征点描述符（本质是向量）的欧氏距离，数值越小也就说明两个特征点越相像。
        double dis = matches[i].distance;
        if (dis > Max)
        {
            Max = dis;
        }
    }

    //筛选出匹配程度高的关键点
    std::vector<cv::DMatch>goodmatches;
    std::vector<cv::Point2f>goodkeypoint_Gframe, goodkeypoint_frame;
    for (int i = 0; i < matches.size(); i++)
    {
        double dis = matches[i].distance;
        if (dis < 0.15 * Max)
        {
            /*
                以右图做透视变换
                左图->queryIdx:查询点索引（查询图像）
                右图->trainIdx:被查询点索引（目标图像）
                */
            //注：对image_right图像做透视变换，故goodkeypoint_left对应queryIdx，goodkeypoint_right对应trainIdx
            //int queryIdx –>是测试图像的特征点描述符（descriptor）的下标，同时也是描述符对应特征点（keypoint)的下标。
            goodkeypoint_Gframe.push_back(keypoint_Gframe[matches[i].queryIdx].pt);
            //int trainIdx –> 是样本图像的特征点描述符的下标，同样也是相应的特征点的下标。
            goodkeypoint_frame.push_back(keypoint_frame[matches[i].trainIdx].pt);
            goodmatches.push_back(matches[i]);
        }
    }

    cv::Mat H = findHomography(goodkeypoint_frame, goodkeypoint_Gframe, cv::RANSAC);
    cv::Mat WarpImg;
    warpPerspective(templ, WarpImg, H, Gframe.size(),0,0, cv::Scalar(0x1F,0x1E,0X33));

    for (int a = 0; a < Gframe.rows; a++)
    {
        for (int b = 0; b < Gframe.cols; b++)
        {
            cv::Vec3b GframePix = Gframe.at<cv::Vec3b>(a,b);
            cv::Vec3b WarpImgPix = WarpImg.at<cv::Vec3b>(a, b);
            bool con1 = (GframePix == cv::Vec3b(0x1F,0x1E,0X33));
            bool con2 = (WarpImgPix == cv::Vec3b(0x1F,0x1E,0X33));
            if (con1 && con2)
            {
                ;
            }
            else if (!con1 && con2)
            {
                ;
            }
            else if (con1 && !con2)
            {
                Gframe.at<cv::Vec3b>(a, b) = WarpImgPix;
            }
            else
            {
                Gframe.at<cv::Vec3b>(a, b) = WarpImgPix / 2 + GframePix / 2;
            }
        }
    }
}

void QVision::QVision_GframeFix()
{
    int fristRow = -1, firstCol = -1;
    for (int a = 0; a < Gframe.rows; a++)
    {
        for (int b = 0; b < Gframe.cols; b++)
        {
            cv::Vec3b GframePix = Gframe.at<cv::Vec3b>(a,b);
            bool con1 = (GframePix == cv::Vec3b(0x1F,0x1E,0X33));
            if(!con1)
            {
                fristRow = a+1;
                //firstCol = b;
                break;
            }
        }
        if(fristRow > 0)
        {
            break;
        }
    }

    for (int b = 0; b < Gframe.cols; b++)
    {
        for (int a = 0; a < Gframe.rows; a++)
        {
            cv::Vec3b GframePix = Gframe.at<cv::Vec3b>(a,b);
            bool con1 = (GframePix == cv::Vec3b(0x1F,0x1E,0X33));
            if(!con1)
            {
                //fristRow = a;
                firstCol = b+1;
                break;
            }
        }
        if(firstCol > 0)
        {
            break;
        }
    }

    qDebug() << fristRow << " " << firstCol;

    if(fristRow < 0 || firstCol < 0) return;
    cv::Mat temp(Gframe.rows-fristRow,Gframe.cols-firstCol,CV_8UC3);
    temp = Gframe(cv::Rect(firstCol,fristRow,temp.cols,temp.rows)).clone();
    Gframe = cv::Mat(temp.size(),CV_8UC3);
    for (int a = 0; a < temp.rows; a++)
    {
        for (int b = 0; b < temp.cols; b++)
        {
            cv::Vec3b tempPix = temp.at<cv::Vec3b>(a,b);
            Gframe.at<cv::Vec3b>(a,b) = tempPix;
        }
    }
}

void QVision::QVision_ProcessOnce()
{
    cv::cvtColor(frame,templ,cv::COLOR_GRAY2BGR);

    ///TODO: detect prob and frectures

    ///TODO: mask picture under prob

    std::vector<cv::KeyPoint>keypoint_Gframe, keypoint_frame;
    cv::Mat descriptor_Gframe, descriptor_frame;
    detector->detectAndCompute(Gframe, cv::Mat(), keypoint_Gframe, descriptor_Gframe);
    detector->detectAndCompute(templ, cv::Mat(), keypoint_frame, descriptor_frame);

    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch>matches;
    matcher.match(descriptor_Gframe, descriptor_frame, matches);

    double Max = 0.0;
    for (int i = 0; i < matches.size(); i++)
    {
        //float distance –>代表这一对匹配的特征点描述符（本质是向量）的欧氏距离，数值越小也就说明两个特征点越相像。
        double dis = matches[i].distance;
        if (dis > Max)
        {
            Max = dis;
        }
    }

    //筛选出匹配程度高的关键点
    std::vector<cv::DMatch>goodmatches;
    std::vector<cv::Point2f>goodkeypoint_Gframe, goodkeypoint_frame;
    for (int i = 0; i < matches.size(); i++)
    {
        double dis = matches[i].distance;
        if (dis < 0.15 * Max)
        {
            /*
                以右图做透视变换
                左图->queryIdx:查询点索引（查询图像）
                右图->trainIdx:被查询点索引（目标图像）
                */
            //注：对image_right图像做透视变换，故goodkeypoint_left对应queryIdx，goodkeypoint_right对应trainIdx
            //int queryIdx –>是测试图像的特征点描述符（descriptor）的下标，同时也是描述符对应特征点（keypoint)的下标。
            goodkeypoint_Gframe.push_back(keypoint_Gframe[matches[i].queryIdx].pt);
            //int trainIdx –> 是样本图像的特征点描述符的下标，同样也是相应的特征点的下标。
            goodkeypoint_frame.push_back(keypoint_frame[matches[i].trainIdx].pt);
            goodmatches.push_back(matches[i]);
        }
    }

    cv::Mat H = findHomography(goodkeypoint_frame, goodkeypoint_Gframe, cv::RANSAC);
    cv::Mat ori = cv::Mat::zeros(3, 1, CV_64FC1); ori.at<double>(2) = 1;
    cv::Mat dpix = H * ori;

    px = dpix.at<double>(1);
    py = dpix.at<double>(0);

    qDebug() << px << " " << py;
}

void QVision::QVision_Process()
{
    while(isStart)
    {
        QTime _Timer = QTime::currentTime().addMSecs(100);
        QVision_ProcessOnce();
        while( QTime::currentTime() < _Timer ) QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
    }
}

void QVision::QVision_ProcessInit()
{
    //detector->detectAndCompute(Gframe, cv::Mat(), Gkeypoints, Gdescriptors);
    QFuture<void> thread = QtConcurrent::run(&QVision::QVision_Process,this);
    watcher.setFuture(thread);
}

void QVision::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == timerID)
    {
        if(isStart)
        {
            driver.MVS_GetFrame(frame);
            newFrame = true;
            //QVision_ProcessOnce();
        }
        if(isShow)
        {
            emit QVision_NewFrameReady(frame);
        }
    }
}

QVision::~QVision()
{
    isStart = false;
    isShow = false;
    while(watcher.isRunning());
    killTimer(timerID);
}
