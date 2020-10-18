typedef struct
{
	mtx_t* lock;
} Mutex;

typedef struct
{
	NullString message;
} Exception;

typedef struct
{
	Character*   pointer;
	UnsignedSize length;
	UnsignedSize capacity;
} StringData;

struct _String
{
	StringData data;
	Mutex      mutex;
	Exception  exception;
};

typedef struct
{
	Unsigned8*   pointer;
	UnsignedSize length;
	UnsignedSize capacity;
} BlobData;

struct _Blob
{
	Unsigned8    endian;
	UnsignedSize offset;
	BlobData     data;
	Mutex        mutex;
	Exception    exception;
};

typedef struct
{
	Undefined*   pointer;
	Undefined*   start;
	UnsignedSize offset;
	UnsignedSize length;
	UnsignedSize capacity;
} ListData;

struct _List
{
	CompareFunction function;
	ListData        data;
	Mutex           mutex;
	Exception       exception;
};

typedef struct
{
	Undefined key;
	Undefined value;
} MapPair;

typedef struct
{
	MapPair*     pointer;
	UnsignedSize length;
	UnsignedSize capacity;
} MapData;

struct _Map
{
	HashFunction    hashFunction;
	CompareFunction compareFunction;
	UnsignedSize    hashSize;
	UnsignedSize    length;
	MapData*        data;
	Mutex           mutex;
	Exception       exception;
};

struct _Container
{
	Pointer      pointer;
	UnsignedSize size;
	Boolean      lock;
};
