#include "QGCAutoHilControl.h"
#include "ui_QGCAutoHilControl.h"
#include <QMenuBar>
#include "MissionSettings.h"
#include "UAS.h"
#include "QGCHilMissionStatus.h"
#include <QMessageBox>

QGCAutoHilControl::QGCAutoHilControl(Vehicle *vehicle, QWidget *parent) :
    QWidget(parent),
    _vehicle(vehicle),
    ui(new Ui::QGCAutoHilControl)
{
    ui->setupUi(this);

    // Ensure the sim exists and is disabled
    _vehicle->uas()->enableHilXPlane(false);

    this->link = _vehicle->uas()->getHILSimulation();

    Init();

}

/// @brief Initializes the slots for the connection to the X-Plane (v10)
void QGCAutoHilControl::Init()
{
    // Create a config/settings menu
    CreateMenu();

    connect(ui->btnConnect, &QPushButton::clicked, this, &QGCAutoHilControl::toggleSimulation);

    // Select correct version of XPlane
    QGCXPlaneLink* xplane = dynamic_cast<QGCXPlaneLink*>(link);
    if (xplane)
    {
        xplane->setVersion(10);
        connect(xplane, &QGCXPlaneLink::statusMessage, ui->statusLabel, &QLabel::setText);
    }

    //clean up
    QLayoutItem *child;
    while ((child = ui->hitlMissionStatusLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    // ** Ensure the sim exists and is disabled
    _vehicle->uas()->enableHilXPlane(false);

    // Patch the Mission status widget on to the parent widget
    QGCHilMissionStatus* hxpconf = new QGCHilMissionStatus(_vehicle, this);
    hxpconf->show();
    ui->hitlMissionStatusLayout->addWidget(hxpconf);

    /*QVBoxLayout *boxLayout = new QVBoxLayout(this); // Main layout of widget*/

}

/// @brief Create menu items for settings and command dispatch tester
void QGCAutoHilControl::CreateMenu()
{
    new QVBoxLayout(this); // Main layout of widget
    QMenuBar* menuBar = new QMenuBar();

    QMenu *fileMenu = new QMenu("File");
    fileMenu->addAction("HIL Settings");
    fileMenu->addAction("Exit");
    menuBar->addMenu(fileMenu);

    QMenu *testingMenu = new QMenu("Testing");
    testingMenu->addAction("Send Commands");
    menuBar->addMenu(testingMenu);

    this->layout()->setMenuBar(menuBar);

}

QGCAutoHilControl::~QGCAutoHilControl()
{
    delete ui;
}

/*************************** SLOTS for triggered SIGNALS ***************************/

/// @brief Updates the status message Initializes the slots for the connection to the X-Plane (v10)
void QGCAutoHilControl::receiveStatusMessage(const QString& message)
{
    ui->statusLabel->setText(message);
}

void QGCAutoHilControl::receiveXplane_sensorHilGpsChanged(quint64 time_us, double lat, double lon, double alt, int fix_type, float eph, float epv, float vel, float vn, float ve, float vd, float cog, int satellites)
{
    // qDebug() << "time_us: " << time_us <<", (lat, long, alt): (" << lat <<", " << lon << ", " << alt << ")";
}

void QGCAutoHilControl::receiveXplane_hilStateChanged(quint64 time_us, float roll, float pitch, float yaw, float rollspeed,
                                      float pitchspeed, float yawspeed, double lat, double lon, double alt,
                                      float vx, float vy, float vz, float ind_airspeed, float true_airspeed, float xacc, float yacc, float zacc)
{
    qDebug() << "time_us: " << time_us <<", (lat, long, alt): (" << lat <<", " << lon << ", " << alt << ")";
}

// @define A slot defined for starting or stopping the HIL simulation
void QGCAutoHilControl::toggleSimulation(bool connection)
{
    // Make sure the link is not null
    if (link)
    {

        Q_UNUSED(connection);

        // Start or stop the HIL based on the link status
        (!link->isConnected())? StartHIL() : StopHIL();
    }
}

// @define: Start the HIL simulation with the X-Plane
void QGCAutoHilControl::StartHIL()
{
    connect(link, &QGCHilLink::statusMessage, this, &QGCAutoHilControl::receiveStatusMessage);
    connect(link, &QGCHilLink::sensorHilGpsChanged, this, &QGCAutoHilControl::receiveXplane_sensorHilGpsChanged);
    connect(link, &QGCHilLink::hilStateChanged, this, &QGCAutoHilControl::receiveXplane_hilStateChanged);

    link->setRemoteHost(this->remoteIP); //(ui->hostComboBox->currentText());
    link->connectSimulation();
    ui->btnConnect->setText(tr("Stop HITL"));
}

// @define: Stop the HIL simulation with the X-Plane
void QGCAutoHilControl::StopHIL()
{
    link->disconnectSimulation();

    disconnect(link, &QGCHilLink::statusMessage, this, &QGCAutoHilControl::receiveStatusMessage);
    disconnect(link, &QGCHilLink::sensorHilGpsChanged, this, &QGCAutoHilControl::receiveXplane_sensorHilGpsChanged);
    disconnect(link, &QGCHilLink::hilStateChanged, this, &QGCAutoHilControl::receiveXplane_hilStateChanged);

    QThread::msleep(100);
    receiveStatusMessage("X-Plane has been disconnected!");
    ui->btnConnect->setText(tr("Start HITL"));
}

void QGCAutoHilControl::on_btnSettings_clicked()
{
    MissionSettings* missionSettingsDialog = new MissionSettings();
    missionSettingsDialog->showNormal();
}

void QGCAutoHilControl::on_btnArm_clicked()
{
    // If the vehicle is not yet armed, we arm it and start mission.
    // If the LINK is not connected it will anyways, reject the arming serquence.
    if (!_vehicle->armed())
    {
        _vehicle->setArmed(true);
        ui->btnArm->setText("DISARM");
        qDebug() << "Vehicle is armed";
        _vehicle->setFlightMode("Mission");

    }
    else
     {
        // Disarm the vehicle and land.
        _vehicle->setArmed(false);
        ui->btnArm->setText("ARM");
        _vehicle->setFlightMode("Land");
        qDebug() << "Vehicle is disarmed";
     }
}

// @define Reboot the Pixhawk by sending the mavlink command "MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN"
void QGCAutoHilControl::on_btnRebootPixhawk_clicked()
{
    // Disconnect and gracefully exit the HIL before rebooting
    StopHIL();
    // Test reboot the vehicle
    _vehicle->rebootVehicle();
}
