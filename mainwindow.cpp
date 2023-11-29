#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"
#include "QWheelEvent"
#include "QDateTime"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int num_devices = cv::cuda::getCudaEnabledDeviceCount();
    if (num_devices <= 0)
    {
        std::cerr << "There is no device." << std::endl;
    }
    int enable_device_id = -1;
    for (int i = 0; i < num_devices; i++)
    {
        cv::cuda::DeviceInfo dev_info(i);
        if (dev_info.isCompatible())
        {
            enable_device_id = i;
        }
    }
    if (enable_device_id < 0)
    {
        std::cerr << "GPU module isn't built for GPU" << std::endl;
    }
    cv::cuda::setDevice(enable_device_id);

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
    connect(this,SIGNAL(GframeReady()),this,SLOT(showGframe()));
    connect(vision,SIGNAL(QVision_ProcessDone()),this,SLOT(showVisionData()));

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
        if(state == STATE_SCAN_FINISH)
        {
            if(watcher.isFinished())
            {
                ui->pushButtonScan->setText("scan");
                state = STATE_IDLE;
                vision->QVision_GframeFix();
                //showGframe();
                //QFuture<void> thread = QtConcurrent::run(&MainWindow::showGframe,this);
                //emit GframeReady();
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
                    float data[] = {(float)x*1.0f,(float)y*1.0f,0};
                    PZT->Device_SendTarget<float>(data,3);
                    QTime _Timer = QTime::currentTime().addMSecs(500);
                    while( QTime::currentTime() < _Timer ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                    vision->QVision_GframeProcessOnce();
                    //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                    emit GframeReady();//showGframe();
                }
            }
            else
            {
                for(int y = 9; y >= 0; y--)
                {
                    float data[] = {(float)x*1.0f,(float)y*1.0f,0};
                    PZT->Device_SendTarget<float>(data,3);
                    QTime _Timer = QTime::currentTime().addMSecs(500);
                    while( QTime::currentTime() < _Timer ) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                    vision->QVision_GframeProcessOnce();
                    //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                    emit GframeReady();//showGframe();
                }
            }
        }
        for(int x = 9; x >= 0; x--)
        {
            QTime _Timer = QTime::currentTime().addMSecs(200);
            float data[] = {(float)x*1.0f,0,0};
            PZT->Device_SendTarget<float>(data,3);
            while( QTime::currentTime() < _Timer ) ;//QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        state = STATE_SCAN_FINISH;
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

void MainWindow::showGframe()
{
    Mat show = vision->Gframe;
    QImage img(show.data,show.cols,show.rows,QImage::Format_Grayscale8);
    ui->labelGImg->setPixmap(QPixmap::fromImage(img).scaled(ui->labelGImg->size(),Qt::KeepAspectRatio));
}

void MainWindow::showVisionData()
{
    static qint64 nTime = 0;
    QDateTime time= QDateTime::currentDateTime();
    nTime -= time.currentMSecsSinceEpoch();
    ui->label_x->setText(QString("x:%1").arg(vision->px));
    ui->label_y->setText(QString("y:%1").arg(vision->py));
    ui->label_fps->setText(QString("time:%1ms").arg(nTime));
    nTime = time.currentMSecsSinceEpoch();
}

void MainWindow::showFrame(cv::Mat frame)
{
    QImage img = QImage(frame.data,frame.cols,frame.rows,QImage::Format_Grayscale8);
    ui->labelImg->setPixmap(QPixmap::fromImage(img).scaled(ui->labelImg->size(),Qt::KeepAspectRatio));
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

