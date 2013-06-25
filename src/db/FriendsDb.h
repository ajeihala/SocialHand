#ifndef FRIENDSDB_H
#define FRIENDSDB_H

#include <QObject>

#include "engine/FriendsStorage.h"

class QSqlDatabase;

class FriendsDb : public QObject, public FriendsStorage
{
    Q_OBJECT
public:
    explicit FriendsDb(QObject *parent = 0);
    virtual ~FriendsDb();
    
public: // FrindsStorage
    virtual void storeFriends(QStringList friendsList, QString parentId, int level);

signals:
    
public slots:

private:
    bool createTables();


private:
    QSqlDatabase* _db;
    
};

#endif // FRIENDSDB_H