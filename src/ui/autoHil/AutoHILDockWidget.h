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

#ifndef AUTOMATEDOCKWIDGET_H
#define AUTOMATEDOCKWIDGET_H

#include "MultiVehicleDockWidget.h"

class AutoHILDockWidget : public MultiVehicleDockWidget
{
    Q_OBJECT

public:

    explicit AutoHILDockWidget(const QString& title, QAction *action, QWidget *parent = 0);
    ~AutoHILDockWidget();

protected:

    // Override from MultivehicleDockWidget
    virtual QWidget* _newVehicleWidget(Vehicle *vehicle, QWidget *parent);
};

#endif // AUTOMATEDOCKWIDGET_H
