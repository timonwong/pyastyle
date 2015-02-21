#ifndef __PYASTYLE_H__
#define __PYASTYLE_H__

#include "astyle_main.h"
#include <Python.h>

#if PY_MAJOR_VERSION >= 3
#   define IS_PY3K      1
#endif

#ifdef __cplusplus
extern "C" {
#endif

PyObject * PyAStyle_Format(PyObject *self, PyObject *args);
PyObject * PyAStyle_Version(PyObject *self, PyObject *args);

// Exceptions
extern PyObject *PyAStyle_Error;

#ifdef __cplusplus
}
#endif

#endif /* __PYASTYLE_H__ */
