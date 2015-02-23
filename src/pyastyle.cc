#include "pyastyle.h"
#include <stddef.h>


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
    PyGILState_STATE gstate = PyGILState_Ensure();
    // Raise an exception in python script
    PyErr_Format(PyAStyle_Error, "[%d] %s", error_number, error_message);
    PyGILState_Release(gstate);
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

    Py_BEGIN_ALLOW_THREADS
    formatted_code = AStyleMain(source, options, astyle_error_handler, astyle_mem_alloc);
    Py_END_ALLOW_THREADS

    PyMem_Free(source);
    PyMem_Free(options);

    if (formatted_code == NULL || PyErr_Occurred()) {
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

/* Docstrings */
PyDoc_STRVAR(
    pyastyle__doc__,
    "Python wrapper module for Artistic Style."
);

PyDoc_STRVAR(
    pyastyle_format__doc__,
    "format(code[, options]) -> unicode\n"
    "\n"
    "Format code using Artistic Style, see http://astyle.sourceforge.net/astyle.html for options.\n"
    "Return formatted code."
);

PyDoc_STRVAR(
    pyastyle_version__doc__,
    "version() -> str\n"
    "\n"
    "Get the version of the embedded Artistic Style library."
);

/* Method table for python module */
static PyMethodDef pyastyle_methods[] = {
    {"format", PyAStyle_Format, METH_VARARGS, pyastyle_format__doc__},
    {"version", PyAStyle_Version, METH_NOARGS, pyastyle_version__doc__},
    {NULL, NULL, 0, NULL},
};

#if IS_PY3K
static PyModuleDef pyastyle_moduledef = {
    PyModuleDef_HEAD_INIT,
    MOD_PYASTYLE,
    pyastyle__doc__,
    -1,
    pyastyle_methods,
    NULL,
    NULL,
    NULL,
    NULL,
};
#endif /* IS_PY3K */

PyObject *PyAStyle_Error;

static void define_exceptions(PyObject *module)
{
    PyAStyle_Error = PyErr_NewException(const_cast<char *>(MOD_PYASTYLE ".error"), NULL, NULL);
    Py_INCREF(PyAStyle_Error);
    PyModule_AddObject(module, "error", PyAStyle_Error);
}

#if IS_PY3K
PyMODINIT_FUNC PyInit_pyastyle()
#else /* IS_PY3K */
PyMODINIT_FUNC initpyastyle()
#endif /* IS_PY3K */
{
    PyObject *module = NULL;

#if IS_PY3K
    module = PyModule_Create(&pyastyle_moduledef);
#else /* IS_PY3K */
    module = Py_InitModule3(MOD_PYASTYLE, pyastyle_methods, pyastyle__doc__);
#endif /* IS_PY3K */

    // Error on module initialization
    if (module == NULL) {
#if IS_PY3K
        return NULL;
#else /* IS_PY3K */
        return;
#endif /* IS_PY3K */
    }

    define_exceptions(module);

#if IS_PY3K
    return module;
#endif /* IS_PY3K */
}
