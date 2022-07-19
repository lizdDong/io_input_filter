
import os
from building import *

cwd = GetCurrentDir()

src = Split('''
io_input_filter.c
''')

if GetDepend(['IIF_EXAMPLE']):
    src += ['io_input_filter_example.c']

path = [cwd]

group = DefineGroup('io_input_filter', src, depend = ['PKG_USING_IO_INPUT_FILTER'], CPPPATH = path)

Return('group')
