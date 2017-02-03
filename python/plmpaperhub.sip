%Module plmpaperhub

%Import QtCore/QtCoremod.sip
%Import plmerror.sip

//%Include QtCore/qpycore_qhash.sip
%Include plmmappedtypes.sip
class PLMPaperHub : QObject
{
%TypeHeaderCode
#include "./plmpaperhub.h"
%End


public:
 
	explicit PLMPaperHub(QObject *parent, const QString &tableName);
	//QList<QHash<QString, QVariant> > getAll(int projectId) const;
    QHash<int, QString> getAllTitles(int projectId) const;
    QHash<int, int> getAllSortOrders(int projectId) const;
    QHash<int, int>  getAllIndents(int projectId) const;
    QList<int>  getAllIds(int projectId) const;
    PLMError setId(int projectId, int sheetId, int newId);
    PLMError setTitle(int projectId, int sheetId, const QString &newTitle);
    QString getTitle(int projectId, int sheetId) const;

    PLMError setIndent(int projectId, int sheetId, int newIndent);
    int getIndent(int projectId, int sheetId) const;
    PLMError setSortOrder(int projectId, int sheetId, int newSortOrder);
    int getSortOrder(int projectId, int sheetId) const;
    PLMError setContent(int projectId, int sheetId, const QString &newContent);
    QString getContent(int projectId, int sheetId) const;
    PLMError setDeleted(int projectId, int sheetId, bool newDeletedState);
    bool getDeleted(int projectId, int sheetId) const;
    PLMError setCreationDate(int projectId, int sheetId, const QDateTime &newDate);
    QDateTime getCreationDate(int projectId, int sheetId) const;
    PLMError setUpdateDate(int projectId, int sheetId, const QDateTime &newDate);
    QDateTime getUpdateDate(int projectId, int sheetId) const;
    PLMError setContentDate(int projectId, int sheetId, const QDateTime &newDate);
    QDateTime getContentDate(int projectId, int sheetId) const;

    PLMError getError();
    PLMError set(int projectId, int sheetId, const QString &fieldName, const QVariant &value, bool setCurrentDateBool = true);
    QVariant get(int projectId, int sheetId, const QString &fieldName) const;
    
    int getLastAddedId();
    PLMError addPaper(const QHash<QString, QVariant> &values, int projectId);
    PLMError addPaperBelow(int projectId, int targetId);
    PLMError addChildPaper(int projectId, int targetId);
    PLMError removePaper(int projectId, int targetId);



signals:

    void idChanged(int projectId, int paperId, int newId);
    void titleChanged(int projectId, int sheetId, const QString &newTitle);
    void indentChanged(int projectId, int sheetId, int newIndent);
    void sortOrderChanged(int projectId, int sheetId, int newSortOrder);
    void contentChanged(int projectId, int sheetId, const QString &newContent);
    void deletedChanged(int projectId, int sheetId, bool newDeletedState);
    void creationDateChanged(int projectId, int sheetId, const QDateTime &newDate);
    void updateDateChanged(int projectId, int sheetId, const QDateTime &newDate);
    void contentDateChanged(int projectId, int sheetId, const QDateTime &newDate);
    void paperAdded(int projectId, int paperId);
    void paperRemoved(int projectId, int paperId);

};
