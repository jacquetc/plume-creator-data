/***************************************************************************
 *   Copyright (C) 2016 by Cyril Jacquet                                 *
 *   cyril.jacquet@plume-creator.eu                                        *
 *                                                                         *
 *  Filename: plmimporter.h                                                   *
 *  This file is part of Plume Creator.                                    *
 *                                                                         *
 *  Plume Creator is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  Plume Creator is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Plume Creator.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef PLMIMPORTER_H
#define PLMIMPORTER_H

#include <QObject>
#include <QtSql/QSqlDatabase>

#include "plmerror.h"

class PLMImporter : public QObject
{
    Q_OBJECT
public:
    explicit PLMImporter(QObject *parent = 0);

    QSqlDatabase createSQLiteDbFrom(const QString &type, const QString &fileName, int projectId, PLMError &error);
    QSqlDatabase createEmptySQLiteProject(int projectId, PLMError &error);
signals:

public slots:

private:
    QSqlDatabase copySQLiteDbToMemory(QSqlDatabase sourceSqlDb, int projectId, PLMError &error);

};

#endif // PLMIMPORTER_H
