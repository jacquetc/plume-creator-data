
QT -= gui
QT += sql
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

VERSION = 1.61

TARGET = plume-creator-data
TEMPLATE = lib
DEFINES += PLUME_CREATOR_DATA_LIBRARY

CONFIG(release, debug|release) {
MYDLLDIR = $$IN_PWD
DESTDIR = \"$$MYDLLDIR\"
SDIR = \"$$IN_PWD/\"
DDIR = \"$$MYDLLDIR/\"
}

CONFIG(debug, debug|release) {

MYDLLDIR = $$IN_PWD/../../lib
DESTDIR = \"$$MYDLLDIR\"
SDIR = \"$$IN_PWD/\"
DDIR = \"$$MYDLLDIR/\"

}

SOURCES += \
    plmdata.cpp \
    plmpaperhub.cpp \
    plmprojecthub.cpp \
    tasks/sql/plmexporter.cpp \
    tasks/sql/plmimporter.cpp \
    tasks/sql/plmproperty.cpp \
    tasks/sql/tree/plmdbpaper.cpp \
    tasks/sql/tree/plmdbtree.cpp \
    tasks/sql/tree/plmnotetree.cpp \
    tasks/sql/tree/plmsheettree.cpp \
    tasks/sql/tree/plmtree.cpp \
    tasks/plmprojectmanager.cpp \
    tasks/sql/plmproject.cpp \
    plmerrorhub.cpp \
    tasks/plmtaskerror.cpp \
    tasks/plmprojectloadproject.cpp \
    tasks/plmsqlqueries.cpp \
    plmerror.cpp \
    plmsheethub.cpp \
    plmnotehub.cpp \
    plmpropertyhub.cpp \
    tasks/sql/plmupgrader.cpp

HEADERS += \
    tasks/plmtask.h \
    plmdata.h \
    plmsignalhub.h \
    plmpaperhub.h \
    plmprojecthub.h \
    tasks/plmprojectcloseproject.h \
    tasks/plmprojectloadproject.h \
    tasks/plmprojectcloseallprojects.h \
    tasks/sql/plmexporter.h \
    tasks/sql/plmimporter.h \
    tasks/sql/plmproperty.h \
    tasks/sql/tree/plmdberror.h \
    tasks/sql/tree/plmdbpaper.h \
    tasks/sql/tree/plmdbtree.h \
    tasks/sql/tree/plmnotetree.h \
    tasks/sql/tree/plmsheettree.h \
    tasks/sql/tree/plmtree.h \
    tasks/plmprojectmanager.h \
    tasks/sql/plmproject.h \
    tasks/plmprojectgetprojectidlist.h \
    plmerrorhub.h \
    tasks/plmtaskerror.h \
    tools.h \
    tasks/plmprojectgetpath.h \
    tasks/plmprojectsetpath.h \
    tasks/plmprojectsaveprojectas.h \
    tasks/plmprojectsaveproject.h \
    tasks/plmprojectgetlastloaded.h \
    plume_creator_data_global.h \
    tasks/plmsqlqueries.h \
    plmerror.h \
    plmsheethub.h \
    plmnotehub.h \
    plmpropertyhub.h \
    tasks/sql/plmupgrader.h

OTHER_FILES += \
    version.info.in


# python :

DISTFILES += \
    ../LICENSE
