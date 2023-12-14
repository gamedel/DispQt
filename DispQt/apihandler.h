// apihandler.h
#ifndef APIHANDLER_H
#define APIHANDLER_H

#include "cachemanager.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ApiHandler : public QObject
{
    Q_OBJECT
public:
    explicit ApiHandler(QObject* parent = nullptr);
    Q_INVOKABLE void fetchData();
    Q_INVOKABLE void commentData(QString userId,QString commText);
    Q_INVOKABLE void loadCachedData();
    QString mergeGetCached(const QString& _getData, const QString& _cachedData);
    void addComment(const QString& _userid, const QString& _comment);

signals:
    void dataFetched(const QString& data);

private slots:
    void onFinished(QNetworkReply* reply);

private:    
    QNetworkAccessManager m_networkAccessManager;
    CacheManager cacheManager;
    
};

#endif // APIHANDLER_H