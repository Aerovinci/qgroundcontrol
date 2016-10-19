/****************************************************************************
 *
 * (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 * Author: shyam@aerovinci.com
 * Date: 15-10-2016
 *
 ****************************************************************************/


#include "AutoHILDockWidget.h"
#include "QGCAutoHilControl.h"

AutoHILDockWidget::AutoHILDockWidget(const QString& title, QAction* action, QWidget* widget):
    MultiVehicleDockWidget(title, action, widget)
{
    init();

    loadSettings();
}

AutoHILDockWidget::~AutoHILDockWidget()
{

}

QWidget* AutoHILDockWidget::_newVehicleWidget(Vehicle *vehicle, QWidget *parent)
{
    return new QGCAutoHilControl(vehicle, parent);
}
