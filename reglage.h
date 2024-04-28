#ifndef REGLAGE_H
#define REGLAGE_H

#include <QDialog>

namespace Ui {
class reglage;
}

class reglage : public QDialog
{
    Q_OBJECT

public:
    explicit reglage(QWidget *parent = nullptr);
    ~reglage();

private:
    Ui::reglage *ui;
};

#endif // REGLAGE_H
