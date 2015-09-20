package com.example.nikitayurkov.textmessagesender;

import android.app.Activity;
import android.content.Context;
import android.location.Address;
import android.location.Criteria;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.getpebble.android.kit.Constants;
import com.getpebble.android.kit.PebbleKit;
import com.getpebble.android.kit.util.PebbleDictionary;

import java.io.IOException;
import java.util.List;
import java.util.Locale;
import java.util.UUID;


public class TextActivity extends AppCompatActivity {
    private PebbleKit.PebbleDataReceiver textDataHandler = null;
    Activity activity = this;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_text);
        final Button button = (Button) findViewById(R.id.button);
        final Activity activity = this;

        boolean connected = PebbleKit.isWatchConnected(getApplicationContext());
        boolean appMessages = PebbleKit.areAppMessagesSupported(this);
        Log.d("CONNECTIVITY: ", Boolean.toString(connected));
        Log.d("APPMESSAGES: ", Boolean.toString(appMessages));

        final Handler handler = new Handler();


        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String messageToSend = "Your friend needs help";
                String number = "9522173971";
                SmsManager.getDefault().sendTextMessage(number, null, messageToSend, null, null);
                Toast.makeText(activity, "Sent message!", Toast.LENGTH_LONG);

            }
        });

        textDataHandler = new PebbleKit.PebbleDataReceiver(UUID.fromString("5f5f17a3-e475-4f37-88ee-6b31e7dd2f4a")) {
            @Override
            public void receiveData(final Context context, final int transactionId, final PebbleDictionary data) {

                PebbleKit.sendAckToPebble(context, transactionId);

                String number = data.toJsonString();
                Log.d("NUMBER: ", number);

                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        String messageToSend;

                        double latitude = MyLocationListener.getLat();
                        double longitude = MyLocationListener.getLon();
                        messageToSend = "Your friend "+ data.getString(1) +" needs help. They are at: https://www.google.com/maps?q=" + latitude + "," + longitude;

                        String number = data.getString(0);

                        SmsManager.getDefault().sendTextMessage(number, null, messageToSend, null, null);
                        Toast.makeText(activity, "Sent message!", Toast.LENGTH_LONG);
                    }
                });
            }
        };
        PebbleKit.registerReceivedDataHandler(this, textDataHandler);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_text, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

}

