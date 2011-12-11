# -*- coding: utf-8 -*-
import os
from distutils.core import Extension, setup

version = '0.1'

cflags = [
    '-ansi',
    '-fvisibility=hidden',
    '-Wall',
    '-Wconversion',
    '-Wdeclaration-after-statement',
    '-g'
    ]

module = Extension('zziplib',
    libraries = ['zzip'],
    extra_compile_args = cflags + ['-D_XOPEN_SOURCE=600', '-DVERSION="%s"' % version],
    language = 'C',
    sources = [
        'src/module.c',
        'src/dir.c',
        'src/errors.c',
        'src/file.c',
        ],
    depends = [
        'src/pyzzip.h',
        ])

setup(name = 'zziplib',
      version = version,
      description = 'zziplib bindings for Python',
      author = "Rémy Oudompheng",
      author_email = "remy@archlinux.org",
      url = "http://github.com/remyoudompheng/python-zziplib",
      ext_modules = [module])

# vim: set ts=4 sw=4 et tw=0:
