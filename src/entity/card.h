#ifndef CARD_H
#define CARD_H

#include <QRegularExpression>
#include <QString>

#include "../transformations.h"

class Card
{
public:
    const int mtgaId;
    const int multiverseId;
    const QString setCode;
    const QString number;
    const QString name;
    const QString type;
    const QString manaCost;
    const QList<QChar> manaColorIdentity;
    bool isLand;
    bool isArtifact;

    Card(int mtgaId = 0, int multiverseId = 0, QString setCode = "",
         QString number = "", QString name = "", QString type = "",
         QString manaCost = "", QList<QChar> manaColorIdentity = {},
         bool isLand = false, bool isArtifact = false)
        : mtgaId(mtgaId), multiverseId(multiverseId), setCode(setCode),
          number(number), name(name), type(type), manaCost(manaCost),
          manaColorIdentity(manaColorIdentity), isLand(isLand), isArtifact(isArtifact){}

    int manaCostValue()
    {
        int manaValue = 0;
        for (QChar mana : manaCost) {
            manaValue += mana.isDigit() ? QString(mana).toInt() : 1;
        }
        return manaValue;
    }

    QString manaColorIdentityAsString()
    {
        return Transformations::colorIdentityListToString(manaColorIdentity);
    }

};

#endif // CARD_H
