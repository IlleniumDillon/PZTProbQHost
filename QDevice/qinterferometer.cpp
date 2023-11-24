#include "qinterferometer.h"

QInterferometer::QInterferometer(QObject *parent)
    : QObject{parent}
{
    m_init = false;
    m_stop = true;
    if(WinExec("D:\\Laser Interferometer\\Project1\\Debug\\Project1.exe",SW_SHOWNORMAL) > 31) return;
    m_hMapping = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE, false, _T("LC_DATA"));
    if (INVALID_HANDLE_VALUE == m_hMapping)
    {
        std::cout << "initial open file mapping Handel failed," << std::endl;
        CloseHandle(m_hMapping);
        return;
    }
    m_pBase = (LC_Data*)MapViewOfFile(m_hMapping, FILE_MAP_WRITE, 0, 0, 0);
    m_init = true;
}

void QInterferometer::start()
{
    m_stop = false;
    QFuture<void> thread = QtConcurrent::run(&QInterferometer::runInThread,this);
    watcher.setFuture(thread);
}

void QInterferometer::stop()
{
    m_stop = true;
}

QInterferometer::~QInterferometer()
{
    m_stop = true;
    while(watcher.isRunning());
}

void QInterferometer::runInThread()
{
    while(m_stop)
    {
        QTime _Timer = QTime::currentTime().addMSecs(500);
        while(m_pBase->flag==0);
        ch1 = m_pBase->ch1;
        ch2 = m_pBase->ch2;
        str1 = m_pBase->str1;
        str2 = m_pBase->str2;
        m_pBase->flag=0;
        while( QTime::currentTime() < _Timer );
    }
}
