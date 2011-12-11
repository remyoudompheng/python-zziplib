#include <Python.h>
#include "pyzzip.h"

extern PyObject* PyZzipError_T;

static PyMethodDef dir_methods [] = {
  { NULL, NULL, 0, NULL },
};

static void dir_dealloc(PyZzipDir *self) {
  if (self->dir != NULL) {
    zzip_dir_close(self->dir);
    self->dir = NULL;
  }
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* dir_new(PyTypeObject *subtype, PyObject *args, PyObject *kwargs) {
  char *filename;
  char *keywords[] = { "path", NULL };
  zzip_error_t errcode = 0;
  PyZzipDir *result = subtype->tp_alloc(subtype, 0);

  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s:Dir", keywords, &filename))
    return NULL;

  result->dir = zzip_dir_open(filename, &errcode);
  if (errcode == 0) {
    Py_INCREF(result);
    return (PyObject*)result;
  } else {
    PyErr_SetObject(PyZzipError_T, PyInt_FromLong(errcode));
    return NULL;
  }
}

PyTypeObject PyZzipDir_T = {
  .tp_name = "Dir",
  .tp_basicsize = sizeof(PyZzipDir),
  .tp_alloc = PyType_GenericAlloc,
  .tp_dealloc = (destructor)dir_dealloc,
  .tp_doc = "An object representing a Zip archive.",
  .tp_methods = dir_methods,
  .tp_new = dir_new,
};

void add_dir_types(PyObject *m) {
  PyObject *t = &PyZzipDir_T;

  if (PyType_Ready(&PyZzipDir_T) < 0)
    return;

  Py_INCREF(t);
  PyModule_AddObject(m, "Dir", t);
}
