#include "model.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
//#include <iostream>


Model::Model(QObject* parent): QObject(parent)
{
    
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cache.db");

    if (!db.open()) {
        // Обработка ошибки открытия базы данных
        
    }
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS api_cache (key TEXT PRIMARY KEY, value TEXT)")) {
        // Обработка ошибки создания таблицы
       
    }
   
    cachedData = loadData("https://jsonplaceholder.typicode.com/users");
}

void Model::commentAdd(const QString& _userid, const QString& _comment) {

    if (!_comment.isEmpty()) {
        // Преобразование строки JSON в QJsonDocument
        QJsonDocument doc = QJsonDocument::fromJson(cachedData.toUtf8());
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
        cachedData = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
        cacheData("https://jsonplaceholder.typicode.com/users", cachedData);
       // loadCachedData();
        emit commentAdded();
    }
}


void Model::cacheData(const QString& key, const QString& value) { 

    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO api_cache (key, value) VALUES (:key, :value)");
    query.bindValue(":key", key);
    query.bindValue(":value", value);

    if (!query.exec()) {
        // Обработка ошибки записи в базу данных
    }

    cachedData = value;
}

QString Model::loadData(const QString& key) {
    QSqlQuery query;
    query.prepare("SELECT value FROM api_cache WHERE key = :key");
    query.bindValue(":key", key);


    if (!query.exec()) {
        QSqlError error = query.lastError();
        qDebug() << "Database error: " << error.text();
        QString jj = error.text();
    }

    if (query.next()) {
        return query.value(0).toString();
    }
    else {
        return QString();
    }
}

