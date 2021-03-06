//
// Created by Administrator on 2019/1/2.
//
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include <pthread.h>
#include <malloc.h>
/* Header for class com_luozhanming_opengltest_GLDrawer */

#ifndef _Included_com_luozhanming_opengltest_GLDrawer
#define _Included_com_luozhanming_opengltest_GLDrawer
#ifdef __cplusplus
extern "C" {
#endif

static const char *TAG = "glDrawer";

#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)


const char *shaderSrc = "";

/*
 * Class:     com_luozhanming_opengltest_GLDrawer
 * Method:    init
 * Signature: (Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_com_luozhanming_opengltest_GLDrawer_init
        (JNIEnv *env, jobject invoker, jobject surface) {
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay retrned error %d", eglGetError());
        return -1;
    }
    EGLint major, minor;
    if (!eglInitialize(display, &major, &minor)) {
        LOGE("eglInitialize returned %d", eglGetError());
        return -1;
    }
    EGLint attrib_list[] = {EGL_BUFFER_SIZE, 32,
                            EGL_ALPHA_SIZE, 8,
                            EGL_BLUE_SIZE, 8,
                            EGL_GREEN_SIZE, 8,
                            EGL_RED_SIZE, 8,
                            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                            EGL_NONE};
    EGLConfig config;
    EGLint num_config;
    if (!eglChooseConfig(display, attrib_list, &config, 1, &num_config)) {
        LOGE("eglChooseConfig() returned error %d", eglGetError());
        return -1;
    }
    EGLint attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context;
    if (!(context = eglCreateContext(display, config, EGL_NO_CONTEXT,
                                     attributes))) {
        LOGE("eglCreateContext() returned error %d", eglGetError());
        return -1;
    }
    EGLSurface eglSurface = NULL;
    EGLint format;
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID,
                            &format)) {
        LOGE("eglGetConfigAttrib() returned error %d", eglGetError());
        return surface;
    }
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);
    if (!(eglSurface = eglCreateWindowSurface(display, config, window, 0))) {
        LOGE("eglCreateWindowSurface() returned error %d", eglGetError());
    }
    if (!eglMakeCurrent(display, eglSurface, eglSurface, context)) {
        return -1;
    }
    GLuint vertexShader,fragmentShader;
    vertexShader = LoadShader(GL_VERTEX_SHADER,"");
    fragmentShader = LoadShader(GL_FRAGMENT_SHADER,"");
    GLuint program = LinkShaderAndProgram(vertexShader,fragmentShader);
    glUseProgram(program);


    return 0;
}

/*
 * Class:     com_luozhanming_opengltest_GLDrawer
 * Method:    start
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_luozhanming_opengltest_GLDrawer_start
        (JNIEnv *env, jobject invoker) {
    (*env)->NewGlobalRef(env, invoker);
    jclass clazz = (*env)->FindClass(env, "com/luozhanming/opengltest/GLDrawer");
    jmethodID methodId = (*env)->GetMethodID(env, clazz, "showText", "(Ljava/lang/String;)V");
    if (methodId == NULL) {
        return 1;
    }
    (*env)->CallVoidMethod(env, invoker, methodId,
                           (jstring) (*env)->NewStringUTF(env, "手动阀撒旦发射点手动阀"));
    return 0;

}

/*
 * Class:     com_luozhanming_opengltest_GLDrawer
 * Method:    draw
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_luozhanming_opengltest_GLDrawer_draw
        (JNIEnv *env, jobject invoker) {
    return 0;
}

/*
 * Class:     com_luozhanming_opengltest_GLDrawer
 * Method:    destroy
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_luozhanming_opengltest_GLDrawer_destroy
        (JNIEnv *env, jobject invoker) {
    return 0;
}


/**
 * 加载着色器
 * @param type shader type
 * @param shaderSrc shaderSrc
 * @return shader
 * */
GLuint LoadShader(GLenum type, const char *shaderSrc) {
    GLuint shader;
    GLuint complied;
    //Create the shader object
    shader = glCreateShader(type);

    if (shader == 0) {
        return 0;
    }

    //Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    //Complied the shader
    glCompileShader(shader);

    //Check the compiled status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &complied);

    if (!complied) {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            LOGE("Error compiling shader :\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}



GLuint LinkShaderAndProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint programObject = glCreateProgram();
    GLuint linked;

    if (programObject == 0) {
        return 0;
    }

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    glLinkProgram(programObject);
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if(!linked){
        GLint infoLen = 0;

        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            LOGE("Error compiling shader :\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteProgram(programObject);
        return 0;
    }
    return programObject;

}

#ifdef __cplusplus
}
#endif
#endif

