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

void	usleep_ms_until(long long ms)
{
	long long	curr;

	curr = get_current_time_ms();
	while (get_current_time_ms() < curr + ms)
		;
}