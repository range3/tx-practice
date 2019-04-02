# Basic 2 Phase Locking
## Build

```bash
$ git clone <repoUrl> --recursive
$ cd basic-two-phase-locking
$ mkdir build
$ cd build
$ cmake .. \
  -DCMAKE_BUILD_TYPE=Release
```

### Debug build example
``` bash
$ cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_VERBOSE_MAKEFILE=1
```
