package play.xplay;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class XPlay extends SurfaceView implements SurfaceHolder.Callback {


    public XPlay(Context context) {
        this(context,null);
    }

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
        initHolder();
    }

    private void initHolder() {
        getHolder().addCallback(this);
        setFocusable(true);
        setFocusableInTouchMode(true);
        this.setKeepScreenOn(true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        InitView(holder.getSurface());
    }


    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }


    public native void InitView(Object surface);
}
