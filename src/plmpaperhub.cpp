#include "plmpaperhub.h"
#include "tools.h"
#include "tasks/plmsqlqueries.h"

#include <QDateTime>
#include <QDebug>

///
/// \brief PLMPaperHub::PLMPaperHub
/// \param parent
//
PLMPaperHub::PLMPaperHub(QObject *parent, const QString &tableName)
    : QObject(parent), m_tableName(tableName), m_last_added_id(-1)
{
    // connection for 'getxxx' functions to have a way to get errors.
    connect(this, &PLMPaperHub::errorSent, this, &PLMPaperHub::setError, Qt::DirectConnection);

}

///
/// \brief PLMPaperHub::getAll
/// \param projectId
/// \return
///
QList<QHash<QString, QVariant> >  PLMPaperHub::getAll(int projectId) const
{
}

///
/// \brief PLMPaperHub::getAllTitles
/// \param projectId
/// \return
///
QHash<int, QString>  PLMPaperHub::getAllTitles(int projectId) const
{

    PLMError error;
    QHash<int, QString> result;
    QHash<int, QVariant> out;
    PLMSqlQueries queries(projectId, m_tableName);

    error = queries.getValueByIds("t_title", out);

    IFOK(error) {
        result = HashIntQVariantConverter::convertToIntQString(out);
    }

    IFKO(error) {
        emit errorSent(error);
    }
    return result;
}
//------------------------------------------------------------

///
/// \brief PLMPaperHub::getAllIndents
/// \param projectId
/// \return
///
//------------------------------------------------------------

QHash<int, int> PLMPaperHub::getAllIndents(int projectId) const
{
    PLMError error;
    QHash<int, int> result;
    QHash<int, QVariant> out;
    PLMSqlQueries queries(projectId, m_tableName);

    error = queries.getValueByIds("l_indent", out);

    IFOK(error) {
        result = HashIntQVariantConverter::convertToIntInt(out);
    }

    IFKO(error) {
        emit errorSent(error);
    }
    return result;
}

//------------------------------------------------------------

/**
 * @brief PLMPaperHub::getAllIds
 * @param projectId
 * @return
 * Get sorted ids
 */
QList<int> PLMPaperHub::getAllIds(int projectId) const
{
    PLMError error;
    QList<int> result;
    QList<int> out;
    PLMSqlQueries queries(projectId, m_tableName);

    error = queries.getSortedIds(out);

    IFOK(error) {
        result = out;
    }


    IFKO(error) {
        emit errorSent(error);
    }
    return result;
}

//------------------------------------------------------------

QHash<int, int> PLMPaperHub::getAllSortOrders(int projectId) const
{
    PLMError error;
    QHash<int, int> result;
    QHash<int, QVariant> out;
    PLMSqlQueries queries(projectId, m_tableName);

    error = queries.getValueByIds("l_sort_order", out);

    IFOK(error) {
        result = HashIntQVariantConverter::convertToIntInt(out);
    }


    IFKO(error) {
        emit errorSent(error);
    }
    return result;
}

//------------------------------------------------------------
///
/// \brief PLMPaperHub::setId
/// \param projectId
/// \param sheetId
/// \param newId
/// \return
/// Change de id. No date updated. Be careful since ids must be unique (sql constraint)
PLMError PLMPaperHub::setId(int projectId, int sheetId, int newId)
{

    PLMError error;

    PLMSqlQueries queries(projectId, m_tableName);
    queries.beginTransaction();

    error = queries.setId(sheetId, newId);
    IFKO(error){
        queries.rollback();
    }
    IFOK(error){
        queries.commit();
    }
    IFKO(error) {
        emit errorSent(error);
    }
    IFOK(error){
        emit idChanged(projectId, sheetId, newId);
    }
    return error;




}

//------------------------------------------------------------

PLMError PLMPaperHub::setTitle(int projectId, int sheetId, const QString &newTitle)
{
    PLMError error = set(projectId, sheetId, "t_title", newTitle);
    IFOK(error){
        emit titleChanged(projectId, sheetId, newTitle);
    }

    return error;
}

