#include "apihandler.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QString mergeGetCached(const QString& _getData, const QString& _cachedData) {
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
                QString commentText = commentObj["Comment"].toString();
                if (!commentText.isEmpty()) {
                    obj["Comment"] = commentText;
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



ApiHandler::ApiHandler(QObject* parent) : QObject(parent), cacheManager()
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &ApiHandler::onFinished);

    

}
void ApiHandler::loadCachedData() {
    if (!cacheManager.cachedData.isEmpty()) {
        emit dataFetched(cacheManager.cachedData);
    }
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
        getData = QString::fromUtf8(reply->readAll());
        

        if (cacheManager.cachedData.isEmpty()) {
            // Если данных нет в кэше, сохраняем новые данные
            cacheManager.cacheData(reply->url().toString(), getData);
        }
        else {
            // Если данные уже есть в кэше, объединяем их с новыми данными
            // Здесь вам нужно будет написать свою логику объединения
            getData = mergeGetCached(getData,cacheManager.cachedData);
            cacheManager.cacheData(reply->url().toString(), getData);
        }



        emit dataFetched(getData);
    }
    reply->deleteLater();
}

