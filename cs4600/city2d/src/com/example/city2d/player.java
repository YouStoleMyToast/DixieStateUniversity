package com.example.city2d;

public class player{
	private String mUsername;
	private String mPassword;
	private int mXp;
	private int mMoney;
	private int mLevel;
	
	player(String name, String pass){
		mUsername=name;
		mPassword=pass;
	}
	public String getUsername() {return mUsername;}
	public void setUsername(String username) {this.mUsername = username;}
	
	public String getPassword() {return mPassword;}
	public void setPassword(String password) {this.mPassword = password;}
	
	public int getMoney() {return mMoney;}
	public void setMoney(int money) {this.mMoney = money;}
	
	public int getXp() {return mXp;}
	public void setXp(int xp) {this.mXp = xp;}
	
	public int getLevel() {return mLevel;}
	public void setLevel(int level) {this.mLevel = level;}
}
