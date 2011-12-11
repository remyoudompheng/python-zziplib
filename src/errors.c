#include "pyzzip.h"

PyTypeObject *PyZzipError_Tp;

void add_error_types(PyObject *m) {
  PyZzipError_Tp = PyErr_NewException("zziplib.Error", NULL, NULL);
  PyZzipError_Tp->tp_doc = "Errors from zziplib.";
  PyModule_AddObject(m, "Error", (PyObject*) PyZzipError_Tp);
  Py_INCREF(PyZzipError_Tp);
}
