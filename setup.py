#!/usr/bin/env python
import sys

from setuptools import setup, Extension
from setuptools.command.test import test as TestCommand


astyle_sources = [
    './astyle/src/' + basename + '.cpp'
    for basename in ('ASBeautifier', 'ASEnhancer', 'ASFormatter', 'ASResource',
                     'astyle_main')
]

sources = ['pyastyle.cc']
sources.extend(astyle_sources)

if sys.platform != 'win32':
    extra_compile_args = '-O3 -W -Wall -fno-rtti -fno-exceptions'.split()
else:
    extra_compile_args = []

if sys.platform == 'win32':
    extra_compile_args.extend(['/EHsc'])


module = Extension(
    'pyastyle',
    define_macros=[('ASTYLE_LIB', 1), ('ASTYLE_STATIC', 1),
                   ('ASTYLE_NO_EXPORTS', 1)],
    include_dirs=['./astyle/src/'],
    sources=sources,
    extra_compile_args=extra_compile_args
)


class PyTest(TestCommand):
    user_options = [('pytest-args=', 'a', "Arguments to pass to py.test")]

    def initialize_options(self):
        TestCommand.initialize_options(self)
        self.pytest_args = []

    def finalize_options(self):
        TestCommand.finalize_options(self)
        self.test_args = []
        self.test_suite = True

    def run_tests(self):
        # import here, cause outside the eggs aren't loaded
        import pytest
        errno = pytest.main(self.pytest_args)
        sys.exit(errno)


setup(
    name="pyastyle",
    version="1.1.0",
    author="Timon Wong",
    author_email="timon86.wang@gmail.com",
    url="https://github.com/timonwong/pyastyle",
    zip_safe=False,
    ext_modules=[module],
    tests_require=['pytest'],
    cmdclass={'test': PyTest},
)
