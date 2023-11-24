#include "qvision.h"
#include "qdebug.h"
#include "vector"

QVision::QVision(QObject *parent)
    : QObject{parent}
{
    frame = cv::Mat(2048,2448,CV_8UC1);
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
    Gframe = frame.clone();
    //templ = Gframe;
    frameRoi = cv::Rect(frame.cols / 8*3, frame.rows / 8*3, frame.cols /4, frame.rows /4);
}

void QVision::QVision_GframeProcessOnce()
{
   /* double minVal, maxVal;
    cv::Point minLoc = {0}, maxLoc = {0};
    cv::Mat temp = frame(frameRoi).clone();
    //qDebug() << temp.cols << " " << temp.rows;
    cv::matchTemplate(temp,templ,res,cv::TM_CCOEFF_NORMED);
    //qDebug() << templ.cols << " " << templ.rows;
    //qDebug() << res.cols << " " << res.rows;
    cv::minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);
    //qDebug() << maxLoc.x << " " << maxLoc.y;

    int centor_y_inGflag = maxLoc.x+temp.cols/2;
    int centor_x_inGflag = maxLoc.y+temp.rows/2;

    int l_y = centor_y_inGflag - frame.cols / 2;
    int t_x = centor_x_inGflag - frame.rows / 2;
    int r_y = centor_y_inGflag + frame.cols / 2;
    int b_x = centor_x_inGflag + frame.rows / 2;

    int left = l_y < 0 ? -l_y : 0;
    int right = Gframe.cols >= r_y ? 0 : r_y - Gframe.cols;
    int top = t_x < 0 ? -t_x : 0;
    int bottom = Gframe.rows >= b_x ? 0 : b_x - Gframe.rows;

    cv::Mat newGframe(cv::Size(Gframe.cols+left+right,Gframe.rows+top+bottom),CV_8UC1);
    cv::copyMakeBorder(Gframe,newGframe,top,bottom,left,right,cv::BORDER_CONSTANT,255);

    l_y += left;
    t_x += top;

    frame.copyTo(newGframe(cv::Rect(l_y,t_x,frame.cols,frame.rows)));

    Gframe = newGframe.clone();

    templ = Gframe;*/

    //qDebug() << left << " " << right << " " << top << " " << bottom;

    //qDebug() << "-----------------------------";

    /*std::vector<cv::Mat>images;

    cv::cvtColor(frame,templ,cv::COLOR_GRAY2BGR);
    cv::cvtColor(Gframe,res,cv::COLOR_GRAY2BGR);

    images.push_back(templ);
    images.push_back(res);

    cv::Mat newGframe;
    cv::Stitcher::Status status = stitcher->stitch(images, newGframe);

    if (status == cv::Stitcher::OK)
    {
        Gframe = newGframe.clone();
    }*/
    std::vector<cv::KeyPoint>keypoint_Gframe, keypoint_frame;
    cv::Mat descriptor_Gframe, descriptor_frame;
    detector->detectAndCompute(Gframe, cv::Mat(), keypoint_Gframe, descriptor_Gframe);
    detector->detectAndCompute(frame, cv::Mat(), keypoint_frame, descriptor_frame);

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

    //int dy = (int)H.at<double>(2);
    //int dx = (int)H.at<double>(5);

    int dy = (int)dpix.at<double>(0);
    int dx = (int)dpix.at<double>(1);

    int l_y = dy;
    int t_x = dx;
    int r_y = dy + frame.cols;
    int b_x = dx + frame.rows;

    int left = l_y < 0 ? -l_y : 0;
    int right = Gframe.cols >= r_y ? 0 : r_y - Gframe.cols;
    int top = t_x < 0 ? -t_x : 0;
    int bottom = Gframe.rows >= b_x ? 0 : b_x - Gframe.rows;

    /*Mat WarpImg;
        warpPerspective(frame, WarpImg, H, Size(frame.cols + (dy > 0 ? dy : -dy), frame.rows + (dx > 0 ? dx : -dx)));*/

    cv::Mat res = cv::Mat(cv::Size(Gframe.cols + left + right, Gframe.rows + top + bottom), CV_8UC1);
    cv::copyMakeBorder(Gframe, res, top, bottom, left, right, cv::BORDER_CONSTANT, 255);

    l_y += left;
    t_x += top;

    frame.copyTo(res(cv::Rect(l_y, t_x, frame.cols, frame.rows)));

    Gframe = res.clone();
}

void QVision::QVision_ProcessOnce()
{
    std::vector<cv::KeyPoint> keypoint_frame;
    cv::Mat descriptor_frame;
    detector->detectAndCompute(Gframe, cv::Mat(), Gkeypoints, Gdescriptors);
    detector->detectAndCompute(frame, cv::Mat(), keypoint_frame, descriptor_frame);

    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch>matches;
    matcher.match(Gdescriptors, descriptor_frame, matches);

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
            goodkeypoint_Gframe.push_back(Gkeypoints[matches[i].queryIdx].pt);
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
}

void QVision::QVision_Process()
{
    while(isStart)
    {
        while(!newFrame);
        newFrame = false;
        QVision_ProcessOnce();
    }
}

void QVision::QVision_ProcessInit()
{
    detector->detectAndCompute(Gframe, cv::Mat(), Gkeypoints, Gdescriptors);
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
