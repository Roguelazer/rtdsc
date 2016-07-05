import sys
import ctypes

import pkg_resources


version_info = (0, 2, 1)
__version__ = '.'.join(str(s) for s in version_info)
__author__ = 'James Brown <roguelazer@roguelazer.com>'
__license__ = 'ISC'


if sys.platform == 'darwin':
    sofile = 'rdtsc.dylib'
elif sys.platform == 'win32':
    sofile = 'rdtsc.dll'
else:
    sofile = 'rdtsc.so.1'

path = pkg_resources.resource_filename('rdtsc', sofile)
so = ctypes.CDLL(path, use_errno=True)

get_cycles = so.get_cycles
get_cycles.argtypes = []
get_cycles.restype = ctypes.c_ulonglong

get_cpu_frequency = so.get_cpu_frequency
get_cpu_frequency.argtypes = []
get_cpu_frequency.restype = ctypes.c_double
