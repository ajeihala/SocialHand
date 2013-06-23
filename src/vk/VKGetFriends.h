#ifndef VKGETFRIENDS_H
#define VKGETFRIENDS_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class VKGetFriends : public QObject
{
    Q_OBJECT
public:
    explicit VKGetFriends(QString userId, QObject *parent = 0);
    
signals:
    
public slots:
    
private slots:
    void onFinished(QNetworkReply* reply);

private:
    static QNetworkAccessManager* getNetworkAccessManager();
};

#endif // VKGETFRIENDS_H
