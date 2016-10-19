#include "QGCCmdDispatcher.h"
#include "ui_QGCCmdDispatcher.h"

QGCCmdDispatcher::QGCCmdDispatcher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QGCCmdDispatcher)
{
    ui->setupUi(this);
}

QGCCmdDispatcher::~QGCCmdDispatcher()
{
    delete ui;
}
