#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <thread>

#include <node_api.h>
#include "pstcore.h"

using namespace std;

#define NAPI_CALL(env, call)                                               \
do {                                                                       \
  napi_status status = call;                                               \
  if (status != napi_ok) {                                                 \
	printf("status %d : ", status);                                        \
    napi_fatal_error(#call, NAPI_AUTO_LENGTH, "failed", NAPI_AUTO_LENGTH); \
  }                                                                        \
} while (0)

static thread::id NODE_THREAD;

typedef struct param_done_callback_context{
	napi_env env;
	napi_threadsafe_function callback;
	napi_ref callback_ref;
}param_done_callback_context;


extern "C" {
static void js_on_set_param_callback(napi_env env, napi_value js_callback, void *_ctx,
		void *args) {
	void **params = (void**)args;

	//printf("js_on_set_param_callback : %s : %s : %s\n", (char*)params[0], (char*)params[1], (char*)params[2]);

	napi_value nv_pst_name;
	NAPI_CALL(env, napi_create_string_utf8(env, (char*)params[0], -1, &nv_pst_name));
	napi_value nv_param;
	NAPI_CALL(env, napi_create_string_utf8(env, (char*)params[1], -1, &nv_param));
	napi_value nv_value;
	NAPI_CALL(env, napi_create_string_utf8(env, (char*)params[2], -1, &nv_value));

	napi_value argv_cb[] = { nv_pst_name, nv_param, nv_value };
	napi_value undefined;
	napi_value ret;
	NAPI_CALL(env, napi_get_undefined(env, &undefined));
	napi_status status = napi_call_function(env, undefined, js_callback, 3, argv_cb, &ret);
	if (status != napi_ok) {
		//printf("something wrong : %d\n", status);
	}

	free(params[0]);
	free(params[1]);
	free(params[2]);
	free(params);
}
}

static void on_set_param_callback(const char *pst_name, const char *param,
		const char *value, void *arg) {
	param_done_callback_context *context = (param_done_callback_context*)arg;

	size_t pst_name_len = strlen(pst_name);
	size_t param_len = strlen(param);
	size_t value_len = strlen(value);
	char *pst_name_copy = (char*)malloc(pst_name_len + 1);
	char *param_copy = (char*)malloc(param_len + 1);
	char *value_copy = (char*)malloc(value_len + 1);
	strcpy(pst_name_copy, pst_name);
	strcpy(param_copy, param);
	strcpy(value_copy, value);

	void **params = (void**)malloc(sizeof(void*)*3);
	params[0] = pst_name_copy;
	params[1] = param_copy;
	params[2] = value_copy;

	if(std::this_thread::get_id() == NODE_THREAD){
		napi_value callback;
		NAPI_CALL(env, napi_get_reference_value(context->env, context->callback_ref, &callback));
		js_on_set_param_callback(context->env, callback, NULL, (void*)params);
	}else{
		NAPI_CALL(env, napi_acquire_threadsafe_function(context->callback));
		NAPI_CALL(env,
				napi_call_threadsafe_function(context->callback, (void*)params,
						napi_tsfn_blocking));
	}

	return;
}

static napi_value napi_pstcore_init(napi_env env, napi_callback_info info) {
	size_t argc = 1;
	napi_value argv[1];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc != 1) {
		return NULL;
	}

	NODE_THREAD = std::this_thread::get_id();

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));

	if (argument_type == napi_string) {
		char buff[1024];
		size_t copied;

		NAPI_CALL(env,
				napi_get_value_string_utf8(env, argv[0], buff, sizeof(buff),
						&copied));
		pstcore_init(buff);
	}

	return NULL;
}

