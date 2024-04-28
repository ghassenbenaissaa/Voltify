#ifndef SERVICE_H
#define SERVICE_H

#include <QDialog>

namespace Ui {
class service;
}

class service : public QDialog
{
    Q_OBJECT

public:
    explicit service(QWidget *parent = nullptr);
    ~service();

private:
    Ui::service *ui;
};

#endif // SERVICE_H
