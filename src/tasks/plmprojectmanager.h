#ifndef PLMPROJECTMANAGER_H
#define PLMPROJECTMANAGER_H

#include <QObject>

#include "sql/plmproject.h"
#include "plmerror.h"

#define plmProjectManager PLMProjectManager::instance()


class PLMProjectManager : public QObject
{
    Q_OBJECT
public:
    explicit PLMProjectManager(QObject *parent);
    static PLMProjectManager* instance(){
        return m_instance;
    }
    PLMError createNewEmptyDatabase(int &projectId);
    PLMError loadProject(const QString &fileName, int &projectId);
    bool saveProject(int projectId);
    bool saveProjectAs(int projectId, const QString &type, const QString &path);
    PLMProject *project(int projectId);
    QList<int> projectIdList();
    PLMError closeProject(int projectId);

signals:

public slots:

private:
    static PLMProjectManager* m_instance;
    QHash<int, PLMProject*> m_projectForIntHash;
    int m_projectIdIncrement;

};

#endif // PLMPROJECTMANAGER_H
