#include <Python.h>
#include "pyzzip.h"

extern PyTypeObject *PyZzipError_Tp;

static PyObject* dir_openentry(PyObject *self, PyObject *args) {
  PyZzipFile *result = NULL;
  PyZzipDir *this = self;
  char *entryname = NULL;
  ZZIP_FILE *f;

  if (!PyArg_ParseTuple(args, "s", &entryname))
    return NULL;
  if (this->dir == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "archive is not open!");
    return NULL;
  }

  f = zzip_file_open(this->dir, entryname, 'r');
  if (f == NULL) {
    int errcode = zzip_error(this->dir);
    PyErr_SetObject((PyObject*)PyZzipError_Tp, PyInt_FromLong(errcode));
    return NULL;
  }

  /* fprintf(stderr, "Allocing Entry object\n"); */
  result = (PyZzipFile*)PyZzipFile_T.tp_alloc(&PyZzipFile_T, 0);
  result->parent = self;
  result->file = f;
  Py_INCREF(self);
  return (PyObject*)result;
}

static PyMethodDef dir_methods [] = {
  { .ml_name = "open",
    .ml_meth = dir_openentry,
    .ml_flags = METH_VARARGS,
    .ml_doc = "open an entry by name"
  },
  { NULL, NULL, 0, NULL },
};

static void dir_dealloc(PyZzipDir *self) {
  /* fprintf(stderr, "Deallocing Dir object\n"); */
  if (self->dir != NULL) {
    zzip_dir_close(self->dir);
    self->dir = NULL;
  }
  Py_TYPE(self)->tp_free((PyObject*)self);
}

/* returns -1 on error. */
PyObject* pyzzip_opendir(PyObject *self, PyObject *args) {
  char *filename;
  zzip_error_t errcode = 0;
  ZZIP_FILE *f;
  PyZzipDir *this = NULL;

  if (!PyArg_ParseTuple(args, "s:Dir", &filename))
    return NULL;

  f = zzip_dir_open(filename, &errcode);
  if (errcode == 0) {
    /* fprintf(stderr, "Allocing Dir object\n"); */
    this = PyZzipDir_T.tp_alloc(&PyZzipDir_T, 0);
    this->dir = f;
    return this;
  } else {
    PyErr_SetObject((PyObject*)PyZzipError_Tp, PyInt_FromLong(errcode));
    return NULL;
  }
}

PyTypeObject PyZzipDir_T = {
  .tp_name = "zziplib.Dir",
  .tp_basicsize = sizeof(PyZzipDir),
  .tp_alloc = PyType_GenericAlloc,
  .tp_dealloc = (destructor)dir_dealloc,
  .tp_doc = "An object representing a Zip archive.",
  .tp_methods = dir_methods,
  .tp_free = PyObject_Del,
};

void add_dir_types(PyObject *m) {
  PyObject *t = &PyZzipDir_T;

  if (PyType_Ready(&PyZzipDir_T) < 0)
    return;

  Py_INCREF(t);
  PyModule_AddObject(m, "Dir", t);
}
