#ifndef QGCCMDDISPATCHER_H
#define QGCCMDDISPATCHER_H

#include <QDialog>

namespace Ui {
class QGCCmdDispatcher;
}

class QGCCmdDispatcher : public QDialog
{
    Q_OBJECT

public:
    explicit QGCCmdDispatcher(QWidget *parent = 0);
    ~QGCCmdDispatcher();

private:
    Ui::QGCCmdDispatcher *ui;
};

#endif // QGCCMDDISPATCHER_H
