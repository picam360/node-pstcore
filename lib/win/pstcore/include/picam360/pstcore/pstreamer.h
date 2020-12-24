#pragma once

typedef char uuid_t[16];
#ifdef __cplusplus

extern "C" {

#endif

typedef struct _PSTREAMER_T PSTREAMER_T;
typedef void (*FILL_BUFFER_DONE_CALLBACK)(PSTREAMER_T *origin, void *arg);
struct _PSTREAMER_T {
	uuid_t uuid;
	char name[64];
	void (*release)(PSTREAMER_T *_this);

	PSTREAMER_T *pre_streamer;
	PSTREAMER_T *next_streamer;
	void (*start)(PSTREAMER_T *_this);
	void (*stop)(PSTREAMER_T *_this);
	void (*enqueue)(PSTREAMER_T *_this, unsigned char *buff, int size);
	void (*dequeue)(PSTREAMER_T *_this, unsigned char **out_buff,
			int *out_size);
	void (*set_fill_buffer_done_callback)(struct _PSTREAMER_T *_this,
			FILL_BUFFER_DONE_CALLBACK callback, void *arg);
};

typedef struct _PSTREAMER_FACTORY_T PSTREAMER_FACTORY_T;
struct _PSTREAMER_FACTORY_T {
	char name[64];
	void (*release)(PSTREAMER_FACTORY_T *_this);
	void (*create_pstreamer)(PSTREAMER_FACTORY_T *_this,
			PSTREAMER_T **streamer);
};

#ifdef __cplusplus

}

#endif
