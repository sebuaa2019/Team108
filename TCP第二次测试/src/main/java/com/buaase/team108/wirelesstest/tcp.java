package com.buaase.team108.wirelesstest;

import android.annotation.SuppressLint;
import android.content.Context;
import android.icu.text.SymbolTable;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.Trace;
import android.util.Log;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

import static android.content.Context.WIFI_SERVICE;


public class tcp extends Thread{
    public static final int MESSAGE_TCPREADY = 0;
    public static final int MESSAGE_SEND = 1;
    public static final int MESSAGE_RECEIVE = 2;
    public static final int MESSAGE_TCPCLOSE = 3;
    public static final int MESSAGE_SENDFAIL = 4;
    private static final String ip = "192.168.43.6";
    private Context context;
    public Handler handler;
    private int rcvFlag;

    public tcp(Context _context){
        context = _context;

    }

    private String getMyip(){
        WifiManager wifiManager = (WifiManager)context.getSystemService(WIFI_SERVICE);
        WifiInfo wifiInfo = wifiManager.getConnectionInfo();
        int i = wifiInfo.getIpAddress();
        return (i & 0xFF )+"."+((i >> 8 ) & 0xFF)+"."+((i >> 16 ) & 0xFF)+"."+( i >> 24 & 0xFF) ;
    }

    public void startServerReplyListener(final BufferedReader reader) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    String response;
                    long startTime=System.currentTimeMillis();
                    while ((response = reader.readLine()) != null && System.currentTimeMillis()-startTime <400) {
                        Log.d("Test",response);
                        MainActivity.handler.obtainMessage(MESSAGE_RECEIVE,response).sendToTarget();
                        rcvFlag=1;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private void connectSend(String str){
        BufferedReader reader = null;
        BufferedWriter writer = null;
        Socket socket = null;
        while(socket==null || !socket.isConnected()){
            try {
                socket = new Socket(ip,9999);
                reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                socket.setTcpNoDelay(true);
            } catch (IOException e) {
                Log.d("Test","connection fail!");
            }
        }
        startServerReplyListener(reader);
        try{
            Log.d("Test","send");
            writer.write(str);
            //writer.write("\r\n");
            writer.flush();
        }catch (IOException e){
            e.printStackTrace();
        }
        try{
            reader.close();
            writer.close();
            socket.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    @SuppressLint("HandlerLeak")
    @Override
    public void run() {
        Looper.prepare();
        handler = new Handler(){
            public void handleMessage (Message msg) {
                switch (msg.what){
                    case(MESSAGE_SEND):
                        int counter=5;
                        rcvFlag=0;
                        while(counter>=0 && rcvFlag==0){
                            connectSend((String)msg.obj);
                            try {
                                Thread.sleep(500);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                            counter--;
                        }
                        if(rcvFlag==0){
                            MainActivity.handler.obtainMessage(MESSAGE_SENDFAIL).sendToTarget();
                        }
                }
            }
        };
        Looper.loop();
    }
}
