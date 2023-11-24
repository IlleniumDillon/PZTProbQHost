#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"
#include "QWheelEvent"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    planner = new QPlanner;
    vision = new QVision;
    Prob = new QProbDevice;
    PZT = new QPztDevice;
    //interferometer = new QInterferometer;
    scopePzt = new QOscilloscope("pzt");
    scopeInterferometer = new QOscilloscope("Interferometer");
    scopeVision = new QOscilloscope("vision");


    Prob->Device_SetComPort("COM6");
    PZT->Device_SetComPort("COM7");

    vision->QVision_Init();
    vision->QVision_Start();

    connect(vision,SIGNAL(QVision_NewFrameReady(cv::Mat)),this,SLOT(showFrame(cv::Mat)));

    planner->moveToThread(&QPlannerThread);
    vision->moveToThread(&QVisionThread);
    Prob->moveToThread(&QProbDeviceThread);
    PZT->moveToThread(&QPztDeviceThread);
    //scope->moveToThread(&QOscilloscopeThread);

    QVisionThread.start();
    QProbDeviceThread.start();
    QPztDeviceThread.start();
    QPlannerThread.start();
    //QOscilloscopeThread.start();

    this->grabKeyboard();
    this->setMouseTracking(true);

    /*scopePzt->show();
    scopePzt->QOsc_AddChannel("ADC0",&PZT->debugData.feedback[0],QOscilloscope::DATATYPE_FLOAT32);
    scopePzt->QOsc_AddChannel("ADC1",&PZT->debugData.feedback[1],QOscilloscope::DATATYPE_FLOAT32);
    scopePzt->QOsc_AddChannel("target0",&PZT->debugData.target[0],QOscilloscope::DATATYPE_FLOAT32);
    scopePzt->QOsc_AddChannel("target1",&PZT->debugData.target[1],QOscilloscope::DATATYPE_FLOAT32);
    scopePzt->QOsc_AddChannel("output0",&PZT->debugData.output[0],QOscilloscope::DATATYPE_FLOAT32);
    scopePzt->QOsc_AddChannel("output1",&PZT->debugData.output[1],QOscilloscope::DATATYPE_FLOAT32);*/



    /*scopeVision->show();
    scopeVision->QOsc_AddChannel("X",&vision->px,QOscilloscope::DATATYPE_FLOAT32);
    scopeVision->QOsc_AddChannel("Y",&vision->py,QOscilloscope::DATATYPE_FLOAT32);


    scopeInterferometer->show();
    scopeInterferometer->QOsc_AddChannel("ch1",&interferometer->ch1,QOscilloscope::DATATYPE_FLOAT32);
    scopeInterferometer->QOsc_AddChannel("ch2",&interferometer->ch2,QOscilloscope::DATATYPE_FLOAT32);*/

    //scopePzt->QOsc_Start();
    /*scopeVision->QOsc_Start();
    scopeInterferometer->QOsc_Start();*/

    timerId = startTimer(1000);
}