//------------------------------------------------------------

QString PLMPaperHub::getTitle(int projectId, int sheetId) const
{
    return get(projectId, sheetId, "t_title").toString();
}

PLMError PLMPaperHub::setIndent(int projectId, int sheetId, int newIndent)
{
    PLMError error = set(projectId, sheetId, "l_indent", newIndent);
    IFOK(error){
        emit indentChanged(projectId, sheetId, newIndent);
    }
    return error;
}

//------------------------------------------------------------

int PLMPaperHub::getIndent(int projectId, int sheetId) const
{
    return get(projectId, sheetId, "l_indent").toInt();
}

//------------------------------------------------------------

PLMError PLMPaperHub::setSortOrder(int projectId, int sheetId, int newSortOrder)
{
    PLMError error = set(projectId, sheetId, "l_sort_order", newSortOrder);
    IFOK(error){
        emit sortOrderChanged(projectId, sheetId, newSortOrder);
    }
    return error;
}

//------------------------------------------------------------

int PLMPaperHub::getSortOrder(int projectId, int sheetId) const
{
    return get(projectId, sheetId, "l_sort_order").toInt();
}

//------------------------------------------------------------


PLMError PLMPaperHub::setContent(int projectId, int sheetId, const QString &newContent)
{
    PLMError error = set(projectId, sheetId, "m_content", newContent);
    IFOK(error){
        emit contentChanged(projectId, sheetId, newContent);
    }
    return error;
}

//------------------------------------------------------------

QString PLMPaperHub::getContent(int projectId, int sheetId) const
{
    return get(projectId, sheetId, "m_content").toString();

}

//------------------------------------------------------------

PLMError PLMPaperHub::setDeleted(int projectId, int sheetId, bool newDeletedState)
{
    int target_sort_order = getSortOrder(projectId, sheetId);
    int target_indent = getIndent(projectId, sheetId);

    QHash<int,QVariant> result;
    QHash<QString,QVariant> where;
    where.insert("l_indent >", target_indent);
    where.insert("l_sort_order >", target_sort_order);
    if(newDeletedState)
        where.insert("b_deleted =", 0);

    PLMSqlQueries queries(projectId, m_tableName);
    PLMError error = queries.getValueByIdsWhere("l_sort_order", result, where, true);

    QHash<int,QVariant> result_same_indent;
    where.clear();
    where.insert("l_indent =", target_indent);
    where.insert("l_sort_order >", target_sort_order);
    IFOKDO(error, queries.getValueByIdsWhere("l_sort_order", result_same_indent, where, true));

    int lowestSortSameLevel = 0;
    if(!result_same_indent.isEmpty()){
        QHash<int, QVariant>::const_iterator i = result_same_indent.constBegin();
        lowestSortSameLevel = i.value().toInt();
        while (i != result_same_indent.constEnd()) {
            int sort = i.value().toInt();
            if(sort < lowestSortSameLevel)
                lowestSortSameLevel = sort;
            ++i;
        }
    }

    // filter the children
    QList<int> chilrenIdList;
    if(!result.isEmpty()){
        QHash<int, QVariant>::const_iterator i = result.constBegin();
        int lowestSort = 0;
        lowestSort = i.value().toInt();
        while (i != result.constEnd()) {
            int sort = i.value().toInt();
            if(sort < lowestSortSameLevel)
                chilrenIdList.append(i.key());
            ++i;
        }



        // children deletion (or recovery)
        for(int &_id : chilrenIdList){
            IFOKDO(error, set(projectId, _id, "b_deleted", newDeletedState));
            emit deletedChanged(projectId, _id, newDeletedState);
        }



    }
    //TODO:  deletion
    IFOKDO(error, set(projectId, sheetId, "b_deleted", newDeletedState));
    IFOK(error){
        emit deletedChanged(projectId, sheetId, newDeletedState);
    }

    return error;
}

//------------------------------------------------------------

