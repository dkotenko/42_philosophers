#include "philosophers.h"

void	usleep_ms(long long ms)
{
	usleep(ms * 1000);
}

long long	get_current_time_ms(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

long long	get_current_time_us(void)
{
	struct timeval	te;
	long long		useconds;

	gettimeofday(&te, NULL);
	useconds = te.tv_sec * 1000000LL + te.tv_usec;
	return (useconds);
}

void	usleep_ms_until(long long ms)
{
	long long	curr;

	curr = get_current_time_us();
	while (get_current_time_us() < curr + ms)
		;
}