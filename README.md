# Transaction Practices
## Build

```bash
$ git clone <repoUrl> --recursive
$ cd tx-practice
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
