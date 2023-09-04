template<typename T>
T clamp(T x, T xmin, T xmax)
{
	if(x < xmin)
	{
		return xmin;
	}
	if (x > xmax)
	{
		return xmax;
	}
	return x;
}