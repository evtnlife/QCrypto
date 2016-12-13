#include "issecurebuild.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtCrypto>
#include <QList>
#include <QByteArray>
#include <QString>

isSecureBuild::isSecureBuild()
{
    isSecureValue = true;
}


void isSecureBuild::escreveArquivo(QByteArray customerName, QByteArray MacID, QDateTime data)
{
    QFile file("encrypt.d");
    if(!file.open(QIODevice::WriteOnly | QFile::Truncate | QFile::Text))
        isSecureValue = false;
    else
    {
        isSecureValue = true;
        QString DateTime = data.toString("dd/MM/yyyy hh:mm");

        QByteArray MacIDTMP;
        QString DateTimeTMP;

        //retira pontos
        for(int i = 0 ; i < MacID.count(); i++)
        {
            if(MacID[i] != ':')
                MacIDTMP.append(MacID[i]);
        }
        for(int i = 0 ; i < DateTime.count();i++)
        {
            if(DateTime[i] != '/' and DateTime[i] != ':' and !DateTime[i].isSpace())
                DateTimeTMP.append(DateTime[i]);
        }


        QTextStream stream(&file);
        stream << QCA::arrayToHex(QByteArrayToAES128(customerName)) << endl;
        stream << QCA::arrayToHex(QByteArrayToAES128(MacIDTMP)) << endl;
        stream << QCA::arrayToHex(QByteArrayToAES128(DateTimeTMP.toLatin1())) << endl;

        qDebug() << MacIDTMP << DateTimeTMP;
        file.close();
    }
}

void isSecureBuild::carregaArquivo()
{
    // carrega arquivo de texto
    QFile file("encrypt.d");
    if(!file.open(QIODevice::ReadOnly))
        isSecureValue = false;
    else
    {
        QTextStream stream(&file);
        customerName = stream.readLine().toLatin1();
        macID        = stream.readLine().toLatin1();
        dateTimes     = stream.readLine().toLatin1();

        file.close();
        isSecureValue = true;
    }
}

QByteArray isSecureBuild::QByteArrayToAES128(QByteArray value)
{
    if(isSecureValue == true)
    {
        QByteArray key = "16";
        QByteArray vector = "16";
        QCA::SymmetricKey symKey = QCA::SymmetricKey(key);
        QCA::InitializationVector initVector = QCA::InitializationVector(vector);

        QCA::SecureArray encrypted;
        QCA::Cipher cipher(QString("aes128"),
                           QCA::Cipher::Mode::CBC,
                           QCA::Cipher::Padding::DefaultPadding,
                           QCA::Encode,
                           symKey,
                           initVector,"md5");

        QList<QByteArray> lista;
            lista.append(value);

        foreach (QByteArray item, lista) {
            QCA::SecureArray secureData = cipher.update(item);
            QCA::SecureArray encryptedData = cipher.final();
            if(!cipher.ok()){
                qDebug() << "Encryptation Fail!";
                return "";
            }
            encrypted.append(encryptedData);

            qDebug() << "Encrypted string :" + QCA::arrayToHex(encryptedData.toByteArray());
            secureData.clear();
            encryptedData.clear();
            return encrypted.toByteArray();
        }
    }
    return QByteArray();
}

QByteArray isSecureBuild::AES128ToQByteArray(QByteArray value)
{
    if(isSecureValue == true)
    {
        QByteArray key = "16";
        QByteArray vector = "16";
        QCA::SymmetricKey symKey = QCA::SymmetricKey(key);
        QCA::InitializationVector initVector = QCA::InitializationVector(vector);

        QCA::SecureArray decrypted;

        QCA::Cipher cipher(QString("aes128"),
                          QCA::Cipher::Mode::CBC,
                          QCA::Cipher::DefaultPadding,
                          QCA::Decode,
                          symKey,
                          initVector);

       QCA::SecureArray valorFinal = cipher.process(QCA::hexToArray(value));
            if(!cipher.ok()){
                qDebug() << "Decrypt Fail!";
                return "";
            }
            decrypted.append(valorFinal);
            valorFinal.clear();
        return QString(decrypted.data()).toUtf8();
    }
    return QByteArray();
}
