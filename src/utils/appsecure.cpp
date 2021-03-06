#include "appsecure.h"
#include "../macros.h"

AppSecure::AppSecure(QObject *parent) : QObject(parent) {
}

void AppSecure::store(QString key, QString value)
{
    WritePasswordJob wpj(QLatin1String(APP_NAME));
    wpj.setAutoDelete(false);
    wpj.setKey(key);
    wpj.setTextData(value);
    QEventLoop loop;
    wpj.connect(&wpj, SIGNAL(finished(QKeychain::Job*)), &loop, SLOT(quit()));
    wpj.start();
    loop.exec();
    if (wpj.error()) {
        LOGW(QString("Storing key failed: %1").arg(wpj.errorString()));
    }
}

QString AppSecure::restore(QString key)
{
    ReadPasswordJob rpj(QLatin1String(APP_NAME));
    rpj.setAutoDelete(false);
    rpj.setKey(key);
    QEventLoop loop;
    rpj.connect(&rpj, SIGNAL(finished(QKeychain::Job*)), &loop, SLOT(quit()));
    rpj.start();
    loop.exec();
    return rpj.textData();

}

void AppSecure::remove(QString key)
{
    DeletePasswordJob dpj(QLatin1String(APP_NAME));
    dpj.setAutoDelete(false);
    dpj.setKey(key);
    QEventLoop loop;
    dpj.connect(&dpj, SIGNAL(finished(QKeychain::Job*)), &loop, SLOT(quit()));
    dpj.start();
    loop.exec();
}
