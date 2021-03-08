#pragma once


#ifdef __cplusplus

extern "C" {

#endif

typedef void* PCPIPE_T;
int pcpipe_open(const char *def, PCPIPE_T *fd_r, PCPIPE_T *fd_w, PCPIPE_T *fd_exit);
int pcpipe_close(PCPIPE_T fd);
int pcpipe_read(PCPIPE_T fd, void* ptr, int size);
int pcpipe_write(PCPIPE_T fd, const void* ptr, int size);


#ifdef __cplusplus

}

#endif
