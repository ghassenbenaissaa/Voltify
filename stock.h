#ifndef STOCK_H
#define STOCK_H

#include <QDialog>

namespace Ui {
class stock;
}

class stock : public QDialog
{
    Q_OBJECT

public:
    explicit stock(QWidget *parent = nullptr);
    ~stock();

private:
    Ui::stock *ui;
};

#endif // STOCK_H
