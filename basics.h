typedef uint64 uint64_t;
typedef int64 int64_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef struct
{
  unsigned char _0;
  unsigned char _1;
  unsigned char _2;
} int24<read=read_int24, optimize=false, size=3>;
int value_int24 (int24& ref)
{
  int _0 = ref._0;
  int _1 = ref._1;
  int _2 = ref._2;
  int combined =  _0 | (_1 << 8) | (_2 << 16);
  if (combined & 0x800000)
  {
    combined = combined | 0xFF000000;
  }
  return combined;
}
string read_int24 (int24& ref)
{
  string a;
  SPrintf (a, "%i", value_int24 (ref));
  return a;
}

typedef struct
{
  unsigned char _4;
  unsigned char _3;
  unsigned char _2;
  unsigned char _1;
  unsigned char _0;
} uint40_t_BE<read=read_uint40_t_BE, optimize=false, size=5>;
unsigned long value_uint40_t_BE (uint40_t_BE& ref)
{
  unsigned long _0 = ref._0;
  unsigned long _1 = ref._1;
  unsigned long _2 = ref._2;
  unsigned long _3 = ref._3;
  unsigned long _4 = ref._4;
  unsigned long combined =  _0 | (_1 << 8) | (_2 << 16) | (_3 << 24) | (_4 << 32);
  return combined;
}
string read_uint40_t_BE (uint40_t_BE& ref)
{
  string a;
  SPrintf (a, "%u", value_uint40_t_BE (ref));
  return a;
}

typedef struct
{
  BigEndian();
  uint32_t _;
  LittleEndian();
} uint32_t_BE<read=read_uint32_t_BE, optimize=false>;
string read_uint32_t_BE (uint32_t_BE& ref)
{
  string a;
  SPrintf (a, "%x", ref._);
  return a;
}
typedef struct
{
  BigEndian();
  uint16_t _;
  LittleEndian();
} uint16_t_BE<read=read_uint16_t_BE, optimize=false>;
string read_uint16_t_BE (uint16_t_BE& ref)
{
  string a;
  SPrintf (a, "%u", ref._);
  return a;
}

// stringref -------------------------------------------------------------------

typedef struct
{
  int offset;
  //local unsigned int actual_offset_ = offset + header.record_count * header.record_size + sizeof(header);
} stringref<read=stringrefread, optimize=false, size=4>;

string stringrefread (stringref& ref)
{
  int actual_offset = ref.offset + header.record_count * header.record_size + sizeof (header);
  return ReadString (actual_offset);
}

// bitmask ---------------------------------------------------------------------

typedef struct
{
  uint32_t data;
} bitmask<read=bitmaskread, optimize=false, size=4>;

