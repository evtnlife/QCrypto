#ifndef QCRYPTO_H
#define QCRYPTO_H

#include <QMainWindow>

namespace Ui {
class QCrypto;
}

class QCrypto : public QMainWindow
{
    Q_OBJECT

public:
    explicit QCrypto(QWidget *parent = 0);
    ~QCrypto();

protected slots:
    void cryptMethod();
    void cryptMethod2();

private:
    Ui::QCrypto *ui;
};

#endif // QCRYPTO_H
