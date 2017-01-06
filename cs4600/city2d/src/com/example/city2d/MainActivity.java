package com.example.city2d;

import java.util.Timer;
import java.util.TimerTask;

import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Handler;
import android.annotation.TargetApi;
import android.app.Activity;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity{
	private int mTileRowCount;
	private int mTileColCount;
	private int TILE_SIZE=89;
	private int SECONDS=1000;
	
	private String mUsername="joe";
	private String mPassword="joepass";
	private board gameboard=new board();
	private DBController controller=new DBController(this);
	
	private Button mPastureButton;
	private Button mRiverButton;
	private Button mOceanButton;
	private Button mForestButton;
	private Button mTownButton;
	private Button mCityButton;
	
	private boolean mPasturePurchased=false;
	private boolean mRiverPurchased=false;
	private boolean mOceanPurchased=false;
	private boolean mForestPurchased=false;
	private boolean mTownPurchased=false;
	private boolean mCityPurchased=false;
	
	private boolean mBuying=false;
	
	private int mRiverCost=20;
	private int mOceanCost=30;
	private int mPastureCost=10;
	private int mForestCost=50;
	private int mTownCost=100;
	private int mCityCost=500;
	
	private int mRiverType=10;
	private int mOceanType=20;
	private int mPastureType=30;
	private int mForestType=40;
	private int mTownType=50;
	private int mCityType=60;
	
	private int mRiverJob=10;
	private int mOceanJob=20;
	private int mPastureJob=30;
	private int mForestJob=40;
	private int mTownJob=50;
	private int mCityJob=60;

	private int mRiverJobPay=20;
	private int mOceanJobPay=50;
	private int mPastureJobPay=10;
	private int mForestJobPay=50;
	private int mTownJobPay=100;
	private int mCityJobPay=1000;

	private int mRiverJobTime=2000;
	private int mOceanJobTime=3000;
	private int mPastureJobTime=1000;
	private int mForestJobTime=4000;
	private int mTownJobTime=5000;
	private int mCityJobTime=10000;
	
	private int mTileClosed=0;
	private int mTileAvailable=1;
	private int mTileOpen=2;
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        setupTileIds();
        createxml();
        newPlayerCheck();
        setOnClickers();
    }
	public boolean canAfford(int purchaseType){
		int cost=0;
		if(purchaseType==mRiverType) {cost=mRiverCost;}
		else if(purchaseType==mOceanType) {cost=mOceanCost;}
		else if(purchaseType==mPastureType) {cost=mPastureCost;}
		else if(purchaseType==mForestType) {cost=mForestCost;}
		else if(purchaseType==mTownType) {cost=mTownCost;}
		else if(purchaseType==mCityType) {cost=mCityCost;}
		if(cost<=controller.getMoney(mUsername)){
			int newMoneyAmount=controller.getMoney(mUsername)-cost;
			controller.setMoney(mUsername,newMoneyAmount);
			TextView moneycount = (TextView)findViewById(R.id.money_count);
            moneycount.setText(Integer.toString(newMoneyAmount));
			return true;
		}
		else {return false;}
	}
    public void setOnClickers(){
        mRiverButton = (Button)findViewById(R.id.river_button);
        mRiverButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	if(canAfford(mRiverType)) { 
            		Toast.makeText(MainActivity.this, R.string.river_button_buy_toast, Toast.LENGTH_SHORT).show(); 
            		mRiverPurchased=true;
            		mOceanPurchased=false;
            		mPasturePurchased=false;
            		mForestPurchased=false;
            		mTownPurchased=false;
            		mCityPurchased=false;
            		mBuying=true;
            	}
            	else if(!canAfford(mRiverType)){Toast.makeText(MainActivity.this, R.string.buy_fail_toast, Toast.LENGTH_SHORT).show();}
            }
        });
        mOceanButton = (Button)findViewById(R.id.ocean_button);
        mOceanButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	if(canAfford(mOceanType)) { 
            		Toast.makeText(MainActivity.this, R.string.ocean_button_buy_toast, Toast.LENGTH_SHORT).show(); 
            		mRiverPurchased=false;
            		mOceanPurchased=true;
            		mPasturePurchased=false;
            		mForestPurchased=false;
            		mTownPurchased=false;
            		mCityPurchased=false;
            		mBuying=true;
            	}
            	else if(!canAfford(mOceanType)){Toast.makeText(MainActivity.this, R.string.buy_fail_toast, Toast.LENGTH_SHORT).show();}
            }
        });
        mPastureButton = (Button)findViewById(R.id.pasture_button);
        mPastureButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	if(canAfford(mPastureType)) { 
            		Toast.makeText(MainActivity.this, R.string.pasture_button_buy_toast, Toast.LENGTH_SHORT).show(); 
            		mRiverPurchased=false;
            		mOceanPurchased=false;
            		mPasturePurchased=true;
            		mForestPurchased=false;
            		mTownPurchased=false;
            		mCityPurchased=false;
            		mBuying=true;
            	}
            	else if(!canAfford(mPastureType)){Toast.makeText(MainActivity.this, R.string.buy_fail_toast, Toast.LENGTH_SHORT).show();}
            }
        });
        mForestButton = (Button)findViewById(R.id.forest_button);
        mForestButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	if(canAfford(mForestType)) { 
            		Toast.makeText(MainActivity.this, R.string.forest_button_buy_toast, Toast.LENGTH_SHORT).show(); 
            		mRiverPurchased=false;
            		mOceanPurchased=false;
            		mPasturePurchased=false;
            		mForestPurchased=true;
            		mTownPurchased=false;
            		mCityPurchased=false;
            		mBuying=true;
            	}
            	else if(!canAfford(mForestType)) { Toast.makeText(MainActivity.this, R.string.buy_fail_toast, Toast.LENGTH_SHORT).show(); }
            }
        });
        mTownButton = (Button)findViewById(R.id.town_button);
        mTownButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	if(canAfford(mTownType)) { 
            		Toast.makeText(MainActivity.this, R.string.town_button_buy_toast, Toast.LENGTH_SHORT).show(); 
            		mRiverPurchased=false;
            		mOceanPurchased=false;
            		mPasturePurchased=false;
            		mForestPurchased=false;
            		mTownPurchased=true;
            		mCityPurchased=false;
            		mBuying=true;
            	}
            	else if(!canAfford(mTownType)) { Toast.makeText(MainActivity.this, R.string.buy_fail_toast, Toast.LENGTH_SHORT).show(); }
            }
        });
        mCityButton = (Button)findViewById(R.id.city_button);
        mCityButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            	if(canAfford(mCityType)){
            		Toast.makeText(MainActivity.this, R.string.city_button_buy_toast, Toast.LENGTH_SHORT).show();
            		mRiverPurchased=false;
            		mOceanPurchased=false;
            		mPasturePurchased=false;
            		mForestPurchased=false;
            		mTownPurchased=false;
            		mCityPurchased=true;
            		mBuying=true;
            	}
            	else if(!canAfford(mCityType)) { Toast.makeText(MainActivity.this, R.string.buy_fail_toast, Toast.LENGTH_SHORT).show(); }
            }
        });
        for(int x=0;x<mTileRowCount;x++){
        	for(int y=0;y<mTileColCount;y++){
				final String tilenamestr="tile"+Integer.toString(x)+"_"+Integer.toString(y);
				final int tileidnum=getResources().getIdentifier(tilenamestr, "id", getPackageName());
				updateTilesTask task=new updateTilesTask(tileidnum);
				task.execute();
        		ImageView image=(ImageView)findViewById(tileidnum);
        		image.setOnClickListener(new View.OnClickListener() {
        			public void onClick(View v) {
        				if(controller.getTileStatusById(tileidnum)==mTileOpen && !mBuying){
        					final int jobnum=controller.getTileJobById(v.getId());
        					if(jobnum==mRiverJob){Toast.makeText(MainActivity.this, R.string.river_job_toast, Toast.LENGTH_SHORT).show();}
        					else if(jobnum==mOceanJob){Toast.makeText(MainActivity.this, R.string.ocean_job_toast, Toast.LENGTH_SHORT).show();}
        					else if(jobnum==mPastureJob){Toast.makeText(MainActivity.this, R.string.pasture_job_toast, Toast.LENGTH_SHORT).show();}
        					else if(jobnum==mForestJob){Toast.makeText(MainActivity.this, R.string.forest_job_toast, Toast.LENGTH_SHORT).show();}
        					else if(jobnum==mTownJob){Toast.makeText(MainActivity.this, R.string.town_job_toast, Toast.LENGTH_SHORT).show();}
        					else if(jobnum==mCityJob){Toast.makeText(MainActivity.this, R.string.city_job_toast, Toast.LENGTH_SHORT).show();}
        					startAsync(jobnum);
        				}
        				else if(!(controller.getTileStatusById(tileidnum)==mTileOpen) && mBuying){Toast.makeText(MainActivity.this, R.string.tile_wrong_buy_toast, Toast.LENGTH_SHORT).show();}
        				else if(controller.getTileStatusById(tileidnum)==mTileOpen && mRiverPurchased){
    						Toast.makeText(MainActivity.this, R.string.river_placement_toast, Toast.LENGTH_SHORT).show();
				    		ImageView img=(ImageView)findViewById(v.getId());
					    	img.setImageResource(R.drawable.river_tile);
					    	controller.setTileJobById(v.getId(), mRiverJob);
					    	controller.setTileTypeById(v.getId(), mRiverType);
	        				mRiverPurchased=false;
	        				mOceanPurchased=false;
	        				mPasturePurchased=false;
	        				mForestPurchased=false;
	    					mTownPurchased=false;
	    					mCityPurchased=false;
	    					mBuying=false;
    					}
        				else if(controller.getTileStatusById(tileidnum)==mTileOpen && mOceanPurchased){
    						Toast.makeText(MainActivity.this, R.string.ocean_placement_toast, Toast.LENGTH_SHORT).show();
				    		ImageView img=(ImageView)findViewById(v.getId());
					    	img.setImageResource(R.drawable.ocean_tile);
					    	controller.setTileJobById(v.getId(), mOceanJob);
					    	controller.setTileTypeById(v.getId(), mOceanType);
	        				mRiverPurchased=false;
	        				mOceanPurchased=false;
	        				mPasturePurchased=false;
	        				mForestPurchased=false;
	    					mTownPurchased=false;
	    					mCityPurchased=false;
	    					mBuying=false;
    					}
        				else if(controller.getTileStatusById(tileidnum)==mTileOpen && mPasturePurchased){
    						Toast.makeText(MainActivity.this, R.string.pasture_placement_toast, Toast.LENGTH_SHORT).show();
				    		ImageView img=(ImageView)findViewById(v.getId());
					    	img.setImageResource(R.drawable.pasture_tile);
					    	controller.setTileJobById(v.getId(), mPastureJob);
					    	controller.setTileTypeById(v.getId(), mPastureType);
	        				mRiverPurchased=false;
	        				mOceanPurchased=false;
	        				mPasturePurchased=false;
	        				mForestPurchased=false;
	    					mTownPurchased=false;
	    					mCityPurchased=false;
	    					mBuying=false;
    					}
    					else if(controller.getTileStatusById(tileidnum)==mTileOpen && mForestPurchased){
    						Toast.makeText(MainActivity.this, R.string.forest_placement_toast, Toast.LENGTH_SHORT).show();
				    		ImageView img=(ImageView)findViewById(v.getId());
					    	img.setImageResource(R.drawable.forest_tile);
					    	controller.setTileJobById(v.getId(), mForestJob);
					    	controller.setTileTypeById(v.getId(), mForestType);
	        				mRiverPurchased=false;
	        				mOceanPurchased=false;
	        				mPasturePurchased=false;
	        				mForestPurchased=false;
	    					mTownPurchased=false;
	    					mCityPurchased=false;
	    					mBuying=false;
    					}
    					else if(controller.getTileStatusById(tileidnum)==mTileOpen && mTownPurchased){
    						Toast.makeText(MainActivity.this, R.string.town_placement_toast, Toast.LENGTH_SHORT).show();
				    		ImageView img=(ImageView)findViewById(v.getId());
					    	img.setImageResource(R.drawable.black_town);
					    	controller.setTileJobById(v.getId(), mTownJob);
					    	controller.setTileTypeById(v.getId(), mTownType);
	        				mRiverPurchased=false;
	        				mOceanPurchased=false;
	        				mPasturePurchased=false;
	        				mForestPurchased=false;
	    					mTownPurchased=false;
	    					mCityPurchased=false;
	    					mBuying=false;
    					}
    					else if(controller.getTileStatusById(tileidnum)==mTileOpen && mCityPurchased){
    						Toast.makeText(MainActivity.this, R.string.city_placement_toast, Toast.LENGTH_SHORT).show();
				    		ImageView img=(ImageView)findViewById(v.getId());
					    	img.setImageResource(R.drawable.black_city);
					    	controller.setTileJobById(v.getId(), mCityJob);
					    	controller.setTileTypeById(v.getId(), mCityType);
	        				mRiverPurchased=false;
	        				mOceanPurchased=false;
	        				mPasturePurchased=false;
	        				mForestPurchased=false;
	    					mTownPurchased=false;
	    					mCityPurchased=false;
	    					mBuying=false;
    					}
        				else if(controller.getTileStatusById(tileidnum)==mTileAvailable && canAfford(mPastureType)){
				    		ImageView img=(ImageView)findViewById(v.getId());
					    	img.setImageResource(R.drawable.pasture_tile);
    				    	controller.buyTile(v.getId());
    				    	controller.updateEastTileStatus(v.getId());
    				    	controller.updateWestTileStatus(v.getId());
    				    	controller.updateNorthTileStatus(v.getId());
    				    	controller.updateSouthTileStatus(v.getId());
    					}
        				else if(controller.getTileStatusById(tileidnum)==mTileAvailable && !canAfford(mPastureType)){Toast.makeText(MainActivity.this, R.string.tile_buy_fail_toast, Toast.LENGTH_SHORT).show();}
        				else if(controller.getTileStatusById(tileidnum)==mTileClosed){Toast.makeText(MainActivity.this, R.string.tile_wrong_buy_toast, Toast.LENGTH_SHORT).show();
        				mRiverPurchased=false;
        				mOceanPurchased=false;
        				mPasturePurchased=false;
        				mForestPurchased=false;
    					mTownPurchased=false;
    					mCityPurchased=false;
    					mBuying=false;
        				}
        			}
        		});
        	}
        }
	}
	private void startAsync(int jobnum) {
		final Handler handler = new Handler();
		final Timer timer = new Timer();
		final int job=jobnum;
		int time=0;
		int units=0;
    	if(job==mRiverJob){time=mRiverJobTime;units=SECONDS;}
    	else if(job==mOceanJob){time=mOceanJobTime;units=SECONDS;}
    	else if(job==mPastureJob){time=mPastureJobTime;units=SECONDS;}
    	else if(job==mForestJob){time=mForestJobTime;units=SECONDS;}
    	else if(job==mTownJob){time=mTownJobTime;units=SECONDS;}
    	else if(job==mCityJob){time=mCityJobTime;units=SECONDS;}
    	final int endtime=time;
    	final int endunits=units;
		TimerTask doAsyncTask = new TimerTask() {
			@Override
			public void run () {
				handler.post(new Runnable() {
					public void run() {
						new CountDownTimer(endtime, endunits) {
					        public void onTick(long millisUntilFinished) {}
					        public void onFinish() {
					        	int jobpay=0;
					        	if(job==mRiverJob){jobpay=mRiverJobPay;}
					        	else if(job==mOceanJob){jobpay=mOceanJobPay;}
					        	else if(job==mPastureJob){jobpay=mPastureJobPay;}
					        	else if(job==mForestJob){jobpay=mForestJobPay;}
					        	else if(job==mTownJob){jobpay=mTownJobPay;}
					        	else if(job==mCityJob){jobpay=mCityJobPay;}
					        	int postjobmoney=controller.getMoney(mUsername)+jobpay;
					        	controller.setMoney(mUsername, postjobmoney);
					        	TextView moneytext = (TextView)findViewById(R.id.money_count);
					        	moneytext.setText(Integer.toString(postjobmoney));
					        }
						}.start();
					}
				});
			}
		};
		timer.schedule(doAsyncTask, 0);
	}

	public void newPlayerCheck(){
		boolean usernameindb=controller.doesPlayerExist(mUsername);
		if(!usernameindb) {startnewgame();}
		int newMoneyAmount=controller.getMoney(mUsername);
		TextView moneycount = (TextView)findViewById(R.id.money_count);
        moneycount.setText(Integer.toString(newMoneyAmount));
        setupTileIds();
	}
    public void setupTileIds(){
    	mTileRowCount=gameboard.getTileRowCount();
    	mTileColCount=gameboard.getTileColCount();
	    for(int x=0;x<mTileRowCount;x++){
	    	for(int y=0;y<mTileColCount;y++){
				String tileidstr="tile"+Integer.toString(x)+"_"+Integer.toString(y);
				int tileidnum=getResources().getIdentifier(tileidstr, "id", getPackageName());
				controller.setupTileId(tileidnum, tileidstr);
	    	}
	    }
    }
    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
	public void createxml(){
    	int cellpadding=3;
    	RelativeLayout rellayout=(RelativeLayout)findViewById(R.id.rellay);
    	rellayout.setBackgroundColor(Color.rgb(0,0,0));
    	for(int x=0;x<mTileRowCount;x++){
			TableRow row=new TableRow(this);
			TableRow.LayoutParams rowparams=new TableRow.LayoutParams(LayoutParams.MATCH_PARENT,TILE_SIZE);
			row.setLayoutParams(rowparams);
			row.setY(TILE_SIZE*x);

			String rowidstr="tile_row"+Integer.toString(x);
			int rowidnum=getResources().getIdentifier(rowidstr, "id", getPackageName());
			row.setId(rowidnum);
			for(int y=0;y<mTileColCount;y++){
				int imgId=0;
		    	FrameLayout frame=new FrameLayout(this);
				TableRow.LayoutParams frameparams=new TableRow.LayoutParams(TILE_SIZE,TILE_SIZE);
		    	frame.setLayoutParams(frameparams);
				frame.setPadding(cellpadding, cellpadding, cellpadding, cellpadding);
				frame.setBackgroundColor(Color.rgb(30,90,30));
				
				String frameidstr="tileframe"+Integer.toString(x)+"_"+Integer.toString(y);
				String imageidstr="tile"+Integer.toString(x)+"_"+Integer.toString(y);
				
				int frameidnum=getResources().getIdentifier(frameidstr, "id", getPackageName());
				int imageidnum=getResources().getIdentifier(imageidstr, "id", getPackageName());
		    	ImageView image=new ImageView(this);
		    	if(controller.getTileStatusByName(imageidstr)==mTileAvailable || controller.getTileStatusByName(imageidstr)==mTileClosed){
		    		imgId = getResources().getIdentifier(getPackageName()+":drawable/primary_forest_tile" , null, null);
		    	}
		    	else if(controller.getTileTypeByName(imageidstr)==mRiverType && controller.getTileStatusByName(imageidstr)==mTileOpen){
		    		imgId = getResources().getIdentifier(getPackageName()+":drawable/river_tile" , null, null);
		    	}
		    	else if(controller.getTileTypeByName(imageidstr)==mOceanType && controller.getTileStatusByName(imageidstr)==mTileOpen){
		    		imgId = getResources().getIdentifier(getPackageName()+":drawable/ocean_tile" , null, null);
		    	}
		    	else if(controller.getTileTypeByName(imageidstr)==mPastureType && controller.getTileStatusByName(imageidstr)==mTileOpen){
		    		imgId = getResources().getIdentifier(getPackageName()+":drawable/pasture_tile" , null, null);
		    	}
		    	else if(controller.getTileTypeByName(imageidstr)==mForestType && controller.getTileStatusByName(imageidstr)==mTileOpen){
		    		imgId = getResources().getIdentifier(getPackageName()+":drawable/forest_tile" , null, null);
		    	}
		    	else if(controller.getTileTypeByName(imageidstr)==mTownType && controller.getTileStatusByName(imageidstr)==mTileOpen){
		    		imgId = getResources().getIdentifier(getPackageName()+":drawable/black_town" , null, null);
		    	}
		    	else if(controller.getTileTypeByName(imageidstr)==mCityType && controller.getTileStatusByName(imageidstr)==mTileOpen){
		    		imgId = getResources().getIdentifier(getPackageName()+":drawable/black_city" , null, null);
		    	}
		    	image.setImageBitmap(BitmapFactory.decodeResource(getResources(),imgId));
		    	image.setVisibility(1);
		  
				frame.setId(frameidnum);
				image.setId(imageidnum);
				
		    	frame.addView(image);
		    	row.addView(frame);
			}
			rellayout.addView(row);  
		}
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    public void startnewgame(){
    	controller.insertPlayer(mUsername,mPassword);
    	int row=(mTileRowCount/2);
    	int col=(mTileColCount/2);
    	String tilename="tile"+Integer.toString(row)+"_"+Integer.toString(col);

    	int tileidnum = controller.getTileIdByName(tilename);
    	controller.buyTile(tileidnum);
		ImageView img=(ImageView)findViewById(tileidnum);
    	img.setImageResource(R.drawable.pasture_tile);
    	
    	controller.updateNorthTileStatus(tileidnum);
    	controller.updateSouthTileStatus(tileidnum);
    	controller.updateEastTileStatus(tileidnum);
    	controller.updateWestTileStatus(tileidnum);
	}
	private class updateTilesTask extends AsyncTask<Void,Void,Void>{
		int tileid;
		updateTilesTask(int x){
			tileid=x;
		}
		@Override
		protected Void doInBackground(Void... params) {
			return null;
		}
	}
}