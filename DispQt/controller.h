// controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject* parent = nullptr);
    Q_INVOKABLE void requestData();
    Q_INVOKABLE void commentData(QString userId,QString commText);
    Q_INVOKABLE void refreshUI();
    

signals:
    void dataFetched(const QString& data);

private slots:
    void onRecieveData(QNetworkReply* reply);
    void onCommentAdded();
private:    
    QNetworkAccessManager m_networkAccessManager;
    Model model;
    
};

#endif // CONTROLLER_H