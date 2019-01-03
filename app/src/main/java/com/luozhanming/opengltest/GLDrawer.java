package com.luozhanming.opengltest;

import android.widget.TextView;

public class GLDrawer {

    public interface Callback{
        void onCallback(String str);
    }

    private Callback mCallback;

    public GLDrawer(Callback callback){
        this.mCallback = callback;
    }

    static {
        System.loadLibrary("opengl3jni-lib");
    }
    public native int init(Object surface);

    public native int start();

    public native int draw();

    public native int destroy();

    public void showText(String str){
        mCallback.onCallback(str);
    }

}
