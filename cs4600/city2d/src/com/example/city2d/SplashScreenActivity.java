package com.example.city2d;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
 
public class SplashScreenActivity extends Activity {
	private static final int SPLASH_SHOW_TIME = 5000;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		setContentView(R.layout.activity_splash_screen);
		splashTask launcher = new splashTask();
		launcher.start();
		}
	
	private class splashTask extends Thread{
		@Override
		public void run(){
			try{
				Thread.sleep(SPLASH_SHOW_TIME);
			}
			catch(Exception e){
			}
			Intent i = new Intent(SplashScreenActivity.this,MainActivity.class);
			startActivity(i);
			finish();
		}
	}
}