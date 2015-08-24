/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.tencent.mm.sdk.modelmsg.SendMessageToWX;
import com.tencent.mm.sdk.modelmsg.WXMediaMessage;
import com.tencent.mm.sdk.modelmsg.WXTextObject;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class AppActivity extends Cocos2dxActivity 
{
	private static final String WeichatId = "wx323c2e438860301b";
	private IWXAPI api;
	
	 protected void onCreate(Bundle savedState)
	 {
		 super.onCreate(savedState);
		 
		 MjmJni.mMainContext = this;
		 
		 //注册微信
		 regToWX();
		 
		 //其他应用打开
//		 Intent intent = getIntent();
//		 Bundle bundle = intent.getExtras();
//		 if (bundle != null) 
//		 {
//			 String canshu1 = bundle.getString("canshu1");
//			 if (canshu1 != null) 
//			 {
//				 Log.d("test_jni", canshu1);
//			 }
//		 }
	 }
	 
	 private void regToWX()
	 {
		 api = WXAPIFactory.createWXAPI(this, WeichatId, true);
		 api.registerApp(WeichatId);
	 }
	 
	 public void sendTest()
	 {
			Log.d("test", "准备发送");
			
			WXTextObject textObj = new WXTextObject();
			textObj.text = "武汉麻将 好玩的麻将🀄️";

			WXMediaMessage msg = new WXMediaMessage();
			msg.mediaObject = textObj;
			
			msg.description = "武汉麻将 好玩的麻将🀄";

			SendMessageToWX.Req req = new SendMessageToWX.Req();
			req.transaction = buildTransaction("text"); 
			req.message = msg;
			req.scene = SendMessageToWX.Req.WXSceneSession;
			
			api.sendReq(req);
//			finish();
	 }
	 
	 private String buildTransaction(final String type) 
	 {
			return (type == null) ? String.valueOf(System.currentTimeMillis()) : type + System.currentTimeMillis();
		}
}
