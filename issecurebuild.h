#ifndef ISSECUREBUILD_H
#define ISSECUREBUILD_H


#include <QObject>
#include <QByteArray>
#include <QtCrypto>
#include <QDateTime>

class isSecureBuild
{
public:

    QCA::Initializer init;
    isSecureBuild();
    QByteArray QByteArrayToAES128(QByteArray);
    QByteArray AES128ToQByteArray(QByteArray);
    void carregaArquivo();
    void escreveArquivo(QByteArray customerName, QByteArray MacID, QDateTime data);

private:
    QByteArray customerName;
    QByteArray macID;
    QByteArray dateTimes;


    bool isSecureValue = false;
};

#endif // ISSECUREBUILD_H
