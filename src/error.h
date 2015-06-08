#ifndef _ERROR_H_
#define _ERROR_H_

#include <errno.h>
void unix_error(char *msg);
void posix_error(int code, char *msg);
//void dns_error(char *msg);
//void app_error(char *msg);

#endif
