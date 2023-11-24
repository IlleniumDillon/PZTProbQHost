#include "qoscilloscope.h"

#include <QThread>
#include <QtConcurrent>
#include <QFuture>

QOscilloscope::QOscilloscope(QString name,QWidget *parent)
    : QWidget{parent}
{
    plot = new QCustomPlot(this);
    plot->setGeometry(1,1,640,480);
    this->setFixedSize(642,482);
    this->setWindowTitle(name);
    timerId = startTimer(20);
    //QFuture<void> threadPlot = QtConcurrent::run(this,&QOscilloscope::runInThread,this->data);
}

QOscilloscope::~QOscilloscope()
{
    plot->close();
}

void QOscilloscope::QOsc_AddChannel(QString name, void *p, DataType type)
{
    plot->addGraph();//添加曲线
    plot->graph(channelnum)->setPen(colors[channelnum]);//设置曲线颜色
    plot->graph(channelnum)->setName(QString(name));//设置曲线名称
    plot->graph(channelnum)->data().data()->clear();//清空数据保留曲线

    plot->xAxis->setVisible(true);//显示下方X轴
    plot->xAxis->setTickLabels(true);//显示下方X轴 刻度
    plot->yAxis->setVisible(true);//显示左侧Y轴
    plot->yAxis->setTickLabels(true);//显示左侧Y轴 刻度
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//放大拖拽选中等
    plot->xAxis->setRange(0, 100);                         //当前X轴显示的范围
    plot->yAxis->setRange(0, 10);                          //当前Y轴显示的范围
    plot->graph(channelnum)->rescaleAxes();//坐标轴自适应
    /*图例*/
    plot->legend->setVisible(true);//设置图例可见
    // 设置图例行优先排列   默认图标会竖着排列，这样是横着
    plot->legend->setFillOrder(QCPLayoutGrid::foColumnsFirst);
    // 设置六个图例自动换行
    plot->legend->setWrap(6);
    // 设置图例位置，这里选择显示在QCPAxisRect下方，同理可设置显示在QCustomplotCh1中任意位置，还有比例
    plot->plotLayout()->addElement(1 , 0, plot->legend);
    // 设置显示比例，图例所在框的大小
    plot->plotLayout()->setRowStretchFactor(1, 0.001);
    // 设置边框隐藏，图例和曲线之间是有框的
    plot->legend->setBorderPen(Qt::NoPen);

    data[channelnum].pdata = p;
    data[channelnum].type = type;

    channelnum++;
}

void QOscilloscope::timerEvent(QTimerEvent *e)
{
    static double time = 0;
    if(e->timerId()==timerId)
    {
        if(runFlag == true)
        {
            for (int i = 0; i < channelnum; i++)
            {
                double d = 0;
                if(data[i].type == DATATYPE_INT32)
                {
                    d = *(int*)data[i].pdata;
                }
                else if(data[i].type == DATATYPE_FLOAT32)
                {
                    d = *(float*)data[i].pdata;
                }
                else
                {
                    return;
                }
                plot->graph(i)->addData(time,d);
                //plot->graph(i)->rescaleAxes(true);
            }
            plot->rescaleAxes();
            plot->replot();

            /*QFuture<void> thread = QtConcurrent::run(&QOscilloscope::runInThread,this,time);

            thread.waitForFinished();*/

            time+=0.02;
        }
    }
}

void QOscilloscope::runInThread(double time)
{
    for (int i = 0; i < channelnum; i++)
    {
        double d = 0;
        if(data[i].type == DATATYPE_INT32)
        {
            d = *(int*)data[i].pdata;
        }
        else if(data[i].type == DATATYPE_FLOAT32)
        {
            d = *(float*)data[i].pdata;
        }
        else
        {
            return;
        }
        //plot->graph(i)->addData(time,d);
        //plot->graph(i)->rescaleAxes(true);
    }
    //plot->rescaleAxes();
    //plot->replot();
}
