%Module plmnotehub

%Import QtCore/QtCoremod.sip
%Import plmpaperhub.sip

//%Include QtCore/qpycore_qhash.sip
%Include plmmappedtypes.sip


class PLMNoteHub : public PLMPaperHub
{
%TypeHeaderCode
#include "./plmnotehub.h"
%End

public:
    PLMNoteHub(QObject *parent);
    int getSynopsisFromSheetCode(int projectId, int sheetId);
    QHash<int, int> getAllSynopsisWithSheetCode(int projectId);
    QHash<int, int> getAllSheetCodes(int projectId);
};
