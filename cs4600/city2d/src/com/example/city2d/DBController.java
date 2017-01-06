package com.example.city2d;

import java.util.Vector;
import android.util.Log;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DBController extends SQLiteOpenHelper {
	private static final String LOGCAT = null;
	private board gameboard=new board();
	private int mTileRowCount;
	private int mTileColCount;
	private int mInitTileCost=100;
	private int mPastureType=30;
	private int mPastureJob=30;
    public DBController(Context applicationcontext){
    	super(applicationcontext, "androidsqlite.db",null,1);
    	mTileRowCount=gameboard.getTileRowCount();
    	mTileColCount=gameboard.getTileColCount();
    	Log.d(LOGCAT,"database created");
    }
    @Override
    public void onCreate(SQLiteDatabase db){
    	String createplayerquery;
    	createplayerquery="CREATE TABLE IF NOT EXISTS player_table(user_id TEXT PRIMARY KEY, user_password TEXT, user_money INTEGER, user_xp INTEGER, user_level INTEGER)";
        Log.d(LOGCAT,createplayerquery);
		db.execSQL(createplayerquery);
		Log.d(LOGCAT,"player_table created");
		String createmapquery;
		createmapquery="CREATE TABLE IF NOT EXISTS map_table(tile_name TEXT PRIMARY KEY, tile_id INTEGER NULL, tile_x INTEGER NULL, tile_y INTEGER NULL, tile_type INTEGER NULL, tile_status INTEGER NULL, tile_cost INTEGER NULL, tile_job INTEGER, tile_starttime INTEGER)";
        Log.d(LOGCAT,createmapquery);
		db.execSQL(createmapquery);
		Log.d(LOGCAT,"map_table created");
        for(int x=0;x<mTileRowCount;x++){
        	for(int y=0;y<mTileColCount;y++){
        		String tile_name="tile"+Integer.toString(x)+"_"+Integer.toString(y);
        		String tile_x=Integer.toString(x);
        		String tile_y=Integer.toString(y);	
        		String tile_type=Integer.toString(mPastureType);	
        		String tile_status=Integer.toString(0);	
        		String tile_cost=Integer.toString(mInitTileCost);
        		String tile_job=Integer.toString(mPastureJob);	
        		String tile_starttime=Integer.toString(0);	
        		String insertTilesQuery="INSERT OR IGNORE INTO map_table(tile_name,tile_x,tile_y,tile_type,tile_status,tile_cost,tile_job, tile_starttime) VALUES('"+tile_name+"','"+tile_x+"','"+tile_y+"','"+tile_type+"','"+tile_status+"','"+tile_cost+"','"+tile_job+"','"+tile_starttime+"')";
                Log.d(LOGCAT,insertTilesQuery);
        		db.execSQL(insertTilesQuery);
        	}
        }
		Log.d(LOGCAT,"map_table started");
		Log.d(LOGCAT,"map_table initialized");
    }
    @Override
    public void onUpgrade(SQLiteDatabase db, int version_old, int current_version) {}
    public void setupTileId(int tileidnum, String tileidstr){
		SQLiteDatabase db = this.getWritableDatabase();
    	String updateIdQuery;
    	updateIdQuery="UPDATE map_table SET tile_id="+tileidnum+" WHERE tile_name='"+tileidstr+"'";
    	db.execSQL(updateIdQuery);
    	}
    public void buyTile(int tileidnum){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String buyQuery;
    	buyQuery="UPDATE map_table SET tile_status=2 WHERE tile_id="+tileidnum;
    	db.execSQL(buyQuery);
    	}
    public void updateNorthTileStatus(int tileidnum){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String buyQuery;
    	int buyx=getTileXById(tileidnum);
    	int buyy=getTileYById(tileidnum)+1;
    	if(buyy>=0 && buyy<mTileRowCount && buyx>=0 && buyx<mTileColCount ){
	    	buyQuery="UPDATE map_table SET tile_status=1 WHERE tile_x="+buyx+" AND tile_y="+buyy+" AND tile_status<1";
	    	Log.d("query",buyQuery);
	    	db.execSQL(buyQuery);
    		}
    	}
    public void updateSouthTileStatus(int tileidnum){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String buyQuery;
    	int buyx=getTileXById(tileidnum);
    	int buyy=getTileYById(tileidnum)-1;
    	if(buyy>=0 && buyy<mTileRowCount && buyx>=0 && buyx<mTileColCount ){
		    buyQuery="UPDATE map_table SET tile_status=1 WHERE tile_x="+buyx+" AND tile_y="+buyy+" AND tile_status<1";
		    Log.d("query",buyQuery);
		    db.execSQL(buyQuery);
    		}
    	}
    public void updateEastTileStatus(int tileidnum){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String buyQuery;
    	int buyx=getTileXById(tileidnum)+1;
    	int buyy=getTileYById(tileidnum);
    	if(buyy>=0 && buyy<mTileRowCount && buyx>=0 && buyx<mTileColCount ){
	    	buyQuery="UPDATE map_table SET tile_status=1 WHERE tile_x="+buyx+" AND tile_y="+buyy+" AND tile_status<1";
	    	Log.d("query",buyQuery);
	    	db.execSQL(buyQuery);
    		}
    	}
    public void updateWestTileStatus(int tileidnum){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String buyQuery;
    	int buyx=getTileXById(tileidnum)-1;
    	int buyy=getTileYById(tileidnum);
    	if(buyy>=0 && buyy<mTileRowCount && buyx>=0 && buyx<mTileColCount ){
	    	buyQuery="UPDATE map_table SET tile_status=1 WHERE tile_x="+buyx+" AND tile_y="+buyy+" AND tile_status<1";
	    	Log.d("query",buyQuery);
    		db.execSQL(buyQuery);
    		}
    	}
    public int getNorthTileId(int tileidnum){
    	String id="";
    	int getx=getTileXById(tileidnum);
    	int gety=getTileYById(tileidnum)+1;
    	Log.d(LOGCAT,"north x="+getx+" y="+gety);
    	if(gety>=0 && gety<mTileRowCount && getx>=0 && getx<mTileColCount ){
    		SQLiteDatabase db = this.getWritableDatabase();	
    		String getQuery="SELECT tile_id FROM map_table WHERE tile_x="+getx+" AND tile_y="+gety+"";
	    	Log.d("query",getQuery);
			Cursor cursor = db.rawQuery(getQuery, null);
			while(cursor.moveToNext()) {id=cursor.getString(0);}
			return Integer.parseInt(id);
    		}
    	else {return -1;}
    	}
    public int getSouthTileId(int tileidnum){
    	String id="";
    	int getx=getTileXById(tileidnum);
    	int gety=getTileYById(tileidnum)-1;
    	Log.d(LOGCAT,"south x="+getx+" y="+gety);
    	if(gety>=0 && gety<mTileRowCount && getx>=0 && getx<mTileColCount ){
    		SQLiteDatabase db = this.getWritableDatabase();	
    		String getQuery="SELECT tile_id FROM map_table WHERE tile_x="+getx+" AND tile_y="+gety+"";
	    	Log.d("query",getQuery);
			Cursor cursor = db.rawQuery(getQuery, null);
			while(cursor.moveToNext()) {id=cursor.getString(0);}
			return Integer.parseInt(id);
    		}
    	else {return -1;}
    	}
    public int getEastTileId(int tileidnum){
    	String id="";
    	int getx=getTileXById(tileidnum)+1;
    	int gety=getTileYById(tileidnum);
    	Log.d(LOGCAT,"east x="+getx+" y="+gety);
    	if(gety>=0 && gety<mTileRowCount && getx>=0 && getx<mTileColCount ){
    		SQLiteDatabase db = this.getWritableDatabase();	
    		String getQuery="SELECT tile_id FROM map_table WHERE tile_x="+getx+" AND tile_y="+gety+"";
	    	Log.d("query",getQuery);
			Cursor cursor = db.rawQuery(getQuery, null);
			while(cursor.moveToNext()) {id=cursor.getString(0);}
			return Integer.parseInt(id);
    		}
    	else {return -1;}
    	}
    public int getWestTileId(int tileidnum){
    	String id="";
    	int getx=getTileXById(tileidnum)-1;
    	int gety=getTileYById(tileidnum);
    	Log.d(LOGCAT,"west x="+getx+" y="+gety);
    	if(gety>=0 && gety<mTileRowCount && getx>=0 && getx<mTileColCount ){
    		SQLiteDatabase db = this.getWritableDatabase();	
    		String getQuery="SELECT tile_id FROM map_table WHERE tile_x="+getx+" AND tile_y="+gety+"";
	    	Log.d("query",getQuery);
			Cursor cursor = db.rawQuery(getQuery, null);
			while(cursor.moveToNext()) {id=cursor.getString(0);}
			return Integer.parseInt(id);
    		}
    	else {return -1;}
    	}
    public int getTileIdByName(String tilename) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_id FROM map_table WHERE tile_name='"+tilename+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {tilevec.add(cursor.getString(0));}
		return Integer.parseInt(tilevec.elementAt(0));
		}
    public int getTileXByName(String tilename) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_x FROM map_table WHERE tile_name='"+tilename+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {tilevec.add(cursor.getString(0));}
		return Integer.parseInt(tilevec.elementAt(0));
		}
    public int getTileYByName(String tilename) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_y FROM map_table WHERE tile_name='"+tilename+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {tilevec.add(cursor.getString(0));}
		return Integer.parseInt(tilevec.elementAt(0));
		}
    public int getTileTypeByName(String tilename) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_type FROM map_table WHERE tile_name='"+tilename+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {tilevec.add(cursor.getString(0));}
		return Integer.parseInt(tilevec.elementAt(0));
		}
    public int getTileStatusByName(String tilename) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_status FROM map_table WHERE tile_name='"+tilename+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {tilevec.add(cursor.getString(0));}
		return Integer.parseInt(tilevec.elementAt(0));
		}
    public int getTileCostByName(String tilename) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_cost FROM map_table WHERE tile_name='"+tilename+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {tilevec.add(cursor.getString(0));}
		return Integer.parseInt(tilevec.elementAt(0));
		}
    public void setTileCostByName(String tilename,int cost) {
		SQLiteDatabase db = this.getWritableDatabase();	
    	String setTileCostQuery;
    	setTileCostQuery="UPDATE map_table SET tile_cost="+cost+" WHERE tile_name='"+tilename+"'";
    	db.execSQL(setTileCostQuery);
    	}
    public int getTileJobByName(String tilename) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_job FROM map_table WHERE tile_name='"+tilename+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {tilevec.add(cursor.getString(0));}
		return Integer.parseInt(tilevec.elementAt(0));
		}
    public void setTileJobByName(String tilename, int newjob){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String setTileJobQuery;
    	setTileJobQuery="UPDATE map_table SET tile_job="+newjob+" WHERE tile_name='"+tilename+"'";
    	db.execSQL(setTileJobQuery);
    	}
    public int getTileStarttimeByName(String tilename) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_starttime FROM map_table WHERE tile_name='"+tilename+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {tilevec.add(cursor.getString(0));}
		return Integer.parseInt(tilevec.elementAt(0));
		}
    public String getTileNameById(int tileid) {
    	String name="";
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_name FROM map_table WHERE tile_id='"+tileid+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {name=cursor.getString(0);}
		return name;
		}
    public int getTileXById(int tileid){
    	int x=0;
		SQLiteDatabase db = this.getReadableDatabase();
		String getQuery="SELECT tile_x FROM map_table WHERE tile_id="+tileid+"";
		Log.d("query",getQuery);
		Cursor cursor = db.rawQuery(getQuery, null);
		while(cursor.moveToNext()) {x=Integer.parseInt(cursor.getString(0));}
		return x;
		}
    public int getTileYById(int tileid){
    	int y=0;
		SQLiteDatabase db = this.getReadableDatabase();	
		String getQuery="SELECT tile_y FROM map_table WHERE tile_id="+tileid+"";
		Log.d("query",getQuery);
		Cursor cursor = db.rawQuery(getQuery, null);
		while(cursor.moveToNext()) {y=Integer.parseInt(cursor.getString(0));}
		return y;
		}
    public int getTileTypeById(int tileid) {
    	int type=0;
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_type FROM map_table WHERE tile_id='"+tileid+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {type=Integer.parseInt(cursor.getString(0));}
		return type;
		}
    public void setTileTypeById(int tileid, int newtype){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String setTileTypeQuery;
    	setTileTypeQuery="UPDATE map_table SET tile_type="+newtype+" WHERE tile_id='"+tileid+"'";
    	db.execSQL(setTileTypeQuery);
    	}
    public int getTileStatusById(int tileid) {
    	int status=0;
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_status FROM map_table WHERE tile_id='"+tileid+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {status=Integer.parseInt(cursor.getString(0));}
		return status;
		}
    public int getTileCostById(int tileid) {
    	int cost=0;
		SQLiteDatabase db = this.getReadableDatabase();
		String getAvailableQuery="SELECT tile_cost FROM map_table WHERE tile_id='"+tileid+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {cost=Integer.parseInt(cursor.getString(0));}
		return cost;
		}
    public void setTileCostById(int tileid,int cost) {
		SQLiteDatabase db = this.getWritableDatabase();	
    	String setTileCostQuery;
    	setTileCostQuery="UPDATE map_table SET tile_cost="+cost+" WHERE tile_id='"+tileid+"'";
    	db.execSQL(setTileCostQuery);
    	}
    public int getTileJobById(int tileid) {
    	int job=0;
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_job FROM map_table WHERE tile_id='"+tileid+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {job=Integer.parseInt(cursor.getString(0));}
		return job;
		}
    public void setTileJobById(int tileid, int newjob){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String setTileJobQuery;
    	setTileJobQuery="UPDATE map_table SET tile_job="+newjob+" WHERE tile_id='"+tileid+"'";
    	db.execSQL(setTileJobQuery);
    	}
    public int getTileStarttimeById(int tileid) {
    	int time=0;
		SQLiteDatabase db = this.getReadableDatabase();	
		String getAvailableQuery="SELECT tile_starttime FROM map_table WHERE tile_id='"+tileid+"'";
		Log.d("query",getAvailableQuery);
		Cursor cursor = db.rawQuery(getAvailableQuery, null);
		while(cursor.moveToNext()) {time=Integer.parseInt(cursor.getString(0));}
		return time;
		}
    public void setMoney(String username, int money){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String setMoneyQuery;
    	setMoneyQuery="UPDATE player_table SET user_money="+money+" WHERE user_id='"+username+"'";
    	db.execSQL(setMoneyQuery);
    	}
    public int getMoney(String username){
    	String money="";
		SQLiteDatabase db = this.getReadableDatabase();	
		String getMoneyQuery="SELECT user_money FROM player_table WHERE user_id='"+username+"'";
		Log.d("query",getMoneyQuery);
		Cursor cursor = db.rawQuery(getMoneyQuery, null);
		while(cursor.moveToNext()) {money=cursor.getString(0);}
		return Integer.parseInt(money);
		}
    public void setXp(String username, int xp){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String setXpQuery;
    	setXpQuery="UPDATE player_table SET user_xp="+xp+" WHERE user_id='"+username+"'";
    	db.execSQL(setXpQuery);
    	}
    public int getXp(String username){
    	String xp="";
		SQLiteDatabase db = this.getReadableDatabase();	
		String getXpQuery="SELECT user_xp FROM player_table WHERE user_id='"+username+"'";
		Log.d("query",getXpQuery);
		Cursor cursor = db.rawQuery(getXpQuery, null);
		while(cursor.moveToNext()) {xp=cursor.getString(0);}
		return Integer.parseInt(xp);
		}
    public void setLevel(String username, int level){
		SQLiteDatabase db = this.getWritableDatabase();	
    	String setLevelQuery;
    	setLevelQuery="UPDATE player_table SET user_level="+level+" WHERE user_id='"+username+"'";
    	db.execSQL(setLevelQuery);
    	}
    public int getLevel(String username){
    	String level="";
		SQLiteDatabase db = this.getReadableDatabase();	
		String getLevelQuery="SELECT user_level FROM player_table WHERE user_id='"+username+"'";
		Log.d("query",getLevelQuery);
		Cursor cursor = db.rawQuery(getLevelQuery, null);
		while(cursor.moveToNext()) {level=cursor.getString(0);}
		return Integer.parseInt(level);
		}
    public void insertPlayer(String username, String password) {
		SQLiteDatabase db = this.getWritableDatabase();	
		int money=1000;
		int xp=0;
		int level=0;
		String insertQuery="INSERT OR IGNORE INTO player_table(user_id,user_password,user_money,user_xp,user_level) VALUES('"+username+"','"+password+"','"+money+"','"+xp+"','"+level+"')";
		Log.d("query",insertQuery);
		db.execSQL(insertQuery);
    	}
    public Vector<String> getPlayer(String username) {
    	Vector<String> tilevec=new Vector<String>();
		SQLiteDatabase db = this.getReadableDatabase();	
		String getPlayerQuery="SELECT * FROM player_table WHERE user_id='"+username+"'";
		Log.d("query",getPlayerQuery);
		Cursor cursor = db.rawQuery(getPlayerQuery, null);
		while(cursor.moveToNext()) {
			tilevec.add(cursor.getString(0));
			tilevec.add(cursor.getString(1));
			tilevec.add(cursor.getString(2));
			tilevec.add(cursor.getString(3));
			tilevec.add(cursor.getString(4));
			}
		return tilevec;
		}
    public boolean doesPlayerExist(String username){
    	String bool="";
		SQLiteDatabase db = this.getReadableDatabase();	
		String doesPlayerExistQuery="SELECT EXISTS(SELECT 1 FROM player_table WHERE user_id='"+username+"')";
		Log.d("query",doesPlayerExistQuery);
		Cursor cursor = db.rawQuery(doesPlayerExistQuery, null);
		while(cursor.moveToNext()) {bool=cursor.getString(0);}
		if(bool.equals("1")){return true;}
		return false;
		}
	}