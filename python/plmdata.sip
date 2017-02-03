%Module plmdata

%Import QtCore/QtCoremod.sip
%Import plmprojecthub.sip
%Import plmsheethub.sip
%Import plmnotehub.sip
%Import plmsignalhub.sip
%Import plmerrorhub.sip
%Import plmpropertyhub.sip

class PLMData : QObject
{
%TypeHeaderCode
#include "./plmdata.h"
%End

public:
  PLMData(QObject *parent /TransferThis/);
    PLMSignalHub *signalHub();
    PLMErrorHub *errorHub();
    PLMSheetHub *sheetHub();
    PLMPropertyHub *sheetPropertyHub();
    PLMNoteHub *noteHub();
    PLMPropertyHub *notePropertyHub();
    PLMProjectHub *projectHub();
};
