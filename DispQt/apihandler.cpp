#include "apihandler.h"
#include <QUrl>
#include <QNetworkRequest>

ApiHandler::ApiHandler(QObject* parent) : QObject(parent)
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &ApiHandler::onFinished);
}

void ApiHandler::fetchData()
{
    QUrl url("https://jsonplaceholder.typicode.com/users");
    QNetworkRequest request(url);
    m_networkAccessManager.get(request);
}


void ApiHandler::onFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QString data = QString::fromUtf8(reply->readAll());
        emit dataFetched(data);
    }
    reply->deleteLater();
}