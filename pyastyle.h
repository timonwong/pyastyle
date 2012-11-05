#ifndef __PYASTYLE_H__
#define __PYASTYLE_H__

#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

// Excpetion class
extern PyObject *PyAStyle_Error;

PyObject *PyAStyle_Format(PyObject *self, PyObject *args);
PyObject *PyAStyle_Version(PyObject *self, PyObject *args);

#ifdef __cplusplus
}
#endif

#endif /* __PYASTYLE_H__ */
