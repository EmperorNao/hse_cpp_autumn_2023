from setuptools import setup, Extension

def main():
    setup(
        name="cjson",
        version="0.0.1",
        ext_modules=[Extension('cjson', ['cjson.c'])]
    )

if __name__ == "__main__":
    main()