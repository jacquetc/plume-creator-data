%Module plmsignalhub

%Import QtCore/QtCoremod.sip

class PLMSignalHub : QObject
{
%TypeHeaderCode
#include "./plmsignalhub.h"
%End

public:
  	explicit PLMSignalHub(QObject *parent);

signals:
    void errorSent(const QString &errorCode);

};
