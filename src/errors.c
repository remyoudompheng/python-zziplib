#include "pyzzip.h"

PyTypeObject *PyZzipError_Tp;

static PyObject* error_str(PyObject* er) {
  PyObject* args = PyObject_GetAttrString(er, "args");
  int errcode;
  if (args == NULL)
    return NULL;
  if (!PyArg_ParseTuple(args, "i", &errcode))
    return NULL;

  const char *errstring = zzip_strerror(errcode);
  if (errstring == NULL) errstring = "<no message>";
  Py_CLEAR(args);
  return PyString_FromFormat("zziplib error: %s (code %d)", errstring, -errcode);
}

void add_error_types(PyObject *m) {
  PyZzipError_Tp = PyErr_NewException("zziplib.Error", NULL, NULL);
  PyZzipError_Tp->tp_doc = "Errors from zziplib.";
  PyZzipError_Tp->tp_str = error_str;
  PyModule_AddObject(m, "Error", (PyObject*) PyZzipError_Tp);
  Py_INCREF(PyZzipError_Tp);
}
