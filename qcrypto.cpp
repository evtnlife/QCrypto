#include "qcrypto.h"
#include "ui_qcrypto.h"
#include <QtCrypto>
#include <QDebug>
#include <QByteArray>
#include "issecurebuild.h"
#include <QNetworkInterface>

QCrypto::QCrypto(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QCrypto)
{
    ui->setupUi(this);

    ui->editDateTime->setDateTime(QDateTime::currentDateTime());
        connect(ui->haveFun,SIGNAL(clicked(bool)),this,SLOT(cryptMethod2()));
        connect(ui->encryptConfig,SIGNAL(clicked(bool)),this,SLOT(cryptMethod()));
}

QCrypto::~QCrypto()
{
    delete ui;
}

void QCrypto::cryptMethod2()
{
    isSecureBuild isSecure;
    if(ui->rbEnc->isChecked()){
        QByteArray encReturn = isSecure.QByteArrayToAES128(ui->lineToCrypt->text().toLocal8Bit());
        ui->lineEncrypted->setText(QCA::arrayToHex(encReturn));
    }
    if(ui->rbDec->isChecked()){
        QByteArray decReturn = isSecure.AES128ToQByteArray(ui->lineToCrypt->text().toLocal8Bit());
        ui->lineDecrypted->setText(decReturn);
        qDebug() << "a" << decReturn;
    }
}


void QCrypto::cryptMethod()
{
    isSecureBuild isSecure;
    QByteArray customerName = ui->editCustomer->text().toLatin1();
    QByteArray macID;
    QDateTime dateTime = ui->editDateTime->dateTime();

    QNetworkInterface netInterface;
    foreach (netInterface, QNetworkInterface::allInterfaces())
    {
        if(!(netInterface.flags() & QNetworkInterface::IsLoopBack)
                && netInterface.humanReadableName().toLower().contains("ethernet")
                or netInterface.humanReadableName().toLower().contains("conexão local"))
        {
            macID = netInterface.hardwareAddress().toLatin1();
            ui->editMacID->setText(macID);
        }
    }
    isSecure.escreveArquivo(customerName,macID,dateTime);
}
