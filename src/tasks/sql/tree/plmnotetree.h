/***************************************************************************
 *   Copyright (C) 2015 by Cyril Jacquet                                 *
 *   cyril.jacquet@plume-creator.eu                                        *
 *                                                                         *
 *  Filename: plmnotetree.h                                                   *
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
#ifndef PLMNOTETREE_H
#define PLMNOTETREE_H

#include <QObject>
#include "plmtree.h"

class PLMNoteTree : public PLMTree
{
    Q_OBJECT

public:
    PLMNoteTree(QObject *parent, const QString &tableName, const QString &codeName, QSqlDatabase sqlDb);
    int addNewChildNote(int parentNoteId = -1);
    void moveNoteToSynopsis(int parentNoteId);
    bool getIsSynopsis(int noteId);
    void setIsSynopsis(int noteId, bool value);
    int getSheetCode(int noteId);
    void setSheetCode(int noteId, int value);
};

#endif // PLMNOTETREE_H
