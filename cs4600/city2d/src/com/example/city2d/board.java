package com.example.city2d;

public class board{
	private int mTileRowCount=11;
	private int mTileColCount=9;
	private int mTileTotal=(mTileRowCount*mTileColCount);
	public int getTileRowCount(){return mTileRowCount;}
	public void setTileRowCount(int row){this.mTileRowCount=row;}
	public int getTileColCount(){return mTileColCount;}
	public void setTileColCount(int col){this.mTileColCount=col;}
	public int getTileTotal() {return mTileTotal;}
}

