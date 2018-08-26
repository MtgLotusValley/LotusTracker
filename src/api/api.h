#ifndef DATABASE_H
#define DATABASE_H

#include "auth.h"
#include "requestdata.h"
#include "rqtuploadplayermatch.h"
#include "entity/deck.h"
#include "entity/user.h"
#include "mtg/mtgamatch.h"

#include <QBuffer>
#include <QObject>
#include <QNetworkAccessManager>
#include <QMap>

class LotusTrackerAPI : public QObject
{
    Q_OBJECT
private:
    FirebaseAuth *firebaseAuth;
    RqtRegisterPlayerMatch rqtRegisterPlayerMatch;
    QNetworkAccessManager networkManager;
    QDateTime lastUpdatePlayerCollectionDate, lastUpdatePlayerInventoryDate;
    //Params for recall after refresh token
    QMap<QString, QPair<QString, RequestData>> requestsToRecall;  //url, <method, request>
    Deck paramDeck;

    void getPlayerDeckToUpdate(QString deckID);
    void getPlayerDeckToUpdateRequestOnFinish();
    void getPlayerDeckWinRateRequestOnFinish();
    Deck jsonToDeck(QJsonObject deckJson);
    QNetworkRequest prepareRequest(RequestData requestData,
                                   bool checkUserAuth, QString method = "");
    QBuffer* prepareBody(RequestData requestData);
    void sendPatch(RequestData requestData);
    void sendPost(RequestData requestData);
    void requestOnFinish();
    void registerPlayerMatch(QString matchID);
    void uploadMatchRequestOnFinish();

public:
    explicit LotusTrackerAPI(QObject *parent = nullptr, FirebaseAuth *firebaseAuth = nullptr);
    ~LotusTrackerAPI();
    void updatePlayerCollection(QMap<int, int> ownedCards);
    void updatePlayerInventory(PlayerInventory playerInventory);
    void createPlayerDeck(Deck deck);
    void updatePlayerDeck(Deck deck);
    void getPlayerDeckWinRate(QString deckId, QString eventId);
    void uploadMatch(MatchInfo matchInfo, Deck playerDeck,
                     QString playerRankClass);

signals:
    void sgnRequestFinished();
    void sgnDeckWinRate(int wins, int losses, double winRate);

private slots:
    void onTokenRefreshed();

};

#endif // DATABASE_H