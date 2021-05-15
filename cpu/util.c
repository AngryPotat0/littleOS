#include"../include/type.h"
void memoryCopy(char *source, char *dest, int len)
{
    for(int i = 0;i < len;i++){
        *(dest + i) = *(source + i);
    }
}

void *memset( void *dest, uint8_t val, uint32_t count )
{
	uint8_t *temp = (uint8_t *) dest;

	for (; count != 0; count-- )
		*temp++ = val;
	return(dest);
}