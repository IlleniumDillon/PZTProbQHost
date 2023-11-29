#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimerEvent>

#include "qplanner.h"
#include "qvision.h"
#include "qpztdevice.h"
#include "qprobdevice.h"
#include "qoscilloscope.h"
#include "qinterferometer.h"

#include <QThread>
#include <QtConcurrent>
#include <QFuture>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef enum
    {
        STATE_IDLE,
        STATE_INIT,
        STATE_SCAN,
        STATE_SCAN_FINISH
    }State;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void timerEvent(QTimerEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void wheelEvent(QWheelEvent *event);
    void runInThread();

signals:
    void GframeReady();

public slots:
    void showFrame(cv::Mat frame);
    void showGframe();

private slots:
    void on_pushButtonScan_clicked();

    void on_pushButtonInit_clicked();

private:
    Ui::MainWindow *ui;

    QPlanner* planner;
    QVision* vision;
    QProbDevice* Prob;
    QPztDevice* PZT;
    QInterferometer* interferometer;

    QOscilloscope* scopePzt;
    QOscilloscope* scopeInterferometer;
    QOscilloscope* scopeVision;

    int timerId;
    int test = 0;

    QThread QPlannerThread;
    QThread QVisionThread;
    QThread QProbDeviceThread;
    QThread QPztDeviceThread;
    QThread QOscilloscopeThread;

    QFutureWatcher<void> watcher;

    State state = STATE_IDLE;

    /*bool threadFlag = true;
    QFuture<void> thread = QtConcurrent::run(&MainWindow::runInThread,this);*/

    //float scanTable[100*100][2] = {};

};
#endif // MAINWINDOW_H
