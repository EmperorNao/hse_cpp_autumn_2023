#ifndef INC_08_CJSON_IMPL_H
#define INC_08_CJSON_IMPL_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define PY_SSIZE_T_CLEAN
#include <Python.h>


// cjson types definition
typedef enum cjson_type {INT, STR} cjson_type;

typedef struct cjson_element {
    const char* key;
    int32_t key_size;
    void* value;
    int32_t value_size;
    cjson_type value_type;
} cjson_element;

typedef cjson_element* cjson_elements;
typedef struct cjson_dict {
    cjson_elements elements;
    uint32_t n_elements;
    uint32_t size;
} cjson_dict;
typedef bool (*predicate)(char);


// cjson function for working with cjson_dict
static int element_compare(const void* lhs, const void* rhs) {

    const cjson_element* l = lhs;
    const cjson_element* r = rhs;
    if (l->key_size != r->key_size) {
        return l->key_size - r->key_size;
    }

    int32_t idx = 0;
    while (idx < l->key_size && (*(l->key + idx) == *(r->key + idx))) {
        ++idx;
    }
    if (idx == l->key_size) {
        return 0;
    }
    return *(l->key + idx) - *(r->key + idx);

}

void dict_sort(cjson_dict* dict) {
    qsort(dict->elements, dict->n_elements, sizeof(cjson_element), element_compare);
}

bool is_elements_unique(cjson_dict* dict) {
    for (uint32_t index = 0; index + 1 < dict->n_elements; ++index) {
        if (!element_compare(&dict->elements[index], &dict->elements[index + 1])) {
            return false;
        }
    }
    return true;
}


// cjson functions for working with memory
cjson_elements create_elements(uint32_t* size) {
    *size = 10;
    return malloc((*size) * sizeof(cjson_element));
}

cjson_elements increase_elements(cjson_elements elements, uint32_t* old_size_ptr) {
    (*old_size_ptr) *= 2;
    return realloc(elements, (*old_size_ptr) * sizeof(cjson_element));
}

void free_elements(cjson_elements elements) {
    free(elements);
}

char* create_string(uint32_t* size) {
    *size = 128;
    return malloc((*size) * sizeof(char));
}

char* increase_string(char* str, uint32_t* old_size_ptr) {
    (*old_size_ptr) *= 2;
    return realloc(str, (*old_size_ptr) * sizeof(char));
}

char* increase_string_for_size(char* str, uint32_t new_size) {
    return realloc(str, (new_size) * sizeof(char));
}


// cjson functions for working with characters
bool is_end(char ch) {
    return ch == '\0';
}

bool is_not_end(char ch) {
    return ch != '\0';
}

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool is_not_digit(char ch) {
    return ch < '0' || ch > '9';
}

bool is_minus(char ch) {
    return ch == '-';
}

bool is_not_minus(char ch) {
    return ch != '-';
}

bool is_empty(char ch) {
    return ch <= ' ';
}

bool is_not_empty(char ch) {
    return ch > ' ';
}

bool is_quote(char ch) {
    return ch == '"';
}

bool is_not_quote(char ch) {
    return ch != '"';
}

bool is_right_curly_brace(char ch) {
    return ch == '}';
}

bool is_not_right_curly_brace(char ch) {
    return ch != '}';
}

bool is_left_curly_brace(char ch) {
    return ch == '{';
}

bool is_not_left_curly_brace(char ch) {
    return ch != '{';
}

bool is_colon(char ch) {
    return ch == ':';
}

bool is_not_colon(char ch) {
    return ch != ':';
}

bool is_comma(char ch) {
    return ch == ',';
}

bool is_not_comma(char ch) {
    return ch != ',';
}


void skip_chars(const char** str, predicate p) {
    const char* sym = *str;
    while (is_not_end(*sym) && p(*sym)) {
        ++sym;
    }
    *str = sym;
}


