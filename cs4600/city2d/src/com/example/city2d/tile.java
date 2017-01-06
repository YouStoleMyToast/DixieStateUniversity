package com.example.city2d;

public class tile{
	private String mName;
	private int mId;
	private int mX;
	private int mY;
	private int mType;
	private int mStatus;
	private int mCost;
	private int mJob;
	private int mStarttime;

	public String getTileName() {return mName;}
	public void setTileName(String mName) {this.mName = mName;}
	
	public int getTileId() {return mId;}
	public void setTileId(int mId) {this.mId = mId;}
	
	public int getTileType() {return mType;}
	public void setTileType(int type) {this.mType=type;}
	
	public int getTileStatus() {return mStatus;}
	public void setTileStatus(int status) {this.mStatus = status;}
	
	public int getTileCost() {return mCost;}
	public void setTileCost(int cost) {this.mCost = cost;}
	
	public int getTileX() {return mX;}
	public void setTileX(int mX) {this.mX = mX;}
	
	public int getTileY() {return mY;}
	public void setTileY(int mY) {this.mY = mY;}
	
	public int getTileJob() {return mJob;}
	public void setTileJob(int mJob) {this.mJob = mJob;}
	
	public int getTileStarttime() {return mStarttime;}
	public void setTileStarttime(int mStarttime) {this.mStarttime = mStarttime;}
}