static napi_value napi_pstcore_add_set_param_done_callback(napi_env env,
		napi_callback_info info) {
	size_t argc = 2;
	napi_value argv[2];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc != 2) {
		return NULL;
	}

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));
	if (argument_type != napi_number) {
		return NULL;
	}
	NAPI_CALL(env, napi_typeof(env, argv[1], &argument_type));
	if (argument_type != napi_function) {
		return NULL;
	}

	PSTREAMER_T *pst = NULL;
	int64_t ptr;
	NAPI_CALL(env, napi_get_value_int64(env, argv[0], &ptr));
	pst = (PSTREAMER_T*) ptr;

	napi_value resource_name;
	NAPI_CALL(env,
			napi_create_string_utf8(env, "pstcore", NAPI_AUTO_LENGTH,
					&resource_name));

	param_done_callback_context *context = new param_done_callback_context();
	context->env = env;
    NAPI_CALL(env, napi_create_reference(env, argv[1], 1, &context->callback_ref));
	NAPI_CALL(env, //
			napi_create_threadsafe_function(
				env,
				argv[1],//func
				NULL,//async_resource
				resource_name,//async_resource_name
				0,//max_queue_size
				2,//initial_thread_count
				NULL,//thread_finalize_data
				NULL,//thread_finalize_cb
				(void*)0x0,//context
				js_on_set_param_callback,//call_js_cb
				&context->callback//result
			));

	PSTHOST_T *psthost = pstcore_get_psthost();
	psthost->add_set_param_done_callback(psthost, pst, on_set_param_callback, context);

	return NULL;
}

//callback style for cordova compatibility
static napi_value napi_pstcore_build_pstreamer(napi_env env,
		napi_callback_info info) {
	size_t argc = 3;
	napi_value argv[3];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc != 2) {
		return NULL;
	}

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));
	if (argument_type != napi_string) {
		return NULL;
	}
	NAPI_CALL(env, napi_typeof(env, argv[1], &argument_type));
	if (argument_type != napi_function) {
		return NULL;
	}

	char def[1024] = { };
	size_t copied;

	NAPI_CALL(env,
			napi_get_value_string_utf8(env, argv[0], def, sizeof(def),
					&copied));

	PSTREAMER_T *pst = pstcore_build_pstreamer(def);
	printf("pst=%p\n", pst);

	{//callback
		napi_value pst_nv;
		napi_create_int64(env, (uint64_t) pst, &pst_nv);
		napi_value argv_cb[] = { pst_nv };
		napi_value undefined;
		napi_value ret;
		NAPI_CALL(env, napi_get_undefined(env, &undefined));
		napi_status status = napi_call_function(env, undefined, argv[1], 1, argv_cb, &ret);
	}
	
	return NULL;
}

static napi_value napi_pstcore_start_pstreamer(napi_env env,
		napi_callback_info info) {
	size_t argc = 1;
	napi_value argv[1];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc == 0) {
		return NULL;
	}

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));

	if (argument_type == napi_number) {
		PSTREAMER_T *pst = NULL;
		int64_t ptr;
		NAPI_CALL(env, napi_get_value_int64(env, argv[0], &ptr));
		pst = (PSTREAMER_T*) ptr;

		pstcore_start_pstreamer(pst);
	}

	return NULL;
}

static napi_value napi_pstcore_stop_pstreamer(napi_env env,
		napi_callback_info info) {
	size_t argc = 1;
	napi_value argv[1];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc == 0) {
		return NULL;
	}

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));

	if (argument_type == napi_number) {
		PSTREAMER_T *pst = NULL;
		int64_t ptr;
		NAPI_CALL(env, napi_get_value_int64(env, argv[0], &ptr));
		pst = (PSTREAMER_T*) ptr;

		pstcore_stop_pstreamer(pst);
	}

	return NULL;
}

static napi_value napi_pstcore_destroy_pstreamer(napi_env env,
		napi_callback_info info) {
	size_t argc = 1;
	napi_value argv[1];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc == 0) {
		return NULL;
	}

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));

	if (argument_type == napi_number) {
		PSTREAMER_T *pst = NULL;
		int64_t ptr;
		NAPI_CALL(env, napi_get_value_int64(env, argv[0], &ptr));
		pst = (PSTREAMER_T*) ptr;

		pstcore_destroy_pstreamer(pst);
	}

	return NULL;
}

