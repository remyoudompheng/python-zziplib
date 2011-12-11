#include <Python.h>

#if __GNUC__ >= 4
#define PUBLICSYM __attribute__ ((visibility ("default")))
#define LOCALSYM  __attribute__ ((visibility ("hidden")))
#else
#define PUBLICSYM
#define LOCALSYM
#endif

/* Module initializers */
void add_file_types(PyObject *m);
void add_dir_types(PyObject *m);
void add_error_types(PyObject *m);

static PyMethodDef module_methods[] = {
  { NULL, NULL, 0, NULL }
};

PUBLICSYM
PyMODINIT_FUNC
initzziplib(void) {
  PyObject *m;
  m = Py_InitModule("zziplib", module_methods);

  add_file_types(m);
  add_dir_types(m);
  add_error_types(m);
}
