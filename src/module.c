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

/* Module methods */
PyObject* pyzzip_opendir(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
  { .ml_name = "open",
    .ml_meth = pyzzip_opendir,
    .ml_flags = METH_VARARGS,
    .ml_doc = "open a Zip archive" },
  { NULL, NULL, 0, NULL }
};


#if PY_MAJOR_VERSION == 2
PUBLICSYM
PyMODINIT_FUNC
initzziplib(void) {
  PyObject *m;
  m = Py_InitModule("zziplib", module_methods);

  add_file_types(m);
  add_dir_types(m);
  add_error_types(m);
}
#else
static struct PyModuleDef module = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_name = "zziplib",
  .m_doc = "Module to open zip files with zziplib",
  .m_size = -1,
  .m_methods = module_methods,
};

PUBLICSYM
PyMODINIT_FUNC
PyInit_zziplib(void) {
  PyObject *m;
  m = PyModule_Create(&module);
  add_file_types(m);
  add_dir_types(m);
  add_error_types(m);
  return m;
}
#endif