// cjson implementation of loads and dumps
cjson_dict cjson_loads_impl(const char* json_string) {
    const char* string = json_string;

    cjson_dict dict;
    dict.elements = NULL;
    dict.n_elements = 0;
    dict.size = 0;
    dict.elements = create_elements(&dict.size);

    skip_chars(&string, is_empty);
    if (is_not_left_curly_brace(*string)) {
        printf("ERROR: Failed during json string validation, json must starts with curly brace\n");
        return dict;
    }
    ++string;

    bool was_comma = false;

    while (is_not_end(*string)) {

        skip_chars(&string, is_empty);
        if (is_right_curly_brace(*string)) {
            ++string;
            break;
        }
        was_comma = false;

        if (is_not_quote(*string)) {
            printf("ERROR: Failed during json string validation, keys must be string surrounded by quote \n");
            free_elements(dict.elements);
            dict.n_elements = 0;
            return dict;
        }
        ++string;

        const char* key_start = string;
        skip_chars(&string, is_not_quote);

        if (is_not_quote(*string)) {
            printf("ERROR: Failed during json string validation, keys must be string surrounded by quote \n");
            free_elements(dict.elements);
            dict.n_elements = 0;
            return dict;
        }
        const char* key_end = string;
        ++string;

        skip_chars(&string, is_empty);
        if (is_not_colon(*string)) {
            printf("ERROR: Failed during json string validation, key and value must be separated by colon \n");
            free_elements(dict.elements);
            dict.n_elements = 0;
            return dict;
        }
        ++string;

        skip_chars(&string, is_empty);
        if (is_not_digit(*string) && is_not_minus(*string) && is_not_quote(*string)) {
            printf("ERROR: Failed during json string validation, value must be 1) str surrounded by quote or "
                   "2) number that can starts with minus '-'\n");
            free_elements(dict.elements);
            dict.n_elements = 0;
            return dict;
        }

        const char* value_start = 0;
        const char* value_end = 0;
        cjson_type value_type;

        if (is_digit(*string) || is_minus(*string)) {
            value_start = string;
            value_type = INT;

            if (is_minus(*string)) {
                ++string;
            }

            skip_chars(&string, is_digit);
            if (is_not_empty(*string) && is_not_right_curly_brace(*string) && is_not_comma(*string)) {
                printf("ERROR: Failed during json string validation, number value must be only with digits and "
                       "minus '-' in start\n");
                free_elements(dict.elements);
                dict.n_elements = 0;
                return dict;
            }
            value_end = string;
        }
        else {
            ++string;
            value_start = string;
            value_type = STR;

            skip_chars(&string, is_not_quote);
            if (is_not_quote(*string)) {
                printf("ERROR: Failed during json string validation, string value must be "
                       "surrounded by quote \n");
                free_elements(dict.elements);
                dict.n_elements = 0;
                return dict;
            }
            value_end = string;
            ++string;
        }

        if (dict.n_elements >= dict.size) {
            dict.elements = increase_elements(dict.elements, &dict.size);
        }

        dict.elements[dict.n_elements].key = key_start;
        dict.elements[dict.n_elements].key_size = key_end - key_start;
        dict.elements[dict.n_elements].value = (void*)value_start;
        dict.elements[dict.n_elements].value_size = value_end - value_start;
        dict.elements[dict.n_elements].value_type = value_type;

        ++dict.n_elements;

        skip_chars(&string, is_empty);
        if (is_comma(*string)) {
            ++string;
            was_comma = true;
            continue;
        }
        else if (is_right_curly_brace(*string)) {
            ++string;
            break;
        }
        printf("ERROR: Failed during json string validation, expected comma or right brace after value\n");
        free_elements(dict.elements);
        dict.n_elements = 0;
        return dict;

    }

    if (was_comma) {
        printf("ERROR: Failed during json string validation, find comma after last element \n");
        free_elements(dict.elements);
        dict.n_elements = 0;
        return dict;
    }

    skip_chars(&string, is_empty);
    if (is_not_end(*string)) {
        printf("ERROR: Failed during json string validation, find not empty characters after right curly brace\n");
        free_elements(dict.elements);
        dict.n_elements = 0;
        return dict;
    }

//    Validation for unique elements
//    dict_sort(&dict);
//    if (!is_elements_unique(&dict)) {
//        printf("ERROR: Failed during json string validation, find duplicate key\n");
//        free_elements(dict.elements);
//        dict.n_elements = 0;
//        return dict;
//    }

    return dict;
};


char* cjson_dumps_impl(PyObject* dict) {

    PyObject *key, *value;
    Py_ssize_t pos = 0;

    uint32_t str_size = 0;
    uint32_t str_len = 0;

    char* start = create_string(&str_size);

    start[0] = '{';
    str_len = 1;

    while (PyDict_Next(dict, &pos, &key, &value)) {

        if (str_len != 1) {
            if (str_len + 2 >= str_size) {
                start = increase_string(start, &str_size);
            }
            start[str_len] = ',';
            start[str_len + 1] = ' ';
            str_len += 2;
        }

        if (!PyUnicode_Check(key)) {
            printf("ERROR: Failed during json dumping, key is not string\n");
            free(start);
            return NULL;
        }

        char* key_str = PyUnicode_AsUTF8(key);
        size_t key_len = strlen(key_str);
        if (str_len + key_len + 4 >= str_size) {
            str_size = (str_len + key_len + 4) * 2;
            start = increase_string_for_size(start, str_size);
        }

        start[str_len] = '"';
        strcpy(start + str_len + 1, key_str);
        str_len += key_len + 1;
        start[str_len] = '"';
        start[str_len + 1] = ':';
        start[str_len + 2] = ' ';
        str_len += 3;

        if (PyLong_Check(value)) {
            long long_value = PyLong_AsLong(value);
            if (str_len + 11 >= str_size) {
                str_size = (str_len + 11) * 2;
                start = increase_string_for_size(start, str_size);
            }
            size_t long_value_len = sprintf(start + str_len, "%ld", long_value);
            str_len += long_value_len;
        }
        else if (PyUnicode_Check(value)) {
            char* value_str = PyUnicode_AsUTF8(value);
            size_t value_len = strlen(value_str);
            if (str_len + value_len + 2 >= str_size) {
                str_size = (str_len + value_len + 2) * 2;
                start = increase_string_for_size(start, str_size);
            }

            start[str_len] = '"';
            strcpy(start + str_len + 1, value_str);
            start[str_len + 1 + value_len] = '"';
            str_len += value_len + 2;
        }
        else {
            printf("ERROR: Failed during json dumping, value must be of type string or integer\n");
            free(start);
            return NULL;
        }
    }
    if (str_len + 2 > str_size) {
        str_size = str_len + 2;
        start = increase_string_for_size(start, str_size);
    }
    start[str_len] = '}';
    start[str_len + 1] = '\0';
    str_len += 2;

    return start;
}

#endif //INC_08_CJSON_IMPL_H