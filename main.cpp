#include "qcrypto.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList listLibrary;
    listLibrary.append("plugins/crypto/libqca-ossl.dll");
    listLibrary.append("plugins/crypto/libqca-gnupg.dll");
    listLibrary.append("plugins/crypto/libqca-logger.dll");
    listLibrary.append("plugins/crypto/libqca-softstore.dll");
    qDebug() << listLibrary[1] << listLibrary[2];
    listLibrary.append("plugins/crypto/libeay32.dll");
    listLibrary.append("plugins/crypto/libssl32.dll");
    listLibrary.append("plugins/crypto/ssleay32.dll");
    listLibrary.append("plugins/crypto/");
    QApplication::libraryPaths();

    QStringList library = a.libraryPaths();
    for(int i = 0; i<library.size();i++)
        qDebug() << library[i] << endl;
    QCrypto w;
    w.show();


    return a.exec();
}
