%Module plmerror

%Import QtCore/QtCoremod.sip

class PLMError : QObject
{
%TypeHeaderCode
#include "./plmerror.h"
%End
public:
	explicit PLMError();
    void setSuccess(bool value);
    bool isSuccess() const;
    PLMError(const PLMError &error);
    operator bool() const;

};
