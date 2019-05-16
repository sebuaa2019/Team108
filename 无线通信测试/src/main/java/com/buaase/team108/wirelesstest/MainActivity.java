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
    private TextView textView1;
    private TextInputLayout textInputLayout1;
    public static Handler handler;
    private tcp tcpThread;

    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button1=findViewById(R.id.button1);
        textInputLayout1=findViewById(R.id.input1);
        textView1=findViewById(R.id.textView1);
        button1.setEnabled(false);
        tcpThread = new tcp(this);
        tcpThread.start();
        handler=new Handler(){
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what){
                    case tcp.MESSAGE_RECEIVE:
                        textView1.setText((String)msg.obj);
                    case tcp.MESSAGE_TCPREADY:
                        Toast.makeText(MainActivity.this,"connected！", Toast.LENGTH_SHORT).show();;
                        button1.setEnabled(true);
                }
            }
        };

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str=textInputLayout1.getEditText().getText().toString();
                Log.d("Test", "send msg:" + str);
//                Message msMessage = new Message();
//                msMessage.arg1 = tcp.MESSAGE_SEND;
//                Looper.handler.sendMessage(msMessage);
                tcpThread.handler.obtainMessage(tcp.MESSAGE_SEND,str).sendToTarget();
            }
        });

    }



    @Override
    protected void onResume(){
        super.onResume();
    }

    @Override
    protected void onDestroy() {
        try {
            tcpThread.closeSocket();
        } catch (IOException e) {
            e.printStackTrace();
        }
        super.onDestroy();
    }
}
