%MappedType QHash<int, int> 
/TypeHint="Dict[int, int]", TypeHintValue="{}"/
{
%TypeHeaderCode
#include <qhash.h>
%End

%ConvertFromTypeCode
    PyObject *d = PyDict_New();

    if (!d)
        return 0;

    QHash<int, int>::const_iterator it = sipCpp->constBegin();
    QHash<int, int>::const_iterator end = sipCpp->constEnd();

    while (it != end)
    {
        PyObject *kobj = SIPLong_FromLong(it.key());

        if (!kobj)
        {
            Py_DECREF(d);

            return 0;
        }


        PyObject *vobj = SIPLong_FromLong(it.value());


        if (!vobj)
        {
            Py_DECREF(kobj);
            Py_DECREF(d);

            return 0;
        }

        int rc = PyDict_SetItem(d, kobj, vobj);

        Py_DECREF(vobj);
        Py_DECREF(kobj);

        if (rc < 0)
        {
            Py_DECREF(d);

            return 0;
        }

        ++it;
    }

    return d;
%End

%ConvertToTypeCode
    if (!sipIsErr)
        return PyDict_Check(sipPy);

    QHash<int, int> *qh = new QHash<int, int>;

    SIP_SSIZE_T pos = 0;
    PyObject *kobj, *vobj;
 
    while (PyDict_Next(sipPy, &pos, &kobj, &vobj))
    {
        PyErr_Clear();
        int k = SIPLong_AsLong(kobj);

        if (PyErr_Occurred())
        {
            PyErr_Format(PyExc_TypeError,
                    "a dict key has type '%s' but 'int' is expected",
                    Py_TYPE(kobj)->tp_name);

            delete qh;
            *sipIsErr = 1;

            return 0;
        }

        int v = SIPLong_AsLong(vobj);

        if (PyErr_Occurred())
        {
            PyErr_Format(PyExc_TypeError,
                    "a dict value has type '%s' but 'int' is expected",
                    Py_TYPE(vobj)->tp_name);

            delete qh;
            *sipIsErr = 1;

            return 0;
        }

        qh->insert(k, v);
    }
 
    *sipCppPtr = qh;
 
    return sipGetState(sipTransferObj);
%End
};


//-------------------------------------------------------------


%MappedType QHash<int, bool> 
/TypeHint="Dict[int, bool]", TypeHintValue="{}"/
{
%TypeHeaderCode
#include <qhash.h>
%End

%ConvertFromTypeCode
    PyObject *d = PyDict_New();

    if (!d)
        return 0;

    QHash<int, bool>::const_iterator it = sipCpp->constBegin();
    QHash<int, bool>::const_iterator end = sipCpp->constEnd();

    while (it != end)
    {
        PyObject *kobj = SIPLong_FromLong(it.key());

        if (!kobj)
        {
            Py_DECREF(d);

            return 0;
        }
        
        PyObject *vobj = PyBool_FromLong(it.value());


        if (!vobj)
        {
            Py_DECREF(kobj);
            Py_DECREF(d);

            return 0;
        }

        int rc = PyDict_SetItem(d, kobj, vobj);

        Py_DECREF(vobj);
        Py_DECREF(kobj);

        if (rc < 0)
        {
            Py_DECREF(d);

            return 0;
        }

        ++it;
    }

    return d;
%End

%ConvertToTypeCode
    if (!sipIsErr)
        return PyDict_Check(sipPy);

    QHash<int, bool> *qh = new QHash<int, bool>;

    SIP_SSIZE_T pos = 0;
    PyObject *kobj, *vobj;
 
    while (PyDict_Next(sipPy, &pos, &kobj, &vobj))
    {
        PyErr_Clear();
        int k = SIPLong_AsLong(kobj);

        if (PyErr_Occurred())
        {
            PyErr_Format(PyExc_TypeError,
                    "a dict key has type '%s' but 'int' is expected",
                    Py_TYPE(kobj)->tp_name);

            delete qh;
            *sipIsErr = 1;

            return 0;
        }

        bool v;
        if(vobj)
            v = true;
        else
            v = false;
            
        if (PyErr_Occurred())
        {
            PyErr_Format(PyExc_TypeError,
                    "a dict value has type '%s' but 'bool' is expected",
                    Py_TYPE(vobj)->tp_name);

            delete qh;
            *sipIsErr = 1;

            return 0;
        }

        qh->insert(k, v);
    }
 
    *sipCppPtr = qh;
 
    return sipGetState(sipTransferObj);
%End
};


//-------------------------------------------------------------


