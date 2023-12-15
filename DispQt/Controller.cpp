#include "controller.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//QString getData;

Controller::Controller(QObject* parent) : QObject(parent), model(parent)
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &Controller::onFinished);
    connect(&model, &Model::commentAdded, this, &Controller::onCommentAdded);
}


QString Controller::mergeGetCached(const QString& _getData, const QString& _cachedData) {
    
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








void Controller::onCommentAdded() {
    Controller::refreshUI();
}

void Controller::refreshUI() {
    if (!model.cachedData.isEmpty()) {
        emit dataFetched(model.cachedData);
    }
}


void Controller::commentData(QString userId, QString commText)
{
    model.commentAdd(userId, commText);
}

void Controller::fetchData()
{
    QUrl url("https://jsonplaceholder.typicode.com/users");
    QNetworkRequest request(url);
    m_networkAccessManager.get(request);
}



QString getData;

void Controller::onFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
 
        if (model.cachedData.isEmpty()) {
            model.cachedData = QString::fromUtf8(reply->readAll());
            model.cacheData(reply->url().toString(), model.cachedData);
        }
        else {
            getData = QString::fromUtf8(reply->readAll());
            model.cachedData = mergeGetCached(getData,model.cachedData);
            model.cacheData(reply->url().toString(), model.cachedData);
        }


        emit dataFetched(model.cachedData);
    }
    reply->deleteLater();
}

