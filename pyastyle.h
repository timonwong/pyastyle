#ifndef __PYASTYLE_H__
#define __PYASTYLE_H__

#include <Python.h>

#if PY_MAJOR_VERSION >= 3
#   define IS_PY3K      1
#endif

#ifdef __cplusplus
extern "C" {
#endif

PyObject *PyAStyle_Format(PyObject *self, PyObject *args);
PyObject *PyAStyle_Version(PyObject *self, PyObject *args);

#ifdef __cplusplus
}
#endif

#endif /* __PYASTYLE_H__ */
