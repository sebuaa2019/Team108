package com.buaase.team108.wirelesstest;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

public class Follow extends AppCompatActivity {

    public static Handler handler;
    private TextView textView;

    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_follow);

        textView = findViewById(R.id.textView2);
        textView.setText("");

        handler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what) {
                    case tcp.MESSAGE_SENDFAIL:{
                        Toast.makeText(Follow.this,"请重试",Toast.LENGTH_SHORT).show();
                        break;
                    }
                }
            }
        };

        String str = "follow";
        tcp.getinstance().handler.obtainMessage(tcp.MESSAGE_SEND, str).sendToTarget();


    }
}