static napi_value napi_pstcore_enqueue(napi_env env, napi_callback_info info) {

	size_t argc = 2;
	napi_value argv[2];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc != 2) {
		return NULL;
	}

	napi_valuetype argument_type;

	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));
	if (argument_type != napi_number) {
		return NULL;
	}
	NAPI_CALL(env, napi_typeof(env, argv[1], &argument_type));
	if (argument_type != napi_object && argument_type != napi_null) {
		printf("not supported type %d\n", argument_type);
		return NULL;
	}

	PSTREAMER_T *pst = NULL;
	int64_t ptr;
	NAPI_CALL(env, napi_get_value_int64(env, argv[0], &ptr));
	pst = (PSTREAMER_T*) ptr;

	unsigned char *buff = NULL;
	size_t size = 0;

	if(argument_type == napi_object){

		bool is_buffer = false;
		bool is_arraybuffer = false;
		NAPI_CALL(env, napi_is_buffer(env, argv[1], &is_buffer));
		NAPI_CALL(env, napi_is_arraybuffer(env, argv[1], &is_arraybuffer));
		if (!is_buffer && !is_arraybuffer) {
			return NULL;
		}

		if (is_buffer) {
			napi_status status = napi_get_buffer_info(env, argv[1], (void**) &buff,
					&size);
		} else if (is_arraybuffer) {
			napi_status status = napi_get_arraybuffer_info(env, argv[1], (void**) &buff,
					&size);
		}
		
	}

    //printf("pst=%p buff=%p size=%d c=%s\n", pst, buff, size, buff);
    pstcore_enqueue(pst, buff, (int)size);

	return NULL;
}

void on_fill_buffer_done_callback(PSTREAMER_T *origin, void *arg){
	napi_threadsafe_function callback = (napi_threadsafe_function)arg;

	int size = 0;
	MEMBUFF_T _buff;
	origin->dequeue(origin, &_buff);
    //printf("on_fill_buffer_done_callback:%d %d %d\n", size, ((int*)_buff)[0], _buff[4]);
	if(_buff.data == NULL){
		NAPI_CALL(env, napi_acquire_threadsafe_function(callback));
		NAPI_CALL(env,
				napi_call_threadsafe_function(callback, NULL,
						napi_tsfn_blocking));
	}else{
		vector<uint8_t> *buff = new vector<uint8_t>(_buff.data, _buff.data + _buff.size);

		NAPI_CALL(env, napi_acquire_threadsafe_function(callback));
		NAPI_CALL(env,
				napi_call_threadsafe_function(callback, (void* )buff,
						napi_tsfn_blocking));
	}
}

extern "C" {
	static void js_on_fill_buffer_done_callback(napi_env env, napi_value js_callback, void *_ctx,
			void *_vec) {
		napi_value buff;
		if(_vec == NULL){
			napi_get_null(env, &buff);
		}else{
			vector<uint8_t> *vec = (vector<uint8_t>*)_vec;

			void *_buff = NULL;
			napi_create_buffer(env, vec->size(), &_buff, &buff);
			memcpy(_buff, vec->data(), vec->size());
			delete(vec);
		}
		napi_value argv_cb[] = { buff };
		napi_value undefined;
		napi_value ret;
		NAPI_CALL(env, napi_get_undefined(env, &undefined));
		NAPI_CALL(env,
				napi_call_function(env, undefined, js_callback, 1, argv_cb, &ret));
	}
}

static napi_value napi_pstcore_set_dequeue_callback(napi_env env, napi_callback_info info) {

	size_t argc = 2;
	napi_value argv[2];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc != 2) {
		return NULL;
	}

	napi_valuetype argument_type;

	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));
	if (argument_type != napi_number) {
		return NULL;
	}
	NAPI_CALL(env, napi_typeof(env, argv[1], &argument_type));
	if (argument_type != napi_function) {
		return NULL;
	}

	PSTREAMER_T *pst = NULL;
	int64_t ptr;
	NAPI_CALL(env, napi_get_value_int64(env, argv[0], &ptr));
	pst = (PSTREAMER_T*) ptr;

	napi_value resource_name;
	NAPI_CALL(env,
			napi_create_string_utf8(env, "pstcore", NAPI_AUTO_LENGTH,
					&resource_name));

	napi_threadsafe_function callback = NULL;
	NAPI_CALL(env, //
			napi_create_threadsafe_function(env, argv[1],//func
			NULL,//async_resource
			resource_name,//async_resource_name
			0,//max_queue_size
			2,//initial_thread_count
			NULL,//thread_finalize_data
			NULL,//thread_finalize_cb
			(void*)0x0,//context
			js_on_fill_buffer_done_callback,//call_js_cb
			&callback//result
			));

	pstcore_set_fill_buffer_done_callback(pst, on_fill_buffer_done_callback, callback);

	return NULL;
}

