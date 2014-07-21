package com.example.android.navigationdrawerexample;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.Window;
import android.view.WindowManager;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class Login extends Activity {

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// hides action bar
		getWindow().requestFeature(Window.FEATURE_ACTION_BAR);
		getActionBar().hide();

		setContentView(R.layout.activity_login);

		// -- hides keyboard before text entry
		this.getWindow().setSoftInputMode(
				WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);

		WebView view = (WebView) this.findViewById(R.id.loginwebview);
		WebSettings settings = view.getSettings();
		settings.setJavaScriptEnabled(true);

		view.loadUrl("file:///android_asset/login.html");

		view.setWebViewClient(new WebViewClient() {

			@Override
			public boolean shouldOverrideUrlLoading(final WebView view,
					String url) {
				if (url.startsWith("http://www.bucksell.com/index.php?route=account/account")) {
					Intent x = new Intent(Login.this, MainActivity.class);
					startActivity(x);
					return true;
				} else if (url
						.startsWith("http://www.bucksell.com/index.php?route=account/success")) {
					Handler handler = new Handler();
					handler.postDelayed(new Runnable() {
						public void run() {
							view.loadUrl("file:///android_asset/login.html");
						}
					}, 6000);
				}

				return false;
			}
		});

	}

	@Override
	public void onBackPressed() {
		// do nothing
	}
}
