package play.xplay;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class OpenUrlActivity extends AppCompatActivity implements View.OnClickListener {


    Button btOpenVideo;
    Button btOpenTv;
    EditText etVideoPath;
    EditText etTVUrl;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_open_url);

        btOpenVideo = findViewById(R.id.bt_open_video);
        btOpenTv = findViewById(R.id.bt_open_tv);
        etVideoPath = findViewById(R.id.et_video_path);
        etTVUrl = findViewById(R.id.et_tv_url);

        btOpenVideo.setOnClickListener(this);
        btOpenTv.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.bt_open_video:
                openVideo(etVideoPath);
                break;
            case R.id.bt_open_tv:
                openVideo(etTVUrl);
                break;
        }
    }

    private void openVideo(EditText editText){
        String path = editText.getText().toString().trim();
        Open(path);
        finish();
    }

    public native void Open(String path);
}
