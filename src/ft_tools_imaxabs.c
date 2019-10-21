#include <stdint.h>

uintmax_t	ft_imaxabs(intmax_t n)
{
	return ((uintmax_t)(n < 0 ? -n : n));
}