string bitmaskread(bitmask& mask)
{
  string a;
  int i = 0;
  for (i = 0; i < 32; ++i)
  {
    SPrintf(a, "%s%c", a, (mask.data & (1<<i) ? '1' : '0');
  }
  return a;
}

// C2IVector --------------------------------------------------------------------

typedef struct
{
  int x;
  int y;
} C2IVector<read=C2IVectorRead, write=C2IVectorWrite, optimize=false>;

string C2IVectorRead (C2IVector& rec)
{
  string a;
  SPrintf (a, "(%i %i)\n", rec.x, rec.y);
  return a;
}
void C2IVectorWrite (C2IVector& rec, string s)
{
  SScanf (s, "(%i %i)", rec.x, rec.y);
}

// C2Vector --------------------------------------------------------------------

typedef struct
{
  float x;
  float y;
} C2Vector<read=C2VectorRead, write=C2VectorWrite, optimize=false>;

string C2VectorRead (C2Vector& rec)
{
  string a;
  SPrintf (a, "(%f %f)\n", rec.x, rec.y);
  return a;
}
void C2VectorWrite (C2Vector& rec, string s)
{
  SScanf (s, "(%f %f)", rec.x, rec.yz);
}

// C3Vector --------------------------------------------------------------------

typedef struct
{
  float x;
  float y;
  float z;
} C3Vector<read=C3VectorRead, write=C3VectorWrite, optimize=false>;

string C3VectorRead (C3Vector& rec)
{
  string a;
  SPrintf (a, "(%f %f %f)\n", rec.x, rec.y, rec.z);
  return a;
}
void C3VectorWrite (C3Vector& rec, string s)
{
  SScanf (s, "(%f %f %f)", rec.x, rec.y, rec.z);
}

typedef struct
{
  uint16_t x;
  uint16_t y;
  uint16_t z;
} C3sVector<read=C3sVectorRead, write=C3sVectorWrite, optimize=false>;

string C3sVectorRead (C3sVector& rec)
{
  string a;
  SPrintf (a, "(%u %u %u)\n", rec.x, rec.y, rec.z);
  return a;
}
void C3sVectorWrite (C3sVector& rec, string s)
{
  SScanf (s, "(%u %u %u)", rec.x, rec.y, rec.z);
}

// CAaBox --

typedef struct 
{
C3Vector lower;
C3Vector upper;
} CAaBox<read=CAaBoxRead, optimize=false>;
string CAaBoxRead (CAaBox& rec)
{
  string a;
  SPrintf (a, "[%s %s]\n", C3VectorRead (rec.lower), C3VectorRead (rec.upper));
  return a;
}

// C4Quaternion ----------------------------------------------------------------

typedef struct
{
  float x;
  float y;
  float z;
  float w;
} C4Quaternion<read=C4QuaternionRead, optimize=false>;

string C4QuaternionRead(C4Quaternion& rec)
{
  string a;
  SPrintf (a, "(%f %f %f %f)\n", rec.x, rec.y, rec.z, rec.w);
  return a;
}

// C4Plane ----------------------------------------------------------------

typedef struct
{
  C3Vector normal;
  float distance;
} C4Plane<read=C4PlaneRead, optimize=false>;

string C4PlaneRead(C4Plane& rec)
{
  string a;
  SPrintf (a, "(%s %f)\n", C3VectorRead (rec.normal), rec.distance);
  return a;
}

// C4Vector --------------------------------------------------------------------

typedef struct
{
  float x;
  float y;
  float z;
  float w;
} C4Vector<read=C4VectorRead, write=C4VectorWrite, optimize=false>;

string C4VectorRead (C4Vector& rec)
{
  string a;
  SPrintf (a, "(%f %f %f %f)\n", rec.x, rec.y, rec.z, rec.w);
  return a;
}
void C4VectorWrite (C4Vector& rec, string s)
{
  SScanf (s, "(%f %f %f %f)", rec.x, rec.y, rec.z, rec.w);
}

// C44Matrix --------------------------------------------------------------------

typedef struct
{
  C4Vector x;
  C4Vector y;
  C4Vector z;
  C4Vector w;
} C44Matrix<read=C44MatrixRead, write=C44MatrixWrite, optimize=false>;

string C44MatrixRead (C44Matrix& rec)
{
  string a;
  SPrintf (a, "(%s %s %s %s)\n", C4VectorRead (rec.x), C4VectorRead (rec.y), C4VectorRead (rec.z), C4VectorRead (rec.w));
  return a;
}
void C44MatrixWrite (C44Matrix& rec, string s)
{
  SScanf (s, "(%s %s %s %s)", C4VectorRead (rec.x), C4VectorRead (rec.y), C4VectorRead (rec.z), C4VectorRead (rec.w));
}

// CArgb ----------------------------------------------------------------

typedef struct
{
  unsigned char b;
  unsigned char g;
  unsigned char r;
  unsigned char a;
} CArgb<read=CArgbRead, optimize=false>;

string CArgbRead(CArgb& rec)
{
  string a;
  SPrintf (a, "(%f %f %f %f)\n", rec.r, rec.g, rec.b, rec.a);
  return a;
}

// Chunk based -----------------------------------------------------------------

typedef struct
{
  union
  {
    struct
    {
      char _0;
      char _1;
      char _2;
      char _3;
    } raw;
    unsigned int _;
  } _;
} CHUNK_MAGIC<read=readCHUNK_MAGIC, optimize=false, size=4>;

string readCHUNK_MAGIC(CHUNK_MAGIC& rec)
{
  string a;
  SPrintf (a, "%c%c%c%c", rec._.raw._3, rec._.raw._2, rec._.raw._1, rec._.raw._0);
  return a;
}

typedef struct
{
  CHUNK_MAGIC magic;
  unsigned int size;
} CHUNK_header <read=readCHUNK_header, optimize=false, size=8>;

string readCHUNK_header(CHUNK_header& rec)
{
  string a;
  SPrintf (a, "%s: 0x%x", readCHUNK_MAGIC(rec.magic), rec.size);
  return a;
}

typedef struct
{
  CHUNK_header header;
  local char _known = true;
  local unsigned int _count = header.size;
  local unsigned int _begin = FTell();
  chunk_contents (header);
  if ((_begin + header.size) != FTell())
  {
    char __UNDERREAD[(_begin + header.size) - FTell()];
  }
  //Assert (_begin + _count == FTell(), "bytes left after reading chunk!");
} CHUNK <read=readCHUNK, optimize=false>;

string readCHUNK(CHUNK& rec)
{
  string a;
  if (rec._known) SPrintf (a, "%s [%i]", readCHUNK_MAGIC(rec.header.magic), rec._count);
  else            SPrintf (a, "%s [%i] (unknown)", readCHUNK_MAGIC(rec.header.magic), rec._count);
  return a;
}

void chunks_via_chunk_contents (unsigned int size)
{
  local unsigned int end = FTell() + size;
  while (FTell() < end)
  {
    CHUNK chunk;
  }
}
void all_chunks_via_chunk_contents()
{
  chunks_via_chunk_contents (FileSize());
}

typedef struct
{
  stringref enUS;
  stringref koKR;
  stringref frFR;
  stringref deDE;
  stringref enCN;
  stringref enTW;
  stringref esES;
  stringref esMX;
  stringref ruRU;
  stringref itIT;
  stringref _unk11;
  stringref _unk12;
  stringref _unk13;
  stringref _unk14;
  stringref _unk15;
  stringref _unk16;
  uint32 flags;
} localized_stringref<read=show_localized_stringref, optimize=false>;

string show_localized_stringref(localized_stringref& rec)
{
  string x;
  int count = 0;
  count += rec.enUS.offset != 0;
  count += rec.koKR.offset != 0;
  count += rec.frFR.offset != 0;
  count += rec.deDE.offset != 0;
  count += rec.enCN.offset != 0;
  count += rec.enTW.offset != 0;
  count += rec.esES.offset != 0;
  count += rec.esMX.offset != 0;
  count += rec.ruRU.offset != 0;
  count += rec.itIT.offset != 0;
  count += rec._unk11.offset != 0;
  count += rec._unk12.offset != 0;
  count += rec._unk13.offset != 0;
  count += rec._unk14.offset != 0;
  count += rec._unk15.offset != 0;
  count += rec._unk16.offset != 0;

// 0xFF01FC 1111 1100
// 0xFF01FE 1111 1110      // << present, localized, unicode
// 0xFF01CC 1100 1100
// 0xFF01EE 1110 1110      // << present, localized, unicode, achievement check
// 0xFF01EC 1110 1100
//                 ^  value present
//

  SPrintf (x, "%s %s %i %s", (rec.flags & 2 ? "+" : "-"), (rec.flags == 0xFF01FC || rec.flags == 0xFF01FE ? "F" : (rec.flags == 0xFF01CC ? "C" : "????????")), count,  stringrefread (rec.enUS));
  return x;
}

