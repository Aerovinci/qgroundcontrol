#include "MissionSettings.h"
#include "ui_MissionSettings.h"
#include <QFileDialog>
#include <QDebug>

MissionSettings::MissionSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionSettings)
{
    ui->setupUi(this);
}

enum AutoHITLSettings
{
    MISSION_DIRECTORY,
    REPETITION,
    HOST_IP
};

void Write(QString filename)
{
    QFile mFile(filename);

    if (!mFile.open(QFile::WriteOnly |QFile::Text))
    {
        qDebug() << "Could not open file for writing..";
        return;
    }

    QTextStream out(&mFile);
    out << "Hello world";

    mFile.flush();
    mFile.close();

}

void WriteSettings(AutoHITLSettings param)
{
    /*switch(param)
    {
        case MISSION_DIRECTORY:
    }*/
}

void Read(QString filename)
{
    QFile mFile(filename);

    if (!mFile.open(QFile::ReadOnly |QFile::Text))
    {
        qDebug() << "Could not open file for reading..";
        return;
    }

    QTextStream in(&mFile);
    QString mText  = in.readAll();

    qDebug() << mText;

    mFile.flush();
    mFile.close();
}

MissionSettings::~MissionSettings()
{
    delete ui;
}

void MissionSettings::on_btnLoadDir_clicked()
{
    // Load the directory from here.
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    ui->txtMissionDir->setText(dir);
}
///
/// Saves the settings into resource file for global use
///
void MissionSettings::on_btnSaveSettings_clicked()
{
    QDir mDir;
    QString mPath(ui->txtMissionDir->text());
    if (!mDir.exists(mPath))
    {
        // Save the directory into settings (param 1)

    }
    else
    {
        qDebug() << "Directory does not exist";
    }
}
