package com.example.ricardopetronilho.arduinoappmonitor;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Html;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.physicaloid.lib.Physicaloid;
import com.physicaloid.lib.usb.driver.uart.ReadLisener;

public class MainActivity extends AppCompatActivity {

    TextView text1;
    Button Open, Close, Foward, Back, Right, Left, LED;
    Physicaloid mPhysicaloid; 		// initialising library
    int led = 1;
    Handler mHandler = new Handler();

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        text1 = (TextView) findViewById(R.id.textView);

        LED = (Button) findViewById(R.id.buttonLED);
        Open = (Button) findViewById(R.id.buttonO);
        Close = (Button) findViewById(R.id.buttonC);
        Foward = (Button) findViewById(R.id.buttonF);
        Left = (Button) findViewById(R.id.buttonL);
        Right = (Button) findViewById(R.id.buttonR);
        Back = (Button) findViewById(R.id.buttonB);

        mPhysicaloid = new Physicaloid(this); 		// setting the context for library

        setEnabledUi(false);

        Foward.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {

                if(event.getAction() == MotionEvent.ACTION_DOWN){ //ao pressionar
                    moveF();
                }

                if(event.getAction() == MotionEvent.ACTION_UP){ //sem pressionar
                    moveStop();
                }
                return true;
            }

        });

        Back.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {

                if(event.getAction() == MotionEvent.ACTION_DOWN){ //ao pressionar
                    moveB();
                }

                if(event.getAction() == MotionEvent.ACTION_UP){ //sem pressionar
                    moveStop();
                }
                return true;
            }

        });

        Left.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {

                if(event.getAction() == MotionEvent.ACTION_DOWN){ //ao pressionar
                    moveL();
                }

                if(event.getAction() == MotionEvent.ACTION_UP){ //sem pressionar
                    moveStop();
                }
                return true;
            }

        });

        Right.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {

                if(event.getAction() == MotionEvent.ACTION_DOWN){ //ao pressionar
                    moveR();
                }

                if(event.getAction() == MotionEvent.ACTION_UP){ //sem pressionar
                    moveStop();
                }
                return true;
            }

        });


    }


    private void setEnabledUi(boolean on) {

        if(on) {

            Open.setEnabled(false);
            LED.setEnabled(true);
            Close.setEnabled(true);
            Foward.setEnabled(true);
            Right.setEnabled(true);
            Left.setEnabled(true);
            Back.setEnabled(true);

        } else {

            Open.setEnabled(true);
            LED.setEnabled(false);
            Close.setEnabled(false);
            Foward.setEnabled(false);
            Right.setEnabled(false);
            Left.setEnabled(false);
            Back.setEnabled(false);
        }
    }

    public void onClickOpen(View v) {

        mPhysicaloid.setBaudrate(9600);


        if(mPhysicaloid.open()) { 	// tries to connect to device and if device was connected

            setEnabledUi(true);
            initReadListener();

        } else {

            //Error while connecting
            Toast.makeText(this, "Cannot open", Toast.LENGTH_LONG).show();
        }
    }

    public void initReadListener(){ //inicializar o leitor de dados from Arduino

        mPhysicaloid.addReadListener(new ReadLisener() {
            @Override
            public void onRead(int size) {
                byte[] buf = new byte[size];
                mPhysicaloid.read(buf, size);
                setText(Html.fromHtml("<font color=blue>" + new String(buf) + "</font>"));
            }
        });

    }

    public void onClickClose(View v) {	//when close button is pressed

        if(mPhysicaloid.close()) { 	//close the connection to arduino
            mPhysicaloid.clearReadListener();	//clear read listener
            setEnabledUi(false);	// set UI accordingly
        }
    }

    public void moveF() { 	// move foward

        String str = "f";
        writeData(str);
    }


    public void moveB() { 	// move back

        String str = "b";
        writeData(str);
    }


    public void moveR() { 	// move right

        String str = "r";
        writeData(str);
    }


    public void moveL() { 	// move left

        String str = "l";
        writeData(str);
    }

    public void moveStop() { 	// stop the car

        String str = "s";
        writeData(str);
    }

    public void ledOnOff(View v) { 	// turn led on/ off

        String str;

        if(led == 0) {
            str = "z";
            led = 1;  //liga o led
        }
        else {

            str = "x";
            led = 0;   //desliga o led
        }

        if(str.length()>0) {

            byte[] buf = str.getBytes();	//convert string to byte array
            mPhysicaloid.write(buf, buf.length);	//write data to arduino
        }
    }



    public void writeData(String str){

        if(str.length() > 0) {

            byte[] buf = str.getBytes();	//convert string to byte array
            mPhysicaloid.write(buf, buf.length);	//write data to arduino
        }
    }



    private void setText(CharSequence text) { //escreve os dados lidos do arduino no textView

        final CharSequence ftext = text;
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                text1.setText(ftext);
            }
        });
    }


}