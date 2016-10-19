#ifndef QGCAUTOHILCONTROL_H
#define QGCAUTOHILCONTROL_H

#include <QWidget>

#include "Vehicle.h"
#include "QGCHilLink.h"
#include <QUdpSocket>

namespace Ui {
class QGCAutoHilControl;
}

class QGCAutoHilControl : public QWidget
{
    Q_OBJECT

public:
    explicit QGCAutoHilControl(Vehicle *vehicle, QWidget *parent = 0);
    ~QGCAutoHilControl();
     void Init();

public slots:
    void toggleSimulation(bool connect);
    void receiveStatusMessage(const QString& message);  // Receive status updates on xPlane
    void receiveXplane_sensorHilGpsChanged(quint64 time_us, double lat, double lon, double alt, int fix_type, float eph, float epv, float vel, float vn, float ve, float vd, float cog, int satellites);
    void receiveXplane_hilStateChanged(quint64 time_us, float roll, float pitch, float yaw, float rollspeed,
                                          float pitchspeed, float yawspeed, double lat, double lon, double alt,
                                          float vx, float vy, float vz, float ind_airspeed, float true_airspeed, float xacc, float yacc, float zacc);

private slots:

    void on_btnSettings_clicked();

    void on_btnArm_clicked();

    void on_btnRebootPixhawk_clicked();

protected:
    QGCHilLink* link;
    QUdpSocket* socket;

private:

    void StartHIL();
    void StopHIL();
    void CreateMenu();

    Vehicle* _vehicle;

    Ui::QGCAutoHilControl *ui;
    QString remoteIP = "10.0.0.10:49000";
};

#endif // QGCAUTOHILCONTROL_H
