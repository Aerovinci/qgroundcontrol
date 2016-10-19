#ifndef MISSIONSETTINGS_H
#define MISSIONSETTINGS_H

#include <QWidget>

namespace Ui {
class MissionSettings;
}

class MissionSettings : public QWidget
{
    Q_OBJECT

public:
    explicit MissionSettings(QWidget *parent = 0);
    ~MissionSettings();

private slots:
    void on_btnLoadDir_clicked();

    void on_btnSaveSettings_clicked();

private:
    Ui::MissionSettings *ui;
};

#endif // MISSIONSETTINGS_H
