%Module plmerrorhub

%Import QtCore/QtCoremod.sip
%Import plmerror.sip

class PLMErrorHub : QObject
{
%TypeHeaderCode
#include "./plmerrorhub.h"
%End

public:
    explicit PLMErrorHub(QObject *parent);
    //QList<QString> getlatestError() const;
    //QList<QString> getError(int index) const;
    //int count();
    //void clear();
signals:
    //void errorSent(const QString &errorCode, const QString &origin, const QString &message);
    //void errorSent();
      void errorSent(PLMError error);

public slots:

    //void addError(const QString &errorCode, const QString &origin, const QString &message);
 
};
