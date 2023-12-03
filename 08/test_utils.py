import json
from faker import Faker
import random

NS_IN_S = 1e9

def generate_dict(seed=42, size=10, bs_size=100):
    random.seed(seed)
    fake = Faker('en_US')
    d = {}
    for i in range(size, bs_size):
        r = random.randint(0, 1)
        for b in range(bs_size):
            if r:
                d[fake.name()] = random.randint(-2147483648, 2147483647)
            else:
                d[fake.name()] = fake.name()
    return d

def generate_str_dict(seed=42, size=10, bs_size=100):
    d = generate_dict(seed, size=size, bs_size=bs_size)
    return json.dumps(d)