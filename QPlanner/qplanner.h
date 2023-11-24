#ifndef QPLANNER_H
#define QPLANNER_H

#include <QObject>
#include <qastar.h>

class QPlanner : public QObject
{
    Q_OBJECT
public:
    explicit QPlanner(QObject *parent = nullptr);

signals:

};

#endif // QPLANNER_H
