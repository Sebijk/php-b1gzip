# b1gZIP
b1gZIP is a module for PHP that allows extremely fast creation of ZIP archives. b1gZIP is based on the ZipArchive C++ library from Artpol Software and is completely free.

# Supported PHP versions
PHP version 7 or higher. For older php version look at git history 575ddfe

# Compile
Download the ZipArchive files from http://www.artpol-software.com/Download.aspx and compile this with the -fPIC -Option.
After successfully build compile b1gzip with:

```
g++ -o b1gzip.so -I[PHP_INCLUDE_DIR] -I[PHP_INCLUDE_DIR]/main -I[PHP_INCLUDE_DIR]/Zend -I[PHP_INCLUDE_DIR]/TSRM -I[ZIPARCHIVE_INCLUDE_DIR] -g -O2 b1gzip.cpp -L[ZIPARCHIVE_LIBZIPARCH.A-DIR] -lziparch -shared -export-dynamic -fPIC -Wl,-rpath,-avoid-version -DZEND_DEBUG=0 -DCOMPILE_DL_B1GZIP
```
