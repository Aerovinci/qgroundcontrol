#ifndef QGCHILMISSIONSTATUS_H
#define QGCHILMISSIONSTATUS_H

#include <QWidget>
#include "QGCHilLink.h"
#include "Vehicle.h"
#include "QGCAutoHilControl.h"

namespace Ui {
class QGCHilMissionStatus;
}

class QGCHilMissionStatus : public QWidget
{
    Q_OBJECT

public:   
    explicit QGCHilMissionStatus(Vehicle *vehicle, QGCAutoHilControl *parent = 0);
    ~QGCHilMissionStatus();

private:
    void Register();
    void UnRegister();
    void receiveStatusMessage(const QString& message);
    void receiveQGCHomePositionAvailable(bool);
    void homePositionChanged(const QGeoCoordinate& homePosition);
    void armedChanged(bool armed);
    void flightModeChanged(const QString& flightMode);
    void UpdateLinkState();

private:
    Vehicle* _vehicle;
    Ui::QGCHilMissionStatus *ui;
};

#endif // QGCHILMISSIONSTATUS_H