static napi_value napi_pstcore_set_param(napi_env env,
		napi_callback_info info) {
	size_t argc = 4;
	napi_value argv[4];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc != 4) {
		return NULL;
	}

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));

	if (argument_type == napi_number) {
		PSTREAMER_T *pst = NULL;
		int64_t ptr;
		NAPI_CALL(env, napi_get_value_int64(env, argv[0], &ptr));
		pst = (PSTREAMER_T*) ptr;

		char pst_name[1024] = { };
		char param[1024] = { };
		char *value = NULL;
		size_t copied;

		NAPI_CALL(env,
				napi_get_value_string_utf8(env, argv[1], pst_name,
						sizeof(pst_name), &copied));
		NAPI_CALL(env,
				napi_get_value_string_utf8(env, argv[2], param, sizeof(param),
						&copied));

		size_t value_len = 0;
		NAPI_CALL(env,
		napi_get_value_string_utf8(env, argv[3], NULL, 0,
		&value_len));
		//printf("napi_pstcore_set_param : %d\n", value_len);
		value = (char*)malloc(value_len + 1);
		NAPI_CALL(env,
		napi_get_value_string_utf8(env, argv[3], value, value_len + 1,
		&copied));

		pstcore_set_param(pst, pst_name, param, value);

		free(value);

		return NULL;
	}

	return NULL;
}

static napi_value napi_pstcore_get_param(napi_env env,
		napi_callback_info info) {
	size_t argc = 3;
	napi_value argv[3];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc != 3) {
		return NULL;
	}

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));

	if (argument_type == napi_number) {
		PSTREAMER_T *pst = NULL;
		int64_t ptr;
		NAPI_CALL(env, napi_get_value_int64(env, argv[0], &ptr));
		pst = (PSTREAMER_T*) ptr;

		char pst_name[1024] = { };
		char param[1024] = { };
		char value[1024] = { };
		size_t copied;

		NAPI_CALL(env,
				napi_get_value_string_utf8(env, argv[1], pst_name,
						sizeof(pst_name), &copied));
		NAPI_CALL(env,
				napi_get_value_string_utf8(env, argv[2], param, sizeof(param),
						&copied));

		pstcore_get_param(pst, pst_name, param, value, sizeof(value));
		value[sizeof(value) - 1] = '\0'; //fale safe

		napi_value ret;
		NAPI_CALL(env, napi_create_string_utf8(env, value, -1, &ret));
		return ret;
	}

	return NULL;
}

static napi_value napi_pstcore_poll_events(napi_env env,
		napi_callback_info info) {

	pstcore_poll_events();

	return NULL;
}

typedef struct log_callback_context{
	napi_env env;
	napi_threadsafe_function callback;
	napi_ref callback_ref;
}log_callback_context;

typedef struct log_callback_data{
	int level;
	string tag;
	string msg;
}log_callback_data;
extern "C" {
static void js_on_log_callback(napi_env env, napi_value js_callback, void *_ctx,
		void *_data) {
	log_callback_data *data = (log_callback_data*) _data;

	napi_value nv_level;
	NAPI_CALL(env, napi_create_int32(env, data->level, &nv_level));

	napi_value nv_tag;
	NAPI_CALL(env, napi_create_string_utf8(env, data->tag.c_str(), -1, &nv_tag));

	napi_value nv_msg;
	NAPI_CALL(env, napi_create_string_utf8(env, data->msg.c_str(), -1, &nv_msg));

	napi_value argv_cb[] = { nv_level, nv_tag, nv_msg };
	napi_value undefined;
	napi_value ret;
	NAPI_CALL(env, napi_get_undefined(env, &undefined));
	napi_status status = napi_call_function(env, undefined, js_callback, 3, argv_cb, &ret);
	if (status != napi_ok) {
		//printf("something wrong %d : ", status);
	}

	delete data;
}
}

