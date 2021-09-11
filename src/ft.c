#include "philosophers.h"

#define ERR_MALLOC "Can't allocate memory"
#define ERR_MALLOC_SIZE "Invalid malloc size"

size_t		ft_strlen(const char *str)
{
    size_t	i;

    i = 0;
    if (!str)
        return (i);
    while (str[i])
        i++;
    return (i);
}



long long get_current_time_ms()
{
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

void	*ft_memalloc(size_t size)
{
	void	*a;

	if (size + 1 < size)
		handle_error(ERR_MALLOC_SIZE);
	a = malloc(size);
	if (!a)
		handle_error(ERR_MALLOC);
	ft_memset(a, 0, size);
	return (a);
}

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)destination;
	while (n > 0)
	{
		*(s++) = (unsigned char)c;
		n--;
	}
	return (destination);
}
