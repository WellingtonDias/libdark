#macro endian_swap(SOURCE,SIZE)
{
	#local DKusize start;
	#local DKusize end;
	end = SIZE - 1;
	while (start < end)
	{
		#local DKu8 value;
		value = SOURCE[start];
		SOURCE[start] = SOURCE[end];
		SOURCE[end] = value;
		++start;
		--end;
	};
};
