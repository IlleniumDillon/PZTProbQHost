#ifndef QPZTDEVICE_H
#define QPZTDEVICE_H

#include <QTimerEvent>
#include "qcustomdevice.h"

typedef struct pztdebugdata
{
    float target[2];
    float output[2];
    float feedback[2];
}PztDebugData;

class QPztDevice : public QCustomDevice
{
public:
    QPztDevice();

    void timerEvent(QTimerEvent *e);

public slots:
    void mesgManage(DevLinkRawData *data);

public:
    float ADCData[2] = {0,0};
    PztDebugData debugData = {{0}};
    float target[2] = {0};
};

#endif // QPZTDEVICE_H
