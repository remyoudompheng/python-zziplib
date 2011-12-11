#include "pyzzip.h"

static PyObject* file_read(PyObject *self, PyObject *args) {
  Py_ssize_t n = 0;
  PyObject *result = NULL;
  PyZzipFile *this = self;
  int err;

  if (!PyArg_ParseTuple(args, "n", &n)) {
    return NULL;
  }

  if (this->file == NULL) {
    PyErr_SetString(PyExc_ValueError, "cannot read of a closed file.");
    return NULL;
  }

  result = PyString_FromStringAndSize(NULL, n);
  if (result == NULL) return NULL;

  n = zzip_file_read(this->file, PyString_AS_STRING(result), n);
  err = _PyString_Resize(&result, n);
  if (err == -1) return NULL;

  return result;
}

static PyObject* file_close(PyObject *self, PyObject *args) {
  PyZzipFile* this = self;
  if (this->file != NULL) {
    zzip_file_close(this->file);
    this->file = NULL;
  }
  Py_CLEAR(this->parent);
  Py_RETURN_NONE;
}

static void file_dealloc(PyZzipFile *self) {
  /* fprintf(stderr, "Deallocing Entry object\n"); */
  file_close(self, NULL);
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyMethodDef file_methods[] = {
  { .ml_name = "read",
    .ml_meth = file_read,
    .ml_flags = METH_VARARGS,
    .ml_doc = "Reads a chunk of data from the file."
  },
  { .ml_name = "close",
    .ml_meth = file_close,
    .ml_flags = METH_VARARGS,
    .ml_doc = "Closes the entry."
  },
};

PyTypeObject PyZzipFile_T = {
  .tp_name = "zziplib.Entry",
  .tp_basicsize = sizeof(PyZzipFile),
  .tp_alloc = PyType_GenericAlloc,
  .tp_dealloc = (destructor)file_dealloc,
  .tp_doc = "An object representing an entry in a Zip archive.",
  .tp_methods = file_methods,
  .tp_free = PyObject_Del,
};

void add_file_types(PyObject *m) {
  PyObject *t = &PyZzipFile_T;

  if (PyType_Ready(&PyZzipFile_T) < 0)
    return;

  Py_INCREF(t);
  PyModule_AddObject(m, "Entry", t);
}
