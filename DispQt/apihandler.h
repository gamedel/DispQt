// apihandler.h
#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ApiHandler : public QObject
{
    Q_OBJECT
public:
    explicit ApiHandler(QObject* parent = nullptr);
    Q_INVOKABLE void fetchData();

signals:
    void dataFetched(const QString& data);

private slots:
    void onFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager m_networkAccessManager;
};

#endif // APIHANDLER_H