package play.xplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback,GLSurfaceView.Renderer, View.OnClickListener {


    public XPlay(Context context) {
        this(context,null);
    }

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
        setRenderer(this);
        setOnClickListener(this);
    }



    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        InitView(holder.getSurface());
        //android 8.0需要设置

    }


    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }


    public native void InitView(Object surface);


    @Override
    public void onClick(View v) {
        Log.e("TaoTao", "  onClick  ");
        PlayOrPause();
    }

    public native void PlayOrPause();
}
