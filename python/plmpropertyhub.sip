%Module plmpropertyhub

%Import QtCore/QtCoremod.sip
%Import plmerror.sip

//%Include QtCore/qpycore_qhash.sip
%Include plmmappedtypes.sip
class PLMPropertyHub : QObject
{
%TypeHeaderCode
#include "./plmpropertyhub.h"
%End


public:
 
    explicit PLMPropertyHub(QObject *parent, const QString &tableName, const QString &paperCodeFieldName);

    QList<int> getAllIdsWithPaperCode(int projectId, int paperCode) const;
    PLMError setProperty(int projectId, int paperCode, const QString &name, const QString &value);
    int getLastAddedId();
    PLMError addProperty(int projectId, int paperCode, int imposedPropertyId = -1);
    PLMError removeProperty(int projectId, int propertyId);
    PLMError setPropertyById(int projectId, int propertyId, const QString &name, const QString &value);
    PLMError setId(int projectId, int propertyId, int newId);
    PLMError setValue(int projectId, int propertyId, const QString &value);
    PLMError setName(int projectId, int propertyId, const QString &name);
    QString getName(int projectId, int propertyId);
    PLMError setPaperCode(int projectId, int propertyId, int paperCode);
    int getPaperCode(int projectId, int propertyId);
    PLMError setCreationDate(int projectId, int propertyId, const QDateTime &date);
    QDateTime getCreationDate(int projectId, int propertyId) const;
    PLMError setModificationDate(int projectId, int propertyId, const QDateTime &date);
    QDateTime getModificationDate(int projectId, int propertyId) const;
    PLMError setSystem(int projectId, int propertyId, bool isSystem);
    bool getSystem(int projectId, int propertyId) const;
    bool propertyExists(int projectId, int paperCode, const QString &name);
    int findPropertyId(int projectId, int paperCode, const QString &name);
    QString getProperty(int projectId, int paperCode, const QString &name) const;
    QString getPropertyById(int projectId, int propertyId) const;
    QHash<int, QString> getAllNames(int projectId) const;
    QHash<int, QString> getAllValues(int projectId) const;
    QHash<int, bool> getAllIsSystems(int projectId) const;
    QHash<int, int> getAllPaperCodes(int projectId) const;
    QList<int> getAllIds(int projectId) const;
   
signals:
    void errorSent(const PLMError &error) const;
    void propertyChanged(int projectId, int propertyId, int paperCode, const QString &name, const QString &value);
    void idChanged(int projectId, int propertyId, int newId);
    void propertyAdded(int projectId, int propertyId);
    void propertyRemoved(int projectId, int propertyId);

};
