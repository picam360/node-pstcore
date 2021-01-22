#pragma once


#ifdef __cplusplus

extern "C" {

#endif


int popen2(const char *def, int *fd_r, int *fd_w);


#ifdef __cplusplus

}

#endif
