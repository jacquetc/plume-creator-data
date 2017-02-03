%Module plmprojecthub

%Import QtCore/QtCoremod.sip
%Import plmerror.sip

class PLMProjectHub : QObject
{
%TypeHeaderCode
#include "./plmprojecthub.h"
%End

public:
    explicit PLMProjectHub(QObject *parent);
    PLMError loadProject(const QString &path);
    PLMError saveProject(int projectId);
    PLMError saveProjectAs(int projectId, const QString &type, const QString &path);
    PLMError closeProject(int projectId);
    PLMError closeAllProjects();
    QList<int> getProjectIdList();
    QString getPath(int projectId) const;
    PLMError setPath(int projectId, const QString &newPath);
    int getLastLoaded() const;
    PLMError getError();

signals:
    void errorSent(const PLMError &error) const;
    void projectLoaded(int projectId);
    void projectClosed(int projectId);
    void allProjectsClosed();
    void projectTypeChanged(int projectId, const QString &newType);
    void projectPathChanged(int projectId, const QString &newPath);
    void projectSaved(int projectId);
};
