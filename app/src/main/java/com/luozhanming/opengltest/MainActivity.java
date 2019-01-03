package com.luozhanming.opengltest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    SurfaceView surfaceView;
    TextView textView;
    GLDrawer drawer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        surfaceView = findViewById(R.id.surfaceView);
        textView = findViewById(R.id.text);
        drawer = new GLDrawer(new GLDrawer.Callback() {
            @Override
            public void onCallback(String str) {
                textView.setText(str);
            }
        });
        surfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(final SurfaceHolder holder) {
                new Thread(){
                    @Override
                    public void run() {
                        Surface surface = holder.getSurface();
                        drawer.init(surface);
                    }
                }.start();
            }

            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {

            }
        });
        drawer.start();
    }



}
