#include "cachemanager.h"
#include <QUrl>
#include <QNetworkRequest>



CacheManager::CacheManager()
{
    QSqlQuery query;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cache.db");

    if (!db.open()) {
        // Обработка ошибки открытия базы данных
        int hh = 0;
        QSqlError error = query.lastError();
        qDebug() << "Database error: " << error.text();
        QString jj = error.text();
        hh++;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS api_cache (key TEXT PRIMARY KEY, value TEXT)")) {
        // Обработка ошибки создания таблицы
        int hh = 0;
        QSqlError error = query.lastError();
        qDebug() << "Database error: " << error.text();
        QString jj = error.text();
        hh++;
    }
   
    cachedData = loadData("https://jsonplaceholder.typicode.com/users");

}

void CacheManager::cacheData(const QString& key, const QString& value) { 

    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO api_cache (key, value) VALUES (:key, :value)");
    query.bindValue(":key", key);
    query.bindValue(":value", value);

    if (!query.exec()) {
        // Обработка ошибки записи в базу данных
    }

    cachedData = value;
}

QString CacheManager::loadData(const QString& key) {
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

