#ifndef LIBFT
# define LIBFT

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/*
 * ft.c
 */
int			is_integer(char *s, int n);
size_t		ft_strlen(const char *str);
long long	get_current_time_ms(void);
void		*ft_memset(void *destination, int c, size_t n);
void		*ft_memalloc(size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *ptr1, const void *ptr2, size_t num);

#endif