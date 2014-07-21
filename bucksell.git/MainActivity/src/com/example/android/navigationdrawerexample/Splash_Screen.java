package com.example.android.navigationdrawerexample;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.view.Window;
import android.widget.Toast;

public class Splash_Screen extends Activity {

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// hides action bar
		getWindow().requestFeature(Window.FEATURE_ACTION_BAR);
		getActionBar().hide();

		setContentView(R.layout.activity_splash);

		final Handler handler = new Handler();
		handler.postDelayed(new Runnable() {
			public void run() {
				// TODO: Your application init goes here.
				Intent splashscreen = new Intent(Splash_Screen.this,
						Login.class);
				Splash_Screen.this.startActivity(splashscreen);
				if (isNetworkAvailable() == false) {
					Toast.makeText(
							getApplicationContext(),
							"No Internet Connection Detected, Please turn on your Wi-Fi.",
							Toast.LENGTH_LONG).show();
					startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
				} else
					Splash_Screen.this.finish();
			}
		}, 2200);
	}

	// Check if internet is available, display error message if no network is
	// detected
	private boolean isNetworkAvailable() {
		ConnectivityManager CM = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo NetInfo = CM.getActiveNetworkInfo();
		return NetInfo != null && NetInfo.isConnectedOrConnecting();
	}

	public static void showNoConnectionDialog(Context ctx1) {
		final Context ctx = ctx1;
		AlertDialog.Builder builder = new AlertDialog.Builder(ctx);
		builder.setCancelable(true);
		builder.setMessage("no_connection");
		builder.setTitle("no_connection_title");
		builder.setPositiveButton("settings",
				new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						ctx.startActivity(new Intent(
								Settings.ACTION_WIRELESS_SETTINGS));
					}
				});
		builder.show();
	}

}
