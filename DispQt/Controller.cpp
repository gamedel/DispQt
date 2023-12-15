#include "controller.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


Controller::Controller(QObject* parent) : QObject(parent), model(parent)
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &Controller::onRecieveData);//Подписываемся на событие приема Json 
    connect(&model, &Model::cacheEdited, this, &Controller::onCacheEdited);//Подписываемся на событие добавления комментария
}

void Controller::refreshUI() {
    if (!model.cachedData.isEmpty()) {
        emit dataFetched(model.cachedData);
    }
}




void Controller::editUserName(QString userId, QString nameText)
{
    model.editUserName(userId, nameText);
}


void Controller::commentData(QString userId, QString commText)
{
    model.commentAdd(userId, commText);
}

void Controller::onCacheEdited() {
    Controller::refreshUI();
}






void Controller::requestData()
{
    QUrl url("https://jsonplaceholder.typicode.com/users");
    QNetworkRequest request(url);
    m_networkAccessManager.get(request);
}



void Controller::onRecieveData(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
 
        model.mergeGetCached(reply->url().toString(), QString::fromUtf8(reply->readAll()), model.cachedData);
        emit dataFetched(model.cachedData);
    }
    reply->deleteLater();
}

