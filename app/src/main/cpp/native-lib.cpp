#include <jni.h>
#include <string>
#include <stdlib.h>
#include <android/log.h>

#define LOGOPEN

#ifdef LOGOPEN
#define LOG_TAG "AqCxBoM"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define LOGE(...)
#define LOGD(...)
#define LOGW(...)
#define LOGI(...)
#endif

#define NULL 0

jstring stringFromJNI(JNIEnv* env, jobject /* this */)
{
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
    return env->NewStringUTF("Hello World!");
}

static int registerNativeMethods(JNIEnv *env, const char *className,
                                 JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static const char *gClassName = "aqcxbom/jnitemplatenew/MainActivity";
static JNINativeMethod gMethods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *)stringFromJNI},
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnLoad in");
    JNIEnv *env = NULL;
    jint result = -1;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    if (registerNativeMethods(env, gClassName, gMethods,
                              sizeof(gMethods) / sizeof(gMethods[0])) == JNI_FALSE) {
        return -1;
    }
    LOGI("So load success");
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    return;
}