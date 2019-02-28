package play.xplay;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, Runnable, SeekBar.OnSeekBarChangeListener {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public native double PlayPos();

    public native void Seek(double pos);

    private Button bt;
    private SeekBar sb;
    private Thread th;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt = findViewById(R.id.bt);
        sb = findViewById(R.id.sb);
        bt.setOnClickListener(this);
        sb.setOnSeekBarChangeListener(this);
        sb.setMax(1000);
        //启动播放进度线程
        th = new Thread(this);
        th.start();
    }


    @Override
    public void onClick(View v) {
        Intent intent = new Intent(this, OpenUrlActivity.class);
        startActivity(intent);
    }


    //播放进度显示
    @Override
    public void run() {
        for (; ; ) {
            sb.setProgress((int) (PlayPos() * 1000));
            try {
                Thread.sleep(40);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        Seek((double) seekBar.getProgress() / (double) sb.getMax());
    }
}
