// Pointer
Pointer *pointer_encapsulate(RawPointer RAW_POINTER,UnsignedSize SIZE);
Pointer *pointer_allocate(UnsignedSize SIZE);
Pointer *pointer_zeroedAllocate(UnsignedSize SIZE);
void pointer_reallocate(Pointer *POINTER,UnsignedSize SIZE);
Pointer *pointer_deallocate(Pointer *POINTER);