bool PLMPaperHub::getDeleted(int projectId, int sheetId) const
{
    //TODO: do recursive deletion
    return get(projectId, sheetId, "b_deleted").toBool();
}

//------------------------------------------------------------


PLMError PLMPaperHub::setCreationDate(int projectId, int sheetId, const QDateTime &newDate)
{
    PLMError error = set(projectId, sheetId, "dt_created", newDate);
    IFOK(error){
        emit creationDateChanged(projectId, sheetId, newDate);
    }

    return error;

}

//------------------------------------------------------------

QDateTime PLMPaperHub::getCreationDate(int projectId, int sheetId) const
{
    return get(projectId, sheetId, "dt_created").toDateTime();
}

//------------------------------------------------------------

PLMError PLMPaperHub::setUpdateDate(int projectId, int sheetId, const QDateTime &newDate)
{
    PLMError error = set(projectId, sheetId, "dt_updated", newDate);
    IFOK(error){
        emit updateDateChanged(projectId, sheetId, newDate);
    }

    return error;

}

//------------------------------------------------------------

QDateTime PLMPaperHub::getUpdateDate(int projectId, int sheetId) const
{
    return get(projectId, sheetId, "dt_updated").toDateTime();
}

//------------------------------------------------------------

PLMError PLMPaperHub::setContentDate(int projectId, int sheetId, const QDateTime &newDate)
{
    PLMError error = set(projectId, sheetId, "dt_content", newDate);
    IFOK(error){
        emit contentDateChanged(projectId, sheetId, newDate);
    }
    return error;

}

//------------------------------------------------------------

QDateTime PLMPaperHub::getContentDate(int projectId, int sheetId) const
{
    return get(projectId, sheetId, "dt_content").toDateTime();
}

//------------------------------------------------------------

PLMError PLMPaperHub::getError()
{
    return m_error;
}

//------------------------------------------------------------

void PLMPaperHub::setError(const PLMError &error)
{
    m_error = error;
}


//------------------------------------------------------------

PLMError PLMPaperHub::set(int projectId, int sheetId, const QString &fieldName, const QVariant &value, bool setCurrentDateBool)
{
    PLMError error;

    PLMSqlQueries queries(projectId, m_tableName);
    queries.beginTransaction();

    error = queries.set(sheetId, fieldName, value);
    if(setCurrentDateBool){
        IFOKDO(error, queries.setCurrentDate(sheetId, "dt_updated"));
    }
    IFKO(error){
        queries.rollback();
    }
    IFOK(error){
        queries.commit();
    }
    IFKO(error) {
        emit errorSent(error);
    }
    return error;
}

QVariant PLMPaperHub::get(int projectId, int sheetId, const QString &fieldName) const
{
    PLMError error;
    QVariant var;
    QVariant result;
    PLMSqlQueries queries(projectId, m_tableName);
    error = queries.get(sheetId, fieldName, var);
    IFOK(error) {
        result = var;
    }
    IFKO(error) {
        emit errorSent(error);
    }

    return result;
}

//-----------------------------------------------------------------------------

int PLMPaperHub::getLastAddedId()
{
    return m_last_added_id;
}


//-----------------------------------------------------------------------------

PLMError PLMPaperHub::addPaper(const QHash<QString,QVariant> &values, int projectId)
{
    PLMSqlQueries queries(projectId, m_tableName);
    queries.beginTransaction();
    int newId = -1;
    PLMError error = queries.add(values, newId);
    IFOKDO(error, queries.renumberSortOrder());
    IFKO(error){
        queries.rollback();
    }
    IFOK(error){
        queries.commit();
    }
    IFKO(error) {
        emit errorSent(error);
    }
    m_last_added_id = newId;

    IFOK(error){
        emit paperAdded(projectId, newId);
    }


    return error;
}
//-----------------------------------------------------------------------------

