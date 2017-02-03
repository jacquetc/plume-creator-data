/***************************************************************************
 *   Copyright (C) 2016 by Cyril Jacquet                                   *
 *   cyril.jacquet@plume-creator.eu                                        *
 *                                                                         *
 *  Filename: plmdata.h                                 *
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
#ifndef PLMDATA_H
#define PLMDATA_H

#include <QObject>

#include "plume_creator_data_global.h"
#include "plmsheethub.h"
#include "plmnotehub.h"
#include "plmsignalhub.h"
#include "plmprojecthub.h"
#include "plmerrorhub.h"
#include "plmpropertyhub.h"
#include "tasks/plmprojectmanager.h"

#define plmdata PLMData::instance()



class EXPORT PLMData : public QObject
{
    Q_OBJECT
public:
    explicit PLMData(QObject *parent = 0);
    ~PLMData();

    static PLMData* instance(){
        return m_instance;
    }

    PLMSignalHub *signalHub();
    PLMErrorHub *errorHub();
    PLMSheetHub *sheetHub();
    PLMPropertyHub *sheetPropertyHub();
    PLMNoteHub *noteHub();
    PLMPropertyHub *notePropertyHub();
    PLMProjectHub *projectHub();


signals:

public slots:

private:
    static PLMData* m_instance;

    PLMErrorHub *m_errorHub;
    PLMSignalHub *m_signalHub;
    PLMProjectHub *m_projectHub;
    PLMSheetHub *m_sheetHub;
    PLMNoteHub *m_noteHub;
    PLMProjectManager *m_projectManager;
    PLMPropertyHub *m_notePropertyHub, *m_sheetPropertyHub;



};

#endif // PLMDATA_H
