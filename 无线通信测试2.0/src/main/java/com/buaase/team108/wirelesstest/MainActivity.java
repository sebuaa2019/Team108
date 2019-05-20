package com.buaase.team108.wirelesstest;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.os.Message;
import android.support.design.widget.TextInputLayout;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    private Button button1;
    private Button buttonStart;
    private Button buttonFinish;
    private Button buttonLeft;
    private Button buttonRight;
    private Button buttonUp;
    private Button buttonDown;
    private TextView textView1;
    private TextInputLayout textInputLayout1;
    public static Handler handler;
    private tcp tcpThread;

    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button1 = findViewById(R.id.button1);
        buttonStart = findViewById(R.id.start_map);
        buttonFinish = findViewById(R.id.finish);
        buttonLeft = findViewById(R.id.left);
        buttonRight = findViewById(R.id.right);
        buttonUp = findViewById(R.id.up);
        buttonDown = findViewById(R.id.down);

        textInputLayout1 = findViewById(R.id.input1);
        textView1 = findViewById(R.id.textView1);
        tcpThread = new tcp(this);
        tcpThread.start();
        handler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what) {
                    case tcp.MESSAGE_RECEIVE:{
                        textView1.setText((String) msg.obj);
                        activeButton();
                        break;
                    }
                    case tcp.MESSAGE_SENDFAIL:{
                        activeButton();
                        Toast.makeText(MainActivity.this,"发送失败，请重试",Toast.LENGTH_SHORT).show();
                        break;
                    }
                }
            }
        };

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = textInputLayout1.getEditText().getText().toString();
                tcpThread.handler.obtainMessage(tcp.MESSAGE_SEND, str).sendToTarget();
            }
        });

        buttonStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = "map_start";
                tcpThread.handler.obtainMessage(tcp.MESSAGE_SEND, str).sendToTarget();
                disableButton();
            }
        });

        buttonFinish.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = "map_finish";
                tcpThread.handler.obtainMessage(tcp.MESSAGE_SEND, str).sendToTarget();
                disableButton();
            }
        });

        buttonLeft.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = "move_left";
                tcpThread.handler.obtainMessage(tcp.MESSAGE_SEND, str).sendToTarget();
                disableButton();
            }
        });

        buttonRight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = "move_right";
                tcpThread.handler.obtainMessage(tcp.MESSAGE_SEND, str).sendToTarget();
                disableButton();
            }
        });

        buttonUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = "move_forward";
                tcpThread.handler.obtainMessage(tcp.MESSAGE_SEND, str).sendToTarget();
                disableButton();
            }
        });

        buttonDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = "move_backward";
                tcpThread.handler.obtainMessage(tcp.MESSAGE_SEND, str).sendToTarget();
                disableButton();
            }
        });

    }

    private void activeButton(){
        buttonStart.setEnabled(true);
        buttonFinish.setEnabled(true);
        buttonUp.setEnabled(true);
        buttonDown.setEnabled(true);
        buttonLeft.setEnabled(true);
        buttonRight.setEnabled(true);
    }

    private void disableButton(){
        buttonStart.setEnabled(false);
        buttonFinish.setEnabled(false);
        buttonUp.setEnabled(false);
        buttonDown.setEnabled(false);
        buttonLeft.setEnabled(false);
        buttonRight.setEnabled(false);
    }


    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}
