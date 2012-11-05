#include "pyastyle.h"
#include "astyle.h"
#include <stddef.h>


PyObject *PyAStyle_Error;

static char * STDCALL astyle_mem_alloc(unsigned long size)
{
    return new char[size];
}

static inline void astyle_mem_free(void *p)
{
    delete[] p;
}

static void STDCALL astyle_error_handler(int error_number, const char *error_message)
{
    // Raise an exception in python script
    PyErr_Format(PyAStyle_Error, "[%d] %s", error_number, error_message);
}

PyObject *PyAStyle_Format(PyObject *self, PyObject *args)
{
    char *source = NULL;
    char *options = NULL;
    char *formatted_code = NULL;
    PyObject *result = NULL;

    if (!PyArg_ParseTuple(args, "es|es:format", "utf8", &source, "utf8", &options)) {
        return NULL;
    }

    formatted_code = AStyleMain(source, options, astyle_error_handler, astyle_mem_alloc);

    PyMem_Free(source);
    PyMem_Free(options);

    if (formatted_code == NULL) {
        return NULL;
    }

    result = PyUnicode_DecodeUTF8(formatted_code, strlen(formatted_code), "strict");
    astyle_mem_free(formatted_code);
    return result;
}

PyObject *PyAStyle_Version(PyObject *self, PyObject *args)
{
    return Py_BuildValue("s", AStyleGetVersion());
}

// Method table for python script
static PyMethodDef AStyleMethods[] = {
    {"format", PyAStyle_Format, METH_VARARGS, NULL},
    {"version", PyAStyle_Version, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initpyastyle(void)
{
    PyObject *m = NULL;

    m = Py_InitModule("pyastyle", AStyleMethods);
    if (m == NULL) { // Error on module initialization
        return;
    }

    // Create an excpetion class for astyle
    PyAStyle_Error = PyErr_NewException("pyastyle.error", NULL, NULL);
    Py_INCREF(PyAStyle_Error);
    PyModule_AddObject(m, "error", PyAStyle_Error);
}
