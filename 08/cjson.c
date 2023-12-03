#include <stdio.h>
#include <stdlib.h>

#include "cjson.h"
#include <Python.h>


struct PyMethodDef cjson_method_def[] = {
        {"loads", cjson_loads, METH_VARARGS, "Loads json dict from string"},
        {"dumps", cjson_dumps, METH_VARARGS, "Dumps json dict to string"},
        {NULL, NULL, 0, NULL}
};

struct PyModuleDef cjson_module_def = {
        PyModuleDef_HEAD_INIT,
        "cjson",
        "Module provides functions to work with json",
        -1,
        cjson_method_def
};


PyMODINIT_FUNC PyInit_cjson(void) {
    Py_Initialize();
    return PyModule_Create(&cjson_module_def);
}