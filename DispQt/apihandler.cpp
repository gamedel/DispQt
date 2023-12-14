#include "apihandler.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QString getData;

ApiHandler::ApiHandler(QObject* parent) : QObject(parent), cacheManager()
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &ApiHandler::onFinished);

}


QString ApiHandler::mergeGetCached(const QString& _getData, const QString& _cachedData) {
    
    // �������������� ������ JSON � QJsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(_getData.toUtf8());
    // ��������� ������� �������� �� ��������� JSON
    QJsonArray array = doc.array();  
    // �������������� ������ ������������ � QJsonArray
    QJsonArray cachedDataJArray = QJsonDocument::fromJson(_cachedData.toUtf8()).array();

    // ���������� ������������ � ������ ������ � �������
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();

        // ����� ����������� � ����� �� id, ��� � �������
        for (const QJsonValue& comment : cachedDataJArray) {
            QJsonObject commentObj = comment.toObject();
            if (commentObj["id"].toInt() == obj["id"].toInt()) {
                // ���� id ��������� � ����������� �� ������, ��������� ����������� � �������
                QString commentText = commentObj["comment"].toString();
                if (!commentText.isEmpty()) {
                    obj["comment"] = commentText;
                }
                break;
            }
        }

        array[i] = obj;
    }

    // ���������� ��������� JSON ����� ��������
    doc.setArray(array);

    // �������������� ������������ ��������� JSON ������� � ������
    return QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
}


void ApiHandler::addComment(const QString& _userid, const QString& _comment) {

    if (!_comment.isEmpty()) {
        // �������������� ������ JSON � QJsonDocument
        QJsonDocument doc = QJsonDocument::fromJson(getData.toUtf8());
        // ��������� ������� �������� �� ��������� JSON
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
        getData = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
        cacheManager.cacheData("https://jsonplaceholder.typicode.com/users", getData);
        loadCachedData();
    }
}









void ApiHandler::loadCachedData() {
    if (!cacheManager.cachedData.isEmpty()) {
        getData = cacheManager.cachedData;
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




void ApiHandler::onFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        //
        

        if (cacheManager.cachedData.isEmpty()) {
            // ���� ������ ��� � ����, ��������� ����� ������
            getData = QString::fromUtf8(reply->readAll());
            cacheManager.cacheData(reply->url().toString(), getData);
        }
        else {
            // ���� ������ ��� ���� � ����, ���������� �� � ������ �������
            // ����� ��� ����� ����� �������� ���� ������ �����������
            getData = mergeGetCached(getData,cacheManager.cachedData);
            cacheManager.cacheData(reply->url().toString(), getData);
        }



        emit dataFetched(getData);
    }
    reply->deleteLater();
}

