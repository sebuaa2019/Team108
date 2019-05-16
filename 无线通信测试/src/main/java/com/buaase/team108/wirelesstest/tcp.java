package com.buaase.team108.wirelesstest;

import android.annotation.SuppressLint;
import android.content.Context;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

import static android.content.Context.WIFI_SERVICE;


public class tcp extends Thread{
    public static final int MESSAGE_TCPREADY = 0;
    public static final int MESSAGE_SEND = 1;
    public static final int MESSAGE_RECEIVE = 2;
    private Context context;
    private Socket socket;
    public Handler handler;

    public tcp(Context _context){
        context = _context;

    }

    private String getMyip(){
        WifiManager wifiManager = (WifiManager)context.getSystemService(WIFI_SERVICE);
        WifiInfo wifiInfo = wifiManager.getConnectionInfo();
        int i = wifiInfo.getIpAddress();
        return (i & 0xFF )+"."+((i >> 8 ) & 0xFF)+"."+((i >> 16 ) & 0xFF)+"."+( i >> 24 & 0xFF) ;
    }

    private void send(String str) throws IOException{
        if(socket==null){
            return;
        }else {
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            out.write(str);
            out.flush();
            Log.d("Test", "CustomThread receive msg:" + str);
        }
    }

    public void closeSocket() throws IOException{
        socket.shutdownInput();
        socket.close();
    }

    @Override
    public void run() {
        String ip = "10.128.72.36";
        try {
            socket = new Socket(ip,9999);
        } catch (IOException e) {
            Log.d("Test","connection fail!");
        }
        MainActivity.handler.obtainMessage(MESSAGE_TCPREADY).sendToTarget();


        Looper.prepare();
        handler = new Handler(){
            public void handleMessage (Message msg) {
                switch (msg.what){
                    case(MESSAGE_SEND):
                        try {
                            send((String)msg.obj);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                }

            }
        };
        Looper.loop();
    }
}
