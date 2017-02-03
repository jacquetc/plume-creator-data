%Module plmsheethub

%Import QtCore/QtCoremod.sip
%Import plmpaperhub.sip

//%Include QtCore/qpycore_qhash.sip
%Include plmmappedtypes.sip


class PLMSheetHub : public PLMPaperHub
{
%TypeHeaderCode
#include "./plmsheethub.h"
%End

public:
    PLMSheetHub(QObject *parent);

};
