#ifndef INC_08_CJSON_H
#define INC_08_CJSON_H

#include "cjson_impl.h"


static PyObject* cjson_loads(PyObject* self, PyObject* args) {
    const char* json_string;

    if (!PyArg_ParseTuple(args, "s", &json_string)) {
        printf("ERROR: Failed to parse string argument\n");
        return NULL;
    }

    cjson_dict cjson_dict = cjson_loads_impl(json_string);

    PyObject *dict = NULL;
    if (!(dict = PyDict_New())) {
        printf("ERROR: Failed to create Dict Object\n");
        return NULL;
    }

    PyObject *key = NULL;
    PyObject *value = NULL;
    for (int64_t index = 0; index < cjson_dict.n_elements; ++index) {
        if (!(key = Py_BuildValue("s#", cjson_dict.elements[index].key, cjson_dict.elements[index].key_size))) {
            printf("ERROR: Failed to build key\n");
            return NULL;
        }

        if (cjson_dict.elements[index].value_type == INT) {
            if (!(value = Py_BuildValue("i", atoi(cjson_dict.elements[index].value)))) {
                printf("ERROR: Failed to build integer value\n");
                return NULL;
            }
        }
        else {
            if (!(value = Py_BuildValue("s#", cjson_dict.elements[index].value, cjson_dict.elements[index].value_size))) {
                printf("ERROR: Failed to build string value\n");
                return NULL;
            }
        }

        if (PyDict_SetItem(dict, key, value) < 0) {
            printf("ERROR: Failed to set item\n");
            return NULL;
        }
    }

    if (cjson_dict.n_elements) {
        free_elements(cjson_dict.elements);
    }

    return dict;
}

PyObject* cjson_dumps(PyObject* self, PyObject* args) {
    PyObject* string;

    PyObject* dict;
    if (!PyArg_ParseTuple(args, "O", &dict)) {
        printf("ERROR: Failed to parse dict argument");
        return NULL;
    }

    char* str = cjson_dumps_impl(dict);
    PyObject* py_str = Py_BuildValue("s", str);
    if (str) {
        free(str);
    }

    return py_str;
}


#endif //INC_08_CJSON_H