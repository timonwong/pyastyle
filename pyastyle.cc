#include "pyastyle.h"
#include <stddef.h>

#if IS_PY3K
#   define INITERROR return NULL
#else /* IS_PY3K */
#   define INITERROR return
#endif /* IS_PY3K */

static char * STDCALL astyle_mem_alloc(unsigned long size)
{
    return new char[size];
}

static inline void astyle_mem_free(char *p)
{
    delete[] p;
}

static void STDCALL astyle_error_handler(int error_number, const char *error_message)
{
    // Raise an exception in python script
    PyErr_Format(PyAStyle_Error, "[%d] %s", error_number, error_message);
}

PyObject * PyAStyle_Format(PyObject * /* self */, PyObject *args)
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

PyObject * PyAStyle_Version(PyObject * /* self */, PyObject * /* args */)
{
    return Py_BuildValue("s", AStyleGetVersion());
}

// Method table for python script
static PyMethodDef pyastyle_methods[] = {
    {"format", PyAStyle_Format, METH_VARARGS, NULL},
    {"version", PyAStyle_Version, METH_NOARGS, NULL},
    {NULL, NULL, 0, NULL}
};

#if IS_PY3K
static struct PyModuleDef pyastyle_moduledef = {
    PyModuleDef_HEAD_INIT,
    "pyastyle",
    "Wrapper library for Artistic Style",
    -1,
    pyastyle_methods
};
#endif /* IS_PY3K */

PyObject *PyAStyle_Error;
static void define_exceptions(PyObject *module)
{
    PyAStyle_Error = PyErr_NewException(const_cast<char *>("pyastyle.error"), NULL, NULL);
    Py_INCREF(PyAStyle_Error);
    PyModule_AddObject(module, "error", PyAStyle_Error);
}

PyMODINIT_FUNC
#if IS_PY3K
PyInit_pyastyle(void)
#else /* IS_PY3K */
initpyastyle(void)
#endif /* IS_PY3K */
{
    PyObject *module = NULL;

#if IS_PY3K
    module = PyModule_Create(&pyastyle_moduledef);
#else /* IS_PY3K */
    module = Py_InitModule("pyastyle", pyastyle_methods);
#endif /* IS_PY3K */

    // Error on module initialization
    if (module == NULL) {
        INITERROR;
    }

    define_exceptions(module);

#if IS_PY3K
    return module;
#endif /* IS_PY3K */
}
