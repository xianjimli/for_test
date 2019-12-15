from distutils.core import setup, Extension

foo = Extension('foo', sources = ['foo_module.c'])

setup (name = 'a demo extension module',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [foo])
