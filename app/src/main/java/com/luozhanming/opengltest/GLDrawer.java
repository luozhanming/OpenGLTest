package com.luozhanming.opengltest;

public class GLDrawer {

    static {
        System.loadLibrary("opengl3jni-lib");
    }

    public native int init(Object surface);

    public native int start();

    public native int draw();

    public native int destroy();
}
