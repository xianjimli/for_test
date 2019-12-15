#include <Python.h>

static int _parse_voidp(PyObject* o, void** address) {
  *address = PyLong_AsVoidPtr(o);

  if (*address == NULL) {
    return 0;
  }

  return 1;
}

typedef struct _object_t {
  uint32_t value;
  PyObject* onchanged;
} object_t;

object_t* object_create(PyObject* onchanged) {
  object_t* o = (object_t*)calloc(1, sizeof(object_t));

  if(o != NULL) {
    Py_XINCREF(onchanged);
    o->onchanged = onchanged;
  }
   
  return o;
}

uint32_t object_value(object_t* o) {
  return o->value;
}

void object_set_value(object_t* o, uint32_t value) {
  PyObject* result = NULL;

  o->value = value;
  result = PyObject_CallFunction(o->onchanged, "i", value);

  if(result != NULL) {
    long res = PyLong_AsLong(result);
    Py_DECREF(result);
    printf("call return %ld\n", res);
  } else {
    printf("call return %p %p\n", o->onchanged, result);
  }

  return;
}

void object_destroy(object_t* o) {
  if(o != NULL) {
    Py_DECREF(o->onchanged);
    free(o);
  }
}

static PyObject* foo_object_create(PyObject* self, PyObject* args) {
  PyObject* func = NULL;

  if (PyArg_ParseTuple(args, "O", &func)) {
    if (!PyCallable_Check(func)) {
      PyErr_SetString(PyExc_TypeError, "parameter must be callable");
      return NULL;
    }
  } else {
    printf("not callable\n");
  }

  object_t* o = object_create(func);

  printf("create o=%p\n", o);
  return PyLong_FromVoidPtr(o);
}

static PyObject* foo_object_destroy(PyObject* self, PyObject* args) {
  object_t* o = NULL;
  if (!PyArg_ParseTuple(args, "O&", &_parse_voidp, &o)) {
    return NULL;
  }
  printf("destroy o=%p\n", o);
  object_destroy(o);

  return Py_BuildValue("I", 0);
}

static PyObject* foo_object_set_value(PyObject* self, PyObject* args) {
  int value = 0;
  object_t* o = NULL;

  if (!PyArg_ParseTuple(args, "O&i", &_parse_voidp, &o, &value)) {
    return NULL;
  }

  object_set_value(o, value);
  printf("set value o=%p\n", o);

  return Py_BuildValue("I", 0);
}

static PyObject* foo_object_get_value(PyObject* self, PyObject* args) {
  object_t* o = NULL;
  if (!PyArg_ParseTuple(args, "O&", &_parse_voidp, &o)) {
    return NULL;
  }

  printf("get value o=%p\n", o);

  return Py_BuildValue("I", o->value);
}

// module's method table
static PyMethodDef FooMethods[] = {{"create", foo_object_create, METH_VARARGS, ""},
                                   {"destroy", foo_object_destroy, METH_VARARGS, ""},
                                   {"set_value", foo_object_set_value, METH_VARARGS, ""},
                                   {"get_value", foo_object_get_value, METH_VARARGS, ""},
                                   {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC initfoo(void) {
  (void)Py_InitModule("foo", FooMethods);
}
