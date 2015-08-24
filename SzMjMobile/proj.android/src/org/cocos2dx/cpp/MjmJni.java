package org.cocos2dx.cpp;

import org.cocos2dx.cpp.AppActivity;

import android.content.Intent;
import android.util.Log;

public class MjmJni {

	public static AppActivity mMainContext;
	
	public static boolean openURL(String packname)
	{
		mMainContext.sendTest();
		return true;
	}
}
