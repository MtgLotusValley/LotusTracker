#ifndef UNTAPPED_H
#define UNTAPPED_H

#include "api/untappedapi.h"

#include <QObject>
#include <QStack>

class Untapped : public QObject
{
    Q_OBJECT
private:
    UntappedAPI *untappedAPI;
    QString dataDir;
    void setupUntappedAPIConnections();

public:
    explicit Untapped(QObject *parent = nullptr);
    void checkForUntappedUploadToken();
    void preparedMatchLogFile(QStack<QString> matchLogMsgs);

signals:

public slots:
};

#endif // UNTAPPED_H