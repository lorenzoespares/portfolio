/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.android.navigationdrawerexample;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.SearchManager;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.support.v4.app.ActionBarDrawerToggle;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebSettings.RenderPriority;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SearchView;

/**
 * MOST RECENT COPY: WORKING SLIDE VIEW, GOOGLE WEBVIEW This example illustrates
 * a common usage of the DrawerLayout widget in the Android support library.
 * <p/>
 * <p>
 * When a navigation (left) drawer is present, the host activity should detect
 * presses of the action bar's Up affordance as a signal to open and close the
 * navigation drawer. The ActionBarDrawerToggle facilitates this behavior. Items
 * within the drawer should fall into one of two categories:
 * </p>
 * <p/>
 * <ul>
 * <li><strong>View switches</strong>. A view switch follows the same basic
 * policies as list or tab navigation in that a view switch does not create
 * navigation history. This pattern should only be used at the root activity of
 * a task, leaving some form of Up navigation active for activities further down
 * the navigation hierarchy.</li>
 * <li><strong>Selective Up</strong>. The drawer allows the user to choose an
 * alternate parent for Up navigation. This allows a user to jump across an
 * app's navigation hierarchy at will. The application should treat this as it
 * treats Up navigation from a different task, replacing the current task stack
 * using TaskStackBuilder or similar. This is the only form of navigation drawer
 * that should be used outside of the root activity of a task.</li>
 * </ul>
 * <p/>
 * <p>
 * Right side drawers should be used for actions, not navigation. This follows
 * the pattern established by the Action Bar that navigation should be to the
 * left and actions to the right. An action should be an operation performed on
 * the current contents of the window, for example enabling or disabling a data
 * overlay on top of the current content.
 * </p>
 */
public class MainActivity extends Activity {
	private DrawerLayout mDrawerLayout;
	private ListView mDrawerList;
	private ActionBarDrawerToggle mDrawerToggle;
	static WebView webView;
	private static View rootView;
	public String fragtag = "";

	private CharSequence mDrawerTitle;
	private CharSequence mTitle;
	private String[] mCategoryTitles;
	private final String TAG = "TestLog";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		System.out.println("start");

		Log.v(TAG, "before onCreate ...");

		super.onCreate(savedInstanceState);

		Log.v(TAG, "after onCreate ...");

		setContentView(R.layout.activity_main);

		Log.v(TAG, "after setContentView ...");

		mTitle = mDrawerTitle = getTitle();

		Log.v(TAG, "after getTitle ...");

		mCategoryTitles = getResources().getStringArray(
				R.array.categories_array);

		Log.v(TAG, "after setCategoryTitles ...");

		mDrawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);

		Log.v(TAG, "after get drawerLayout ...");

		mDrawerList = (ListView) findViewById(R.id.left_drawer);

		Log.v(TAG, "after drawerList ...");

		// set a custom shadow that overlays the main content when the drawer
		// opens
		mDrawerLayout.setDrawerShadow(R.drawable.drawer_shadow,
				GravityCompat.START);

		Log.v(TAG, "after setDrawerShadow ...");

		// set up the drawer's list view with items and click listener
		mDrawerList.setAdapter(new ArrayAdapter<String>(this,
				R.layout.drawer_list_item, mCategoryTitles));

		Log.v(TAG, "after setAdapter ...");

		mDrawerList.setOnItemClickListener(new DrawerItemClickListener());

		Log.v(TAG, "after setClickListener ...");

		// enable ActionBar app icon to behave as action to toggle nav drawer
		getActionBar().setDisplayHomeAsUpEnabled(true);

		Log.v(TAG, "after setDisplayHomeAsUpEnabled ...");

		getActionBar().setHomeButtonEnabled(true);

		getActionBar().setDisplayShowTitleEnabled(false);

		Log.v(TAG, "after setHomeButtonEnabled ...");

		Log.v(TAG, "before ActionBarDrawerToggle ...");

		// ActionBarDrawerToggle ties together the the proper interactions
		// between the sliding drawer and the action bar app icon
		mDrawerToggle = new ActionBarDrawerToggle(this, /* host Activity */
		mDrawerLayout, /* DrawerLayout object */
		R.drawable.ic_drawer, /* nav drawer image to replace 'Up' caret */
		R.string.drawer_open, /* "open drawer" description for accessibility */
		R.string.drawer_close /* "close drawer" description for accessibility */
		) {
			public void onDrawerClosed(View view) {
				// getActionBar().setTitle(mTitle);
				getActionBar().setDisplayShowTitleEnabled(false);
				invalidateOptionsMenu(); // creates call to
											// onPrepareOptionsMenu()
			}

			public void onDrawerOpened(View drawerView) {
				getActionBar().setDisplayShowTitleEnabled(true);
				getActionBar().setTitle(mDrawerTitle);
				invalidateOptionsMenu(); // creates call to
											// onPrepareOptionsMenu()
			}
		};

		Log.v(TAG, "after ActionBarDrawerToggle ...");

		mDrawerLayout.setDrawerListener(mDrawerToggle);

		Log.v(TAG, " after setDrawerListener ...");

		if (savedInstanceState == null) {
			selectItem(0);
		}
	}

	/* Called whenever we call invalidateOptionsMenu() */
	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		// If the nav drawer is open, hide action items related to the content
		// view
		boolean drawerOpen = mDrawerLayout.isDrawerOpen(mDrawerList);
		return super.onPrepareOptionsMenu(menu);
	}

	/** Action bar coding **/
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// The action bar home/up action should open or close the drawer.
		// ActionBarDrawerToggle will take care of this.
		if (mDrawerToggle.onOptionsItemSelected(item)) {
			return true;
		}

		// Handle action buttons
		switch (item.getItemId()) {
		case R.id.logout:
			android.webkit.CookieManager.getInstance().removeAllCookie();
			Intent i = new Intent(getApplicationContext(), Login.class);
			startActivity(i);
			return true;
		case R.id.account:
			webView.loadUrl("http://www.bucksell.com/index.php?route=account/account");
			return true;
		case R.id.shoppingcart:
			webView.loadUrl("http://www.bucksell.com/index.php?route=checkout/cart");
			return true;
		case R.id.wishlist:
			webView.loadUrl("http://www.bucksell.com/index.php?route=account/wishlist");
			return true;
		case R.id.checkout:
			webView.loadUrl("http://www.bucksell.com/index.php?route=checkout/checkout");
			return true;

		default:
			return super.onOptionsItemSelected(item);
		}

	}

	/** Search functionality **/
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main_menu, menu);

		SearchManager searchManager = (SearchManager) getSystemService(Context.SEARCH_SERVICE);
		SearchView searchView = (SearchView) menu.findItem(R.id.action_search)
				.getActionView();
		if (null != searchView) {
			searchView.setSearchableInfo(searchManager
					.getSearchableInfo(getComponentName()));
			searchView.setIconifiedByDefault(true);
		}

		SearchView.OnQueryTextListener queryTextListener = new SearchView.OnQueryTextListener() {
			public boolean onQueryTextChange(String newText) {
				// this is your adapter that will be filtered
				return true;
			}

			public boolean onQueryTextSubmit(String query) {
				// Here u can get the value "query" which is entered in the
				// search box.
				// WebView myWebView = (WebView) findViewById(R.id.webPage);
				webView.loadUrl("http://www.bucksell.com/index.php?route=product/search&filter_name="
						+ query);
				return true;
			}
		};
		SearchView.OnCloseListener onCloseListener = new SearchView.OnCloseListener() {

			@Override
			public boolean onClose() {
				// TODO Auto-generated method stub
				return false;
			}
		};

		searchView.setOnCloseListener(onCloseListener);
		searchView.setOnQueryTextListener(queryTextListener);

		return super.onCreateOptionsMenu(menu);

	}

	/* The click listner for ListView in the navigation drawer */
	private class DrawerItemClickListener implements
			ListView.OnItemClickListener {
		@Override
		public void onItemClick(AdapterView<?> parent, View view, int position,
				long id) {
			selectItem(position);
		}
	}

	private void selectItem(int position) {
		// update the main content by replacing fragments
		Fragment fragment = new CategoryFragment();
		Bundle args = new Bundle();
		args.putInt(CategoryFragment.ARG_CATEGORY_NUMBER, position);
		fragment.setArguments(args);

		FragmentManager fragmentManager = getFragmentManager();
		fragmentManager.beginTransaction()
				.replace(R.id.content_frame, fragment).commit();

		// update selected item and title, then close the drawer
		mDrawerList.setItemChecked(position, true);
		setTitle(mCategoryTitles[position]);
		mDrawerLayout.closeDrawer(mDrawerList);
	}

	@Override
	public void setTitle(CharSequence title) {
		mTitle = title;
		getActionBar().setTitle(mTitle);
	}

	/**
	 * When using the ActionBarDrawerToggle, you must call it during
	 * onPostCreate() and onConfigurationChanged()...
	 */

	@Override
	protected void onPostCreate(Bundle savedInstanceState) {
		super.onPostCreate(savedInstanceState);
		// Sync the toggle state after onRestoreInstanceState has occurred.
		mDrawerToggle.syncState();
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		// Pass any configuration change to the drawer toggls
		mDrawerToggle.onConfigurationChanged(newConfig);
	}

	/**
	 * Fragment that appears in the "content_frame", shows a planet
	 */
	public static class CategoryFragment extends Fragment {
		public static final String ARG_CATEGORY_NUMBER = "category_number";

		public CategoryFragment() {
			// Empty constructor required for fragment subclasses
		}

		@Override
		public void onActivityCreated(Bundle savedInstanceState) {
			super.onActivityCreated(savedInstanceState);
		}

		@Override
		public View onCreateView(LayoutInflater inflater, ViewGroup container,
				Bundle savedInstanceState) {
			rootView = inflater.inflate(R.layout.fragment_category, container,
					false);
			int i = getArguments().getInt(ARG_CATEGORY_NUMBER);
			String category = getResources().getStringArray(
					R.array.categories_array)[i];

			// Home
			String myURL = "http://www.bucksell.com/index.php?route=common/home";

			// 0 = Home, 1 = Books, etc.
			if (i == 1)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=59";
			if (i == 2)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=190";
			if (i == 3)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=120";
			if (i == 4)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=104";
			if (i == 5)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=115";
			if (i == 6)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=127";
			if (i == 7)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=130";
			if (i == 8)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=134";
			if (i == 9)
				myURL = "http://www.bucksell.com/index.php?route=product/category&path=153";

			webView = (WebView) rootView.findViewById(R.id.webPage);

			// Webivew settings here
			WebSettings settings = webView.getSettings();
			// enable javascript
			settings.setJavaScriptEnabled(true);
			// increase render priority for speed
			settings.setRenderPriority(RenderPriority.HIGH);
			settings.setCacheMode(settings.LOAD_DEFAULT);

			// prevents link from opening up a new browser to redirect
			webView.setWebViewClient(new WebViewClient() {

				/** Javascript to hide web page javascript **/
				@Override
				public void onLoadResource(WebView view, String url) {
					view.loadUrl("javascript:(function() { "
							+ "document.getElementsByTagName('body')[0].style.background = 'E0FFFF'; "
							+

							"var head = document.getElementById('header');"
							+ "head.style.display = 'none'; " +

							"var categories = document.getElementById('main_navigation');"
							+ "categories.style.display = 'none';" +

							"var bottomFooter = document.getElementById('footer');"
							+ "bottomFooter.style.display = 'none';" +

							"var footer = document.getElementById('footer_nav');"
							+ "footer.style.display = 'none';" +

							"var shopInfo = document.getElementById('shop_info');"
							+ "shopInfo.style.display = 'none';" +

							"var rightColumn = document.getElementById('right_col');"
							+ "rightColumn.style.display = 'none';" +

							"})()");
				}

			});

			// Load the URL
			webView.loadUrl(myURL);

			getActivity().setTitle(category);
			return rootView;
		}
	}

	@Override
	public void onBackPressed() {
		if (webView.canGoBack())
			webView.goBack();
	}

}