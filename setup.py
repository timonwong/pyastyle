#!/usr/bin/env python
import os
import sys

from setuptools import setup, Extension
from setuptools.command.test import test as TestCommand

with open(os.path.join(os.path.dirname(__file__), 'README.rst')) as f:
    long_description = f.read()

astyle_sources = [
    'astyle/src/' + basename + '.cpp'
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
    include_dirs=['astyle/src'],
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
    version="1.1.2",

    description='Python wrapper extension for Artistic Style',
    long_description=long_description,

    author="Timon Wong",
    author_email="timon86.wang@gmail.com",
    url="https://github.com/timonwong/pyastyle",

    classifiers=[
        "Intended Audience :: Developers",
        "License :: OSI Approved :: GNU Lesser General Public License v3 (LGPLv3)",
        "Operating System :: MacOS :: MacOS X",
        "Operating System :: POSIX",
        "Operating System :: POSIX :: BSD",
        "Operating System :: POSIX :: Linux",
        "Operating System :: Microsoft :: Windows",
        "Programming Language :: Python",
        "Programming Language :: Python :: 2",
        "Programming Language :: Python :: 2.6",
        "Programming Language :: Python :: 2.7",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.2",
        "Programming Language :: Python :: 3.3",
        "Programming Language :: Python :: 3.4",
        "Programming Language :: Python :: Implementation :: CPython",
    ],

    zip_safe=False,
    ext_modules=[module],
    tests_require=['pytest'],
    cmdclass={'test': PyTest},
)
