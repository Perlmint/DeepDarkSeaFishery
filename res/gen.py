#-*- coding: utf-8 -*-
import argparse
from sys import stdin, stdout, version_info
from os.path import splitext, split, exists, relpath
from hashlib import md5
if version_info[0] == 2:
    from StringIO import StringIO
else:
    from io import StringIO

parser = argparse.ArgumentParser(description='Gen resource files for windows - visual studio')
parser.add_argument('output', type=str, help='output target.')
parser.add_argument('res_root', type=str, help='resources root')
parser.add_argument('target', choices=['msvc', 'path'])
args = parser.parse_args()

def write_to_file(path, content, encoding='utf-16'):
    content.seek(0)
    buf = content.read().encode(encoding)
    if not exists(path) or md5(open(path, 'rb').read()).hexdigest() != md5(buf).hexdigest():
        with open(path, 'wb') as o:
            o.write(buf)

outpath = args.output
outdir, outfilename = split(outpath)

idx = 101

res_map_by_ext = {}
res_map_id = {}
res_map_by_idx = {}
for res in stdin:
    id, path = res.strip().split(' ', 2)
    b, ext = splitext(path)
    ext = ext[1:].upper()
    res_map_by_ext.setdefault(ext, []).append((id, path))
    res_map_id[id] = idx
    res_map_by_idx[idx] = path
    idx += 1

res_ext_map_by_id = {}
for ext, items in res_map_by_ext.items():
    for res in items:
        res_ext_map_by_id.setdefault(idx, (ext, res[0]))

if args.target == 'msvc':
  header = StringIO()
  paths = StringIO()
  res_map_impl = StringIO()

  paths.write("""// Microsoft Visual C++ generated resource script.
//
#include "{0}.h"

#define APSTUDIO_READONLY_SYMBOLS
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 2 resource.
//
#include "winres.h"

/////////////////////////////////////////////////////////////////////////////
#undef APSTUDIO_READONLY_SYMBOLS

/////////////////////////////////////////////////////////////////////////////
// 한국어 resources

#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_KOR)
LANGUAGE LANG_KOREAN, SUBLANG_DEFAULT

#ifdef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// TEXTINCLUDE
//

1 TEXTINCLUDE
BEGIN
    "{0}.h\\0"
END

2 TEXTINCLUDE
BEGIN
    "#include ""winres.h""\\r\\n"
    "\\0"
END

3 TEXTINCLUDE
BEGIN
    "\\r\\n"
    "\\0"
END

#endif    // APSTUDIO_INVOKED

""".format(outfilename))

  header.write("""//{{NO_DEPENDENCIES}}
""")

  res_map_impl.write("""#include "{0}_map.h"

const std::unordered_map<unsigned int, res_info> res_map = {{""".format(outfilename))

  for ext, items in res_map_by_ext.items():
      paths.write("""/////////////////////////////////////////////////////////////////////////////
//
// {0}
//

""".format(ext))
      for res in items:
          paths.write("""{0}                {1}                     "{2}"\n""".format(res[0], ext, res[1]))
          header.write("#define {0} {1}\n".format(res[0], res_map_id[res[0]]))

  res_map_impl.write(", ".join(["{{{0}, {{\"{1}\", \"{2}\"}}}}".format(id, val[0], val[1]) for id, val in res_ext_map_by_id.items()]))
  res_map_impl.write("};\n")

  header.write("""
// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        {0}
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
""".format(idx))
  paths.write("""
#endif    // 한국어 resources
/////////////////////////////////////////////////////////////////////////////



#ifndef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 3 resource.
//


/////////////////////////////////////////////////////////////////////////////
#endif    // not APSTUDIO_INVOKED
""")

  write_to_file(outpath + '.rc', paths)
  write_to_file(outpath + '.h', header)

  res_map_header = StringIO()
  res_map_header.write("""#include <unordered_map>

struct res_info
{
  const char *const cat;
  const char *const path;
};
extern const std::unordered_map<unsigned int, res_info> res_map;
""")
  write_to_file(outpath + '_map.h', res_map_header, 'utf-8')
  write_to_file(outpath + '_map.cpp', res_map_impl, 'utf-8')
else:
  header = StringIO()
  for id, idx in res_map_id.items():
      header.write('constexpr const char * const {0} = "{1}";\n'.format(id, relpath(res_map_by_idx[idx], args.res_root)))
  write_to_file(outpath + '.h', header ,'utf-8')
