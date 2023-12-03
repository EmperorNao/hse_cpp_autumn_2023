import time

import json
import cjson
import ujson

from test_utils import generate_dict, generate_str_dict, NS_IN_S


def test_empty_loads():
    json_str = '{}'
    json_loads = json.loads(json_str)
    cjson_loads = cjson.loads(json_str)
    assert json_loads == cjson_loads

def test_loads():
    json_str = '{"a": "b", "": "c", "1"   \n:\n 1,\n\n "11"\n: "2"\n, "f": "e", "a": "c"}'
    json_loads = json.loads(json_str)
    cjson_loads = cjson.loads(json_str)
    assert json_loads == cjson_loads

def test_perf_loads():

    print("\n\ntest_perf_loads\nGENERATING BIG JSON. MAY TAKE TIME (few minutes)\n\n")
    big_json_str = generate_str_dict(42)

    json_start = time.perf_counter_ns()
    json_loads = json.loads(big_json_str)
    json_end = time.perf_counter_ns()
    print(f"JSON perf: {(json_end - json_start) / NS_IN_S}")

    cjson_start = time.perf_counter_ns()
    cjson_loads = cjson.loads(big_json_str)
    cjson_end = time.perf_counter_ns()
    print(f"CJSON perf: {(cjson_end - cjson_start) / NS_IN_S}")

    ujson_start = time.perf_counter_ns()
    ujson_loads = ujson.loads(big_json_str)
    ujson_end = time.perf_counter_ns()
    print(f"UJSON perf: {(ujson_end - ujson_start) / NS_IN_S}")
    assert json_loads == cjson_loads == ujson_loads


def test_empty_dumps():
    json_dict = {}
    json_dump = json.dumps(json_dict)
    cjson_dumps = cjson.dumps(json_dict)
    assert json_dump == cjson_dumps

def test_dumps():
    json_dict = {"a": "a", "b": 2, "c": 3, "d": 4}
    json_dump = json.dumps(json_dict)
    cjson_dumps = cjson.dumps(json_dict)
    assert json_dump == cjson_dumps

def test_perf_dumps():

    print("\n\ntest_perf_dumps\nGENERATING BIG JSON. MAY TAKE TIME (few minutes)\n\n")
    big_json = generate_dict(42)

    json_start = time.perf_counter_ns()
    json_dumps = json.dumps(big_json)
    json_end = time.perf_counter_ns()
    print(f"JSON perf: {(json_end - json_start) / NS_IN_S}")

    cjson_start = time.perf_counter_ns()
    cjson_dumps = cjson.dumps(big_json)
    cjson_end = time.perf_counter_ns()
    print(f"CJSON perf: {(cjson_end - cjson_start) / NS_IN_S}")

    ujson_start = time.perf_counter_ns()
    ujson_dumps = ujson.dumps(big_json)
    ujson_end = time.perf_counter_ns()
    print(f"UJSON perf: {(ujson_end - ujson_start) / NS_IN_S}")

    # ujson dumps format a little differs from json and cjson
    assert json_dumps == cjson_dumps