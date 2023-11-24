#ifndef QOSCILLOSCOPE_H
#define QOSCILLOSCOPE_H

#include <QWidget>
#include "qcustomplot.h"

#include <QThread>
#include <QtConcurrent>
#include <QFuture>

class QOscilloscope : public QWidget
{
    Q_OBJECT
public:
    enum DataType{DATATYPE_INT32, DATATYPE_FLOAT32};
    struct OscData{void* pdata; DataType type;};

    explicit QOscilloscope(QString name,QWidget *parent = nullptr);
    ~QOscilloscope();

    void QOsc_Start(){runFlag = true;}

    void QOsc_Stop(){runFlag = false;}

    void QOsc_AddChannel(QString name,void* p,DataType type);

    void timerEvent(QTimerEvent* e);

    void runInThread(double time);

signals:

private:
    QCustomPlot *plot;
    QCPItemTracer *tracer;
    QCPItemText *tracerLabel;

    uint8_t channelnum = 0;
    bool runFlag = false;
    int timerId;
    OscData data[16];
    QPen colors[16] = {QPen(Qt::blue),QPen(Qt::green),QPen(Qt::red),QPen(Qt::cyan),QPen(Qt::magenta),QPen(Qt::yellow),QPen(Qt::black),QPen(Qt::white),
                       QPen(Qt::darkRed),QPen(Qt::darkGreen),QPen(Qt::darkBlue),QPen(Qt::darkCyan),QPen(Qt::darkMagenta),QPen(Qt::darkYellow),QPen(Qt::darkGray),QPen(Qt::lightGray)};

};

#endif // QOSCILLOSCOPE_H
