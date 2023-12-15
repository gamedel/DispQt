#include "apihandler.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//QString getData;

ApiHandler::ApiHandler(QObject* parent) : QObject(parent), cacheManager()
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &ApiHandler::onFinished);

}


QString ApiHandler::mergeGetCached(const QString& _getData, const QString& _cachedData) {
    
    // Преобразование строки JSON в QJsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(_getData.toUtf8());
    // Получение массива объектов из документа JSON
    QJsonArray array = doc.array();  
    // Преобразование строки комментариев в QJsonArray
    QJsonArray cachedDataJArray = QJsonDocument::fromJson(_cachedData.toUtf8()).array();

    // Добавление комментариев в каждый объект в массиве
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();

        // Поиск комментария с таким же id, как у объекта
        for (const QJsonValue& comment : cachedDataJArray) {
            QJsonObject commentObj = comment.toObject();
            if (commentObj["id"].toInt() == obj["id"].toInt()) {
                // Если id совпадают и комментарий не пустой, добавляем комментарий к объекту
                QString commentText = commentObj["comment"].toString();
                if (!commentText.isEmpty()) {
                    obj["comment"] = commentText;
                }
                break;
            }
        }

        array[i] = obj;
    }

    // Обновление документа JSON новым массивом
    doc.setArray(array);

    // Преобразование обновленного документа JSON обратно в строку
    return QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
}




void ApiHandler::addComment(const QString& _userid, const QString& _comment) {

    if (!_comment.isEmpty()) {
        // Преобразование строки JSON в QJsonDocument
        QJsonDocument doc = QJsonDocument::fromJson(cacheManager.cachedData.toUtf8());
        // Получение массива объектов из документа JSON
        QJsonArray array = doc.array();
        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array[i].toObject();
            if (obj["id"].toInt() == _userid.toInt()) {

                obj["comment"] = _comment;
                array[i] = obj;
                break;
            }


        }
        doc.setArray(array);
        cacheManager.cachedData = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
        cacheManager.cacheData("https://jsonplaceholder.typicode.com/users", cacheManager.cachedData);
        loadCachedData();
    }
}









void ApiHandler::loadCachedData() {
    if (!cacheManager.cachedData.isEmpty()) {
        //getData = cacheManager.cachedData;
        emit dataFetched(cacheManager.cachedData);
    }
}

void ApiHandler::commentData(QString userId, QString commText)
{
    addComment(userId, commText);
}

void ApiHandler::fetchData()
{
    QUrl url("https://jsonplaceholder.typicode.com/users");
    QNetworkRequest request(url);
    m_networkAccessManager.get(request);
}



QString getData;

void ApiHandler::onFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        //
        

        if (cacheManager.cachedData.isEmpty()) {
            // Если данных нет в кэше, сохраняем новые данные
            cacheManager.cachedData = QString::fromUtf8(reply->readAll());
            cacheManager.cacheData(reply->url().toString(), cacheManager.cachedData);
        }
        else {
            getData = QString::fromUtf8(reply->readAll());
            cacheManager.cachedData = mergeGetCached(getData,cacheManager.cachedData);
            cacheManager.cacheData(reply->url().toString(), cacheManager.cachedData);
        }


        emit dataFetched(cacheManager.cachedData);
    }
    reply->deleteLater();
}

