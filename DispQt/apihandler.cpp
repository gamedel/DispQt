#include "apihandler.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QString mergeGetCached(const QString& _getData, const QString& _cachedData) {
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
                QString commentText = commentObj["Comment"].toString();
                if (!commentText.isEmpty()) {
                    obj["Comment"] = commentText;
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
            // ���� ������ ��� � ����, ��������� ����� ������
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

