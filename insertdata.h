#ifndef INSERTDATA_H
#define INSERTDATA_H

#include <QWidget>

namespace Ui {
class insertData;
}

class insertData : public QWidget
{
    Q_OBJECT

public:
    explicit insertData(QWidget *parent = nullptr);
    ~insertData();

private slots:
    void on_pushButton_clicked();

private:
    Ui::insertData *ui;
};

#endif // INSERTDATA_H
