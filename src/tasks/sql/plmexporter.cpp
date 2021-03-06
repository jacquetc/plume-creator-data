/***************************************************************************
 *   Copyright (C) 2016 by Cyril Jacquet                                 *
 *   cyril.jacquet@plume-creator.eu                                        *
 *                                                                         *
 *  Filename: plmexporter.cpp                                                   *
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
#include "plmexporter.h"

PLMExporter::PLMExporter(QObject *parent) : QObject(parent)
{

}

bool PLMExporter::exportSQLiteDbTo(PLMProject*db, const QString &type, const QString &fileName)
{
    if(type == "SQLITE"){

// shrink the database
        db->getSqlDb().transaction();
            QString queryStr("VACUUM");

            QSqlQuery query(db->getSqlDb());
            query.prepare(queryStr);
            query.exec();

        db->getSqlDb().commit();



        QString databaseTempFileName =  db->getTempFileName();

        //copy db temp to file
        QFile tempFile(databaseTempFileName);
        QFile file(fileName);

        if(!tempFile.open(QIODevice::ReadOnly)){
            qWarning() << fileName + " can't be opened";
            return false;
        }
        if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
            qWarning() << fileName + " can't be opened";
            return false;
        }
        QByteArray array(tempFile.readAll());
        file.write(array);
        file.close();

        return true;
    }

return false;
}
