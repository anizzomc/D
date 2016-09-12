#ifndef _LOG_H_
#define _LOG_H_

#include <stdlib.h>
#include <stdio.h>

#define ERROR(x) fprintf(stderr, "[*]Error: \"%s\" in %s:%d\n", x, __FILE__, __LINE__) 


#endif