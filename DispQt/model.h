// model.h
#ifndef MODEL_H
#define MODEL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>


class Model : public QObject
{
    Q_OBJECT
   public:
    explicit Model(QObject* parent);
    void cacheData(const QString& key, const QString& value);
    void mergeGetCached(const QString& _url, const QString& _getData, const QString& _cachedData);
    QString loadData(const QString& key);
    QString cachedData;
    void commentAdd(const QString& _userid, const QString& _comment);
   private:
    QSqlDatabase db;
   signals:
    void commentAdded();
};






#endif // MODEL_H