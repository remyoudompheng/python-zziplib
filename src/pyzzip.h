#ifndef PYTHON_ZZIP_H
#define PYTHON_ZZIP_H

#include <Python.h>
#include <zzip/lib.h>

typedef struct _PyZzipFile {
  PyObject_HEAD
  ZZIP_FILE *file;
} PyZzipFile;

typedef struct _PyZzipDir {
  PyObject_HEAD
  ZZIP_DIR *dir;
} PyZzipDir;

PyTypeObject PyZzipFile_T;
PyTypeObject PyZzipDir_T;

#endif /* PYTHON_ZZIP_H */
