This is a crappy ctypes-based wrapper around the X86 RDTSC instruction to get cycle timers.

It will only work on x86-64 systems and probably requires GCC to install. Caveat emptor.

[![CircleCI](https://circleci.com/gh/Roguelazer/rdtsc.svg?style=svg)](https://circleci.com/gh/Roguelazer/rdtsc)

Usage
=====

```python
import time
import rdtsc

start = rdtsc.get_cycles()
# do stuff
time.sleep(5)
end = rdtsc.get_cycles()
frequency = rdtsc.get_cpu_frequency()

print((end - start)/(frequency * 10 ** 6))
```
