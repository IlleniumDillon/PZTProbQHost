#ifndef QINTERFEROMETER_H
#define QINTERFEROMETER_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <QtConcurrent>
#include <QFuture>

class QInterferometer : public QObject
{
    typedef struct _LC_Data
    {
        bool flag;
        int str1;
        int str2;
        double ch1;
        double ch2;
    }LC_Data;
    Q_OBJECT
public:
    explicit QInterferometer(QObject *parent = nullptr);
    void start();
    void stop();
    ~QInterferometer();

signals:

public:
    int str1 = 0;
    int str2 = 0;
    float ch1 = 0;
    float ch2 = 0;

private:
    void runInThread();
    HANDLE m_hMapping;			//内存映射句柄
    LC_Data* m_pBase = nullptr;	//内存映射字符串首地址
    volatile bool m_stop;
    volatile bool m_init;

    QFutureWatcher<void> watcher;
};

#endif // QINTERFEROMETER_H