PLMError PLMPaperHub::addPaperBelow(int projectId, int targetId)
{
    int target_sort_order = getSortOrder(projectId, targetId);
    int target_indent = getIndent(projectId, targetId);

    //find next node with the same indentation

    QHash<int,QVariant> result;
    QHash<QString,QVariant> where;
    where.insert("l_indent <=", target_indent);
    where.insert("l_sort_order >", target_sort_order);

    PLMSqlQueries queries(projectId, m_tableName);
    PLMError error = queries.getValueByIdsWhere("l_sort_order", result, where, true);


    int finalSortOrder = 0;
    // if node after
    if(!result.isEmpty()){
        QHash<int, QVariant>::const_iterator i = result.constBegin();
        int lowestSort = 0;
        lowestSort = i.value().toInt();
        while (i != result.constEnd()) {
            int sort = i.value().toInt();
            if(sort < lowestSort)
                lowestSort = sort;
            ++i;
        }
        finalSortOrder = lowestSort - 1;

        // if tree is empty
        if(finalSortOrder == -1){
            finalSortOrder = 0;
        }



    }
    // if no node after (bottom of tree)
    else{
        QList<int> idList;
        IFOKDO(error, queries.getSortedIds(idList));
        if(idList.isEmpty()){
            error.setSuccess(false);
            return error;
        }
        int lastId = idList.last();

        QHash<int,QVariant> result2;
        IFOKDO(error, queries.getValueByIds("l_sort_order", result2, "id", QVariant(lastId)));
        finalSortOrder = result2.begin().value().toInt() + 1;
    }

    // finally add paper

    QHash<QString, QVariant> values;
    values.insert("l_sort_order", finalSortOrder);
    values.insert("l_indent", target_indent);

    IFOKDO(error, addPaper(values, projectId));

    return error;
}

//-----------------------------------------------------------------------------

PLMError PLMPaperHub::addChildPaper(int projectId, int targetId)
{
    int target_sort_order = getSortOrder(projectId, targetId);
    int target_indent = getIndent(projectId, targetId);

    //find next node with the same indentation

    QHash<int,QVariant> result;
    QHash<QString,QVariant> where;
    where.insert("l_indent <=", target_indent);
    where.insert("l_sort_order >", target_sort_order);

    PLMSqlQueries queries(projectId, m_tableName);
    PLMError error = queries.getValueByIdsWhere("l_sort_order", result, where, true);


    int finalSortOrder = 0;
    // if node after
    if(!result.isEmpty()){
        QHash<int, QVariant>::const_iterator i = result.constBegin();
        int lowestSort = 0;
        lowestSort = i.value().toInt();
        while (i != result.constEnd()) {
            int sort = i.value().toInt();
            if(sort < lowestSort)
                lowestSort = sort;
            ++i;
        }
        finalSortOrder = lowestSort - 1;

        // if tree is empty
        if(finalSortOrder == -1){
            finalSortOrder = 0;
        }



    }
    // if no node after (bottom of tree)
    else{
        QList<int> idList;
        IFOKDO(error, queries.getSortedIds(idList));
        if(idList.isEmpty()){
            error.setSuccess(false);
            return error;
        }
        int lastId = idList.last();

        QHash<int,QVariant> result2;
        IFOKDO(error, queries.getValueByIds("l_sort_order", result2, "id", QVariant(lastId)));
        finalSortOrder = result2.begin().value().toInt() + 1;
    }

    // finally add paper

    QHash<QString, QVariant> values;
    values.insert("l_sort_order", finalSortOrder);
    values.insert("l_indent", target_indent + 1);

    IFOKDO(error, addPaper(values, projectId));

    return error;
}

//-----------------------------------------------------------------------------

PLMError PLMPaperHub::removePaper(int projectId, int targetId)
{
    PLMSqlQueries queries(projectId, m_tableName);
    queries.beginTransaction();

    PLMError error = queries.remove(targetId);
    IFOKDO(error, queries.renumberSortOrder())
            IFKO(error){
        queries.rollback();
    }
    IFOK(error){
        queries.commit();
    }
    IFKO(error) {
        emit errorSent(error);
    }

    IFOK(error){
        emit paperRemoved(projectId, targetId);
    }


    return error;
}
