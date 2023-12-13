// cachemanager.h
#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>


class CacheManager 
{
   public:
    explicit CacheManager();
    void cacheData(const QString& key, const QString& value);
    QString loadData(const QString& key);
    QString cachedData;
   private:
    QSqlDatabase db;
};






#endif // CACHEMANAGER_H