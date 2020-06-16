#macro endian_swap(SOURCE,SIZE)
{
	#local DKusize start;
	#local DKusize end;
	end = SIZE - 1;
	while (start < end)
	{
		U8 value = SOURCE[start];
		SOURCE[start] = SOURCE[end];
		SOURCE[end] = value;
		++start;
		--end;
	}
}

#if (DARK_ENDIAN == DARK_LITTLE_ENDIAN)
	#define endian_swapToLE(SOURCE,SIZE)
	#define endian_swapToBE(SOURCE,SIZE) endian_swap(SOURCE,SIZE);
#elif (DARK_ENDIAN == DARK_BIG_ENDIAN)
	#define endian_swapToLE(SOURCE,SIZE) endian_swap(SOURCE,SIZE);
	#define endian_swapToBE(SOURCE,SIZE)
#endif