MainWindow::~MainWindow()
{
    //threadFlag = false;
    //thread.waitForFinished();

    QVisionThread.quit();
    QProbDeviceThread.quit();
    QPztDeviceThread.quit();
    QPlannerThread.quit();
    //QOscilloscopeThread.quit();

    QVisionThread.wait();
    QProbDeviceThread.wait();
    QPztDeviceThread.wait();
    QPlannerThread.wait();
    //QOscilloscopeThread.wait();

    delete planner;
    delete Prob;
    delete PZT;
    delete scopePzt;
    delete scopeInterferometer;
    delete scopeVision;
    delete vision;

    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == timerId)
    {
        if(state == STATE_SCAN)
        {
            if(watcher.isFinished())
            {
                ui->pushButtonScan->setText("scan");
                state = STATE_IDLE;
                vision->QVision_GframeFix();
                cv::Mat show;
                cv::cvtColor(vision->Gframe,show,cv::COLOR_BGR2GRAY);
                QImage img(show.data,show.cols,show.rows,QImage::Format_Grayscale8);
                ui->labelGImg->setPixmap(QPixmap::fromImage(img).scaled(ui->labelGImg->size(),Qt::KeepAspectRatio));
                //cv::imshow("temp",vision->Gframe);
            }
        }
        else if(state == STATE_INIT)
        {
            if(watcher.isFinished())
            {
                ui->pushButtonInit->setText("init");
                state = STATE_IDLE;
                //cv::imshow("temp",vision->Gframe);
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W)
    {
        int data[] = {0,100,0};
        Prob->Device_SendTarget<int>(data,3);
        qDebug()<<"W";
    }
    else if(e->key() == Qt::Key_S)
    {
        int data[] = {0,-100,0};
        Prob->Device_SendTarget<int>(data,3);
        qDebug()<<"S";
    }
    else if(e->key() == Qt::Key_A)
    {
        int data[] = {-100,0,0};
        Prob->Device_SendTarget<int>(data,3);
        qDebug()<<"A";
    }
    else if(e->key() == Qt::Key_D)
    {
        int data[] = {100,0,0};
        Prob->Device_SendTarget<int>(data,3);
        qDebug()<<"D";
    }
    else if(e->key() == Qt::Key_Up)
    {
        PZT->target[1]+=0.1;
        float data[] = {PZT->target[0],PZT->target[1],0};
        PZT->Device_SendTarget<float>(data,3);
        qDebug()<<"up";
    }
    else if(e->key() == Qt::Key_Down)
    {
        PZT->target[1]-=0.1;
        float data[] = {PZT->target[0],PZT->target[1],0};
        PZT->Device_SendTarget<float>(data,3);
        qDebug()<<"down";
    }
    else if(e->key() == Qt::Key_Left)
    {
        PZT->target[0]-=0.1;
        float data[] = {PZT->target[0],PZT->target[1],0};
        PZT->Device_SendTarget<float>(data,3);
        qDebug()<<"left";
    }
    else if(e->key() == Qt::Key_Right)
    {
        PZT->target[0]+=0.1;
        float data[] = {PZT->target[0],PZT->target[1],0};
        PZT->Device_SendTarget<float>(data,3);
        qDebug()<<"right";
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    qDebug()<<event->angleDelta().x()<<" "<<event->angleDelta().y();
    int data[] = {0,0,event->angleDelta().y()/12};
    Prob->Device_SendTarget<int>(data,3);
}

void MainWindow::runInThread()
{
    if(state == STATE_SCAN)
    {
        for(int x = 0; x < 10; x++)
        {
            if(x%2 == 0)
            {
                for(int y = 0; y < 10; y++)
                {
                    //QTime _Timer = QTime::currentTime().addMSecs(1000);

                    float data[] = {(float)x*1.0f,(float)y*1.0f,0};
                    PZT->Device_SendTarget<float>(data,3);

                    //QThread::msleep(1500);
                    QTime _Timer = QTime::currentTime().addMSecs(400);
                    while( QTime::currentTime() < _Timer ) ;//QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                    vision->QVision_GframeProcessOnce();
                    cv::Mat show;
                    cv::cvtColor(vision->Gframe,show,cv::COLOR_BGR2GRAY);
                    //QImage img = QImage(show.cols,show.rows,QImage::Format_Grayscale8);
                    QImage img(show.data,show.cols,show.rows,QImage::Format_Grayscale8);
                    /*for(int i = 0; i < show.cols; i++)
                    {
                        for(int j = 0; j < show.rows; j++)
                        {
                            uchar data = show.at<uchar>(j,i);
                            img.setPixel(i,j,qRgb(data,data,data));
                        }
                    }*/
                    ui->labelGImg->setPixmap(QPixmap::fromImage(img).scaled(ui->labelGImg->size(),Qt::KeepAspectRatio));
                }
            }
            else
            {
                for(int y = 9; y >= 0; y--)
                {
                    //QTime _Timer = QTime::currentTime().addMSecs(1000);

                    float data[] = {(float)x*1.0f,(float)y*1.0f,0};
                    PZT->Device_SendTarget<float>(data,3);

                    //QThread::msleep(1500);
                    QTime _Timer = QTime::currentTime().addMSecs(400);
                    while( QTime::currentTime() < _Timer ) ;//QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                    vision->QVision_GframeProcessOnce();
                    cv::Mat show;
                    cv::cvtColor(vision->Gframe,show,cv::COLOR_BGR2GRAY);
                    //QImage img = QImage(show.cols,show.rows,QImage::Format_Grayscale8);
                    QImage img(show.data,show.cols,show.rows,QImage::Format_Grayscale8);
                    /*for(int i = 0; i < vision->Gframe.cols; i++)
                    {
                        for(int j = 0; j < vision->Gframe.rows; j++)
                        {
                            //qDebug()<<i<<" "<<j;
                            uchar data = vision->Gframe.at<uchar>(j,i);
                            img.setPixel(i,j,qRgb(data,data,data));
                        }
                    }*/
                    ui->labelGImg->setPixmap(QPixmap::fromImage(img).scaled(ui->labelGImg->size(),Qt::KeepAspectRatio));
                }
            }
        }
        for(int x = 9; x >= 0; x--)
        {
            QTime _Timer = QTime::currentTime().addMSecs(200);

            float data[] = {(float)x*1.0f,0,0};
            PZT->Device_SendTarget<float>(data,3);

            //QThread::msleep(1000);
            while( QTime::currentTime() < _Timer ) ;//QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
//        for(int i = 0; i < vision->images.size(); i ++)
//        {
//            QString path = QString("D:\\pztProb\\hostCode\\QHost\\img_x10_%1.jpg").arg(i);
//            cv::imwrite(path.toStdString(),vision->images.at(i));
//        }
    }
    else if(state == STATE_INIT)
    {
        for(int i = 0; i <= 5; i++)
        {
            QTime _Timer = QTime::currentTime().addMSecs(5);

            float data[] = {(float)i*1.0f,(float)i*1.0f,0};
            PZT->Device_SendTarget<float>(data,3);

            while( QTime::currentTime() < _Timer ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            _Timer = QTime::currentTime().addMSecs(500);
            while( QTime::currentTime() < _Timer ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            vision->QVision_ProcessInit();
        }
    }
}

void MainWindow::showFrame(cv::Mat frame)
{
    QImage img = QImage(frame.data,frame.cols,frame.rows,QImage::Format_Grayscale8);

    ui->labelImg->setPixmap(QPixmap::fromImage(img).scaled(ui->labelImg->size(),Qt::KeepAspectRatio));

    //QFuture<void> thread = QtConcurrent::run(&MainWindow::runInThread,this,frame);
}

void MainWindow::on_pushButtonScan_clicked()
{
    if(state != STATE_IDLE) return;
    state = STATE_SCAN;
    vision->QVision_GframeProcessInit();
    QFuture<void> thread = QtConcurrent::run(&MainWindow::runInThread,this);
    watcher.setFuture(thread);
    ui->pushButtonScan->setText("scanning");
}


void MainWindow::on_pushButtonInit_clicked()
{
    if(state != STATE_IDLE) return;
    state = STATE_INIT;
    QFuture<void> thread = QtConcurrent::run(&MainWindow::runInThread,this);
    watcher.setFuture(thread);
    ui->pushButtonInit->setText("init in progress");
}