static void on_log_callback(int level, const char *tag, const char *msg, void *arg) {
	log_callback_context *context = (log_callback_context*)arg;

	log_callback_data *data = new log_callback_data();
	data->level = level;
	data->tag = tag;
	data->msg = msg;

	if(std::this_thread::get_id() == NODE_THREAD){
		napi_value callback;
		NAPI_CALL(env, napi_get_reference_value(context->env, context->callback_ref, &callback));
		js_on_log_callback(context->env, callback, NULL, (void*)data);
	}else{
		NAPI_CALL(env, napi_acquire_threadsafe_function(context->callback));
		NAPI_CALL(env,
				napi_call_threadsafe_function(context->callback, (void*)data,
						napi_tsfn_blocking));
	}

	return;
}

static napi_value napi_pstcore_add_log_callback(napi_env env,
		napi_callback_info info) {
	size_t argc = 2;
	napi_value argv[2];
	NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, NULL, NULL));
	if (argc != 1) {
		return NULL;
	}

	napi_valuetype argument_type;
	NAPI_CALL(env, napi_typeof(env, argv[0], &argument_type));
	if (argument_type != napi_function) {
		return NULL;
	}

	napi_value resource_name;
	NAPI_CALL(env,
			napi_create_string_utf8(env, "pstcore", NAPI_AUTO_LENGTH,
					&resource_name));

	log_callback_context *context = new log_callback_context();
	context->env = env;
    NAPI_CALL(env, napi_create_reference(env, argv[0], 1, &context->callback_ref));
	NAPI_CALL(env, //
			napi_create_threadsafe_function(
				env,
				argv[0],//func
				NULL,//async_resource
				resource_name,//async_resource_name
				0,//max_queue_size
				2,//initial_thread_count
				NULL,//thread_finalize_data
				NULL,//thread_finalize_cb
				(void*)0x0,//context
				js_on_log_callback,//call_js_cb
				&context->callback//result
			));

	PSTHOST_T *psthost = pstcore_get_psthost();
	psthost->add_log_callback(psthost, on_log_callback, context);

	return NULL;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value Init(napi_env env, napi_value exports) {
	napi_status status;
	napi_property_descriptor desc[] = {
		DECLARE_NAPI_METHOD("pstcore_init", napi_pstcore_init),
		DECLARE_NAPI_METHOD("pstcore_build_pstreamer", napi_pstcore_build_pstreamer),
		DECLARE_NAPI_METHOD("pstcore_start_pstreamer", napi_pstcore_start_pstreamer),
		DECLARE_NAPI_METHOD("pstcore_stop_pstreamer", napi_pstcore_stop_pstreamer),
		DECLARE_NAPI_METHOD("pstcore_destroy_pstreamer", napi_pstcore_destroy_pstreamer),
		DECLARE_NAPI_METHOD("pstcore_enqueue", napi_pstcore_enqueue),
		DECLARE_NAPI_METHOD("pstcore_set_dequeue_callback", napi_pstcore_set_dequeue_callback),
		DECLARE_NAPI_METHOD("pstcore_set_param", napi_pstcore_set_param),
		DECLARE_NAPI_METHOD("pstcore_get_param", napi_pstcore_get_param),
		DECLARE_NAPI_METHOD("pstcore_add_set_param_done_callback", napi_pstcore_add_set_param_done_callback),
		DECLARE_NAPI_METHOD("pstcore_poll_events", napi_pstcore_poll_events),
		DECLARE_NAPI_METHOD("pstcore_add_log_callback", napi_pstcore_add_log_callback),
	};
	status = napi_define_properties(env, exports,
			sizeof(desc) / sizeof(desc[0]), desc);
	assert(status == napi_ok);
	return exports;
}

NAPI_MODULE(pstcore, Init)
