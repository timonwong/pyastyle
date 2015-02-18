#!/usr/bin/env python


from distutils.core import setup, Extension
import sys

astyle_sources = [
    './astyle/src/' + basename + '.cpp'
    for basename in 'ASBeautifier ASEnhancer ASFormatter ASResource astyle_main'.split()
]

sources = ['pyastyle.cc']
sources.extend(astyle_sources)

module = Extension(
    'pyastyle',
    define_macros=[('ASTYLE_LIB', None), ('ASTYLE_STATIC', None), ('ASTYLE_NO_EXPORTS', None)],
    include_dirs=['./astyle/src/'],
    sources=sources,
    extra_compile_args=['/EHsc'] if sys.platform == 'win32' else []
)

setup(
    name='pyastyle',
    version='1.1.0',
    ext_modules=[module]
)
