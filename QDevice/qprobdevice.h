#ifndef QPROBDEVICE_H
#define QPROBDEVICE_H

#include <qcustomdevice.h>

class QProbDevice : public QCustomDevice
{
public:
    explicit QProbDevice(QObject *parent = nullptr);
};

#endif // QPROBDEVICE_H
