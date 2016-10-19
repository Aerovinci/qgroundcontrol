#include "QGCHilMissionStatus.h"
#include "ui_QGCHilMissionStatus.h"
#include "QGCAutoHilControl.h"
#include "QGCHilLink.h"
#include "UAS.h"

QGCHilMissionStatus::QGCHilMissionStatus(Vehicle *vehicle, QGCAutoHilControl *parent) :
    _vehicle(vehicle),
    QWidget(parent),
    ui(new Ui::QGCHilMissionStatus)
{
    ui->setupUi(this);

    this->Register();
}

void QGCHilMissionStatus::Register()
{
    connect(_vehicle, &Vehicle::homePositionAvailableChanged, this, &QGCHilMissionStatus::receiveQGCHomePositionAvailable);
    connect(_vehicle, &Vehicle::homePositionChanged, this, &QGCHilMissionStatus::homePositionChanged);
    connect(_vehicle, &Vehicle::armedChanged, this, &QGCHilMissionStatus::armedChanged);
    connect(_vehicle, &Vehicle::flightModeChanged, this, &QGCHilMissionStatus::flightModeChanged);
}

void QGCHilMissionStatus::UnRegister()
{
    disconnect(_vehicle, &Vehicle::homePositionAvailableChanged, this, &QGCHilMissionStatus::receiveQGCHomePositionAvailable);
    disconnect(_vehicle, &Vehicle::homePositionChanged, this, &QGCHilMissionStatus::homePositionChanged);
    disconnect(_vehicle, &Vehicle::armedChanged, this, &QGCHilMissionStatus::armedChanged);
    disconnect(_vehicle, &Vehicle::flightModeChanged, this, &QGCHilMissionStatus::flightModeChanged);
}
QGCHilMissionStatus::~QGCHilMissionStatus()
{
    delete ui;
}

void QGCHilMissionStatus::UpdateLinkState()
{
    if (_vehicle->uas()->getHILSimulation()->isConnected())
    {
        ui->rbHILState->setChecked(true);
        ui->rbHILState->setText("ON");
    }
    else
    {
        ui->rbHILState->setChecked(true);
        ui->rbHILState->setText("OFF");
    }
}

/*************************** SLOTS for triggered SIGNALS ***************************/

void QGCHilMissionStatus::receiveQGCHomePositionAvailable(bool homeAvailable)
{
    qDebug() <<"YES, the home position is available: " << homeAvailable;
}

void QGCHilMissionStatus::homePositionChanged(const QGeoCoordinate& homePosition)
{
    qDebug() <<"homePositionChanged: " << homePosition;
}

void QGCHilMissionStatus::armedChanged(bool armed)
{
    qDebug() <<"armedChanged: " << armed;
    ui->lblArmed->setText(armed? "Armed" : "Disarmed");
    UpdateLinkState();
}

void QGCHilMissionStatus::flightModeChanged(const QString& flightMode)
{
    qDebug() <<"flightModeChanged: " << flightMode;
    ui->lblMissionMode->setText(flightMode);
    UpdateLinkState();
}
