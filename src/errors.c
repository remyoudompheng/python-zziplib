#include "pyzzip.h"

PyTypeObject *PyZzipError_T;

void add_error_types(PyObject *m) {
  PyZzipError_T = PyErr_NewException("zziplib.Error", NULL, NULL);
  PyZzipError_T->tp_doc = "Errors from zziplib.";
  PyModule_AddObject(m, "Error", (PyObject*) PyZzipError_T);
  Py_INCREF(PyZzipError_T);
}
