#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "awtk-jni.h"

#if 1
struct _object_t;
typedef struct _object_t object_t;

typedef int (*object_sum_t)(object_t* o, int a, int b);
typedef void (*object_destroy_t)(object_t* o);

typedef struct _object_t {
  object_sum_t sum;
  object_destroy_t destroy;
} object_t;

static int object_sum(object_t* o, int a, int b) {
  return a + b;
}

static void object_destroy(object_t* o) {
  printf("free:%p\n", o);
}

object_t* object_create(void) {
  object_t* o = (object_t*)malloc(sizeof(object_t));
  o->sum = object_sum;
  o->destroy = object_destroy;

  return o;
}

JNIEXPORT jlong JNICALL Java_HelloWorld_create(JNIEnv* env) {
  jlong ret = reinterpret_cast<jlong>(object_create());
  printf("ret=%lu\n", ret);

  return ret;
}

JNIEXPORT int JNICALL Java_HelloWorld_sum(JNIEnv* env, jlong obj, jint a, jint b) {
  printf("sum obj=%lu\n", obj);
  return object_sum(reinterpret_cast<object_t*>(obj), a, b);
}

JNIEXPORT void JNICALL Java_HelloWorld_destroy(JNIEnv* env, jlong obj) {
  return object_destroy(reinterpret_cast<object_t*>(obj));
}

#endif
JNIEXPORT void JNICALL Java_HelloWorld_print(JNIEnv* env, jobject obj) {
  printf("Hello World!\n");
  return;
}

JNIEXPORT void JNICALL Java_Widget_print(JNIEnv* env, jobject obj) {
  printf("Hello Widget!\n");
  return;
}

JNIEXPORT int JNICALL Java_HelloWorld_get_1ok(JNIEnv* env) {
  return 1;
}
