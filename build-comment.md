1. mdflib: disable use pre-compile-header
2. mdflib: disable global program optimize
3. mdflib: property - c/c++ - general: additional include dir
4. mdflib: dsiable sdl check (fix c4996 error)
5. mdflibrary: additional lib dir: zlib.lib dependency (link - general)
6. mdflibrary: additional lib dir: libexpat.lib dependency (link - general)
7. mdflibrary: input - additional dependency (zlib.lib;libexpat.lib)
8. copy zlib.dll and libexpat.dll to runtime env