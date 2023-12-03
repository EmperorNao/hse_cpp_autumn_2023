import json
from faker import Faker
import random

NS_IN_S = 1e9

def generate_dict(seed=42, size=100, bs_size=1000):
    random.seed(seed)
    fake = Faker('en_US')
    d = {}
    for i in range(size, bs_size):
        r = random.randint(0, 1)
        rint = random.randint(-2147483648, 2147483647)
        rname = fake.name()
        for b in range(bs_size):
            if r:
                d[fake.name()] = rint
            else:
                d[fake.name()] = rname
    return d

def generate_str_dict(seed=42, size=100, bs_size=1000):
    d = generate_dict(seed, size=size, bs_size=bs_size)
    return json.dumps(d)