/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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
package com.game.simple;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Timer;
import java.util.TimerTask;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.mime.MultipartEntityBuilder;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.entity.mime.content.StringBody;
import org.apache.http.impl.client.DefaultHttpClient;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.Request.GraphUserCallback;
import com.facebook.android.Facebook;
import com.facebook.model.GraphUser;
import com.facebook.widget.WebDialog;
import com.facebook.widget.WebDialog.OnCompleteListener;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.CursorLoader;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.content.pm.PackageManager.NameNotFoundException;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Base64;
import android.util.Log;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.Toast;

public class Game3 extends Cocos2dxActivity{
	public static Facebook fb;
	public static Uri selectedImage;
	public static Uri cropedImage;
	public static Uri cameraImage;
	public String imageFilePath=" ";
	public static String cropedImagePath;
	private static final int PICK_FROM_FILE = 0;
	private static final int PIC_CROP = 1;
	private static final int CAMERA_CAPTURE = 2;
	public static String url = "http://192.168.1.88:8282/Uploader/Upload";
	static Timer t;
	static TimerTask reconnect;
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		printKeyHash();
		this.self=this;
		
	}
	  @Override
	    public void onActivityResult(int requestCode, int resultCode, Intent data) {
	        super.onActivityResult(requestCode, resultCode, data);
	        if (Session.getActiveSession() != null)
	            Session.getActiveSession().onActivityResult(
	                this,
	                requestCode,
	                resultCode,
	                data);
	        
	       ////////////////////image////////////////////
	        if(resultCode!=RESULT_OK)
	        {
	        	return;
	        }
	        switch (requestCode) 
	        { 
	        case PICK_FROM_FILE:
	        	if(data==null)
				{
					Log.e("PICK_FROM_FILE","NULL");
					return;
				}
				selectedImage = data.getData();
				
				cropImage(selectedImage);
				break;
			case PIC_CROP:
				if(data==null)
				{
					return;
				}
				Bundle extras = data.getExtras();
				Bitmap thePic = extras.getParcelable("data");
				Boolean isSDPresent = android.os.Environment.getExternalStorageState().equals(android.os.Environment.MEDIA_MOUNTED);
				if(isSDPresent)
				{
				  cropedImagePath = Environment.getExternalStorageDirectory().toString()+"/DCIM/avatar.jpeg";
				}
				else
				{
					cropedImagePath = "mnt/emmc/avata.jpeg";
				}	
				Log.e("---------------path",cropedImagePath);
				FileOutputStream out = null;
				try {
				       out = new FileOutputStream(cropedImagePath);
				       thePic.compress(Bitmap.CompressFormat.JPEG, 90, out);
				} catch (Exception e) {
				    e.printStackTrace();
				} finally {
				       try{
				           out.close();
				       } catch(Throwable ignore) {}
				}
				
				break;
			case CAMERA_CAPTURE:
				cameraImage= data.getData();
				if(cameraImage==null)
				{
					Log.e("CAMERA_CAPTURE","NULL");
					return;
				}
				cropImage(cameraImage);
				break;
			default:
				break;
			}
	   
	    }

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// Game3 should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
    private static Activity self = null;
   
 
    public static void openImage()
    {
    	//---timer---//
    	//StartReConnect();
    	//-----------//
    	Intent intent = new Intent();
        intent.setType("image/*");
        intent.setAction(Intent.ACTION_GET_CONTENT);
        intent.putExtra("return-data", true);
        self.startActivityForResult(Intent.createChooser(intent, "Complete action using"),PICK_FROM_FILE);	   
    }
    private static native void getFilePath(String path);
    public String getRealPathFromURI(Uri contentUri) {
    	 String[] proj = { MediaStore.Images.Media.DATA };
    	    CursorLoader loader = new CursorLoader(self, contentUri, proj, null, null, null);
    	    Cursor cursor = loader.loadInBackground();
    	    int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
    	    cursor.moveToFirst();
    	    return cursor.getString(column_index);
    }
    public void cropImage(Uri pic)
    {
    	
    	if(pic==null)
    	{
    		return;
    		
    	}
    	try {
    		Intent cropIntent = new Intent("com.android.camera.action.CROP"); 
    	    //indicate image type and Uri
    	cropIntent.setDataAndType(pic, "image/*");
    	    //set crop properties
    	cropIntent.putExtra("crop", "true");
    	    //indicate aspect of desired crop
    	cropIntent.putExtra("aspectX", 1);
    	cropIntent.putExtra("aspectY", 1);
    	    //indicate output X and Y
    	cropIntent.putExtra("outputX", 256);
    	cropIntent.putExtra("outputY", 256);
    	    //retrieve data on return
    	cropIntent.putExtra("return-data", true);
    	    //start the activity - we handle returning in onActivityResult
    	self.startActivityForResult(cropIntent, PIC_CROP);

    	}
    	catch(ActivityNotFoundException anfe){
    	    //display an error message
    	    String errorMessage = "Điện thoại không hỗ trợ !";
    	    Toast toast = Toast.makeText(this, errorMessage, Toast.LENGTH_SHORT);
    	    toast.show();
    	}
    
    }

    public static void camera()
    {
 
    	//---timer---//
    	//StartReConnect();
    	//-----------//
    	try {
    	    //use standard intent to capture an image
    	    Intent captureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
    	    //we will handle the returned data in onActivityResult
    	    self.startActivityForResult(captureIntent, CAMERA_CAPTURE);
    	}
    	catch(ActivityNotFoundException anfe){
    	    //display an error message
    	    String errorMessage = "Điện thoại không hỗ trợ !";
    	    Toast toast = Toast.makeText(self, errorMessage, Toast.LENGTH_SHORT);
    	    toast.show();
    	}
    	
    }
    ////////////////////SMS////////////////////////
    public static void sendSMS(String phoneNumber, String mess)
    {	
    	//---timer---//
    	//StartReConnect();
    	//-----------//
    	
    	Uri uri = Uri.parse("smsto:"+phoneNumber);   
    	Intent it = new Intent(Intent.ACTION_SENDTO, uri);   
    	it.putExtra("sms_body",mess); 
    	it.putExtra("exit_on_sent",true);
    	self.startActivity(it);  
        
     }
////////////////////URL////////////////////////
    public static void openURL (String url) {
        Intent aIntent = new Intent (Intent.ACTION_VIEW);
        aIntent.setData(Uri.parse(url));
        self.startActivity(aIntent);
       
    }
////////////////////EMAIL////////////////////////
    public static void sendEmail(String address, String subject, String content)
    {
    	//---timer---//
    	//StartReConnect();
    	//-----------//
    	String [] _address ={address.toString()};
    	Intent email = new Intent(Intent.ACTION_SEND);
    	email.putExtra(Intent.EXTRA_EMAIL, _address);		  
    	email.putExtra(Intent.EXTRA_SUBJECT, subject);
    	email.putExtra(Intent.EXTRA_TEXT,content);
    	email.setType("message/rfc822");
    	self.startActivity(Intent.createChooser(email, "Choose an Email client :"));
       	
    }
    ///////////////////FACEBOOK///////////////////////
    public static void loginFB()
    {
    	self.runOnUiThread(new Runnable() {
			  public void run() {
    	
    	Session.openActiveSession(self, true, new Session.StatusCallback() {
  		  
 		   
		      // callback when session changes state
		      @Override
		      public void call(Session session, SessionState state, Exception exception) {
		        if (session.isOpened()) {

		          // make request to the /me API
		          Request.newMeRequest(session, new Request.GraphUserCallback() {

		            // callback after Graph API response with user object
		            @Override
		            public void onCompleted(GraphUser user, Response response) {
		              if (user != null) {
		                Log.e("Facebook","Login Success !");
		                Log.e("Username: ",user.getName());
		                Log.e("id: ",user.getId());
		                String email = user.getProperty("email").toString();
		                Log.e("Email: ",email);
		                Toast.makeText(self.getApplicationContext(), 
                                user.getName()+" đã đăng nhập thành công ! ", 
                                Toast.LENGTH_SHORT).show();
		              }
		            }
		          }).executeAsync();
		        }
		      }
		    });
		  }
    	});
    }
    private void printKeyHash(){
        // Add code to print out the key hash
        try {
            PackageInfo info = getPackageManager().getPackageInfo(
                    "com.game.simple", 
                    PackageManager.GET_SIGNATURES);
            for (Signature signature : info.signatures) {
                MessageDigest md = MessageDigest.getInstance("SHA");
                md.update(signature.toByteArray());
                Log.d("KeyHash:", Base64.encodeToString(md.digest(), Base64.DEFAULT));
                }
        } catch (NameNotFoundException e) {
            Log.d("KeyHash:", e.toString());
        } catch (NoSuchAlgorithmException e) {
            Log.d("KeyHash:", e.toString());
        }
    }
    public static void inviteFB()
    {
    	
    	self.runOnUiThread(new Runnable() {
			  public void run() {
				  if (Session.getActiveSession() != null && Session.getActiveSession().isOpened()) {
					///
					  Bundle params = new Bundle();
					    params.putString("message", "Let's play iCasino !");
					    params.putString("data",
					            "{\"badge_of_awesomeness\":\"1\"," +
							            "\"social_karma\":\"5\"}");
					    WebDialog requestsDialog = (
					        new WebDialog.RequestsDialogBuilder(self,
					            Session.getActiveSession(),
					            params))
					            .setOnCompleteListener(new OnCompleteListener() {

					                @Override
					                public void onComplete(Bundle values,
					                    FacebookException error) {
					                    if (error != null) {
					                        if (error instanceof FacebookOperationCanceledException) {
					                            Toast.makeText(self.getApplicationContext(), 
					                                "Hủy mời!", 
					                                Toast.LENGTH_SHORT).show();
					                        } else {
					                            Toast.makeText(self.getApplicationContext(), 
					                                "Hủy", 
					                                Toast.LENGTH_SHORT).show();
					                        }
					                    } else {
					                        final String requestId = values.getString("request");
					                        if (requestId != null) {
					                            Toast.makeText(self.getApplicationContext(), 
					                                "Đã mời bạn bè !",  
					                                Toast.LENGTH_SHORT).show();
					                        } else {
					                            Toast.makeText(self.getApplicationContext(), 
					                                "Hủy yêu cầu !", 
					                                Toast.LENGTH_SHORT).show();
					                        }
					                    }   
					                }

					            })
					            .build();
					    requestsDialog.show();
				  }
		     
		        else {

		            loginFB();
		        }
			  }
    	});	  
  }

public static void hideKeyboard() {
  	  if (self.getCurrentFocus() != null) {
  	   InputMethodManager inputMethodManager = (InputMethodManager) self.getSystemService(INPUT_METHOD_SERVICE);
  	   inputMethodManager.hideSoftInputFromWindow(self.getCurrentFocus()
  	     .getWindowToken(), 0);
  	  }
  	 }
  
public static void uploadAvatar(final String token)
  {
	//---timer---//
	//StartReConnect();
	//-----------//
	 self.runOnUiThread(new Runnable() {
		  public void run() {
			  if(cropedImagePath==null)
			  {
				  Toast.makeText(self.getApplicationContext(), 
                          "Chưa chọn ảnh !", 
                          Toast.LENGTH_SHORT).show();
		    		 return ;
			  }
			  if(cropedImagePath.compareTo(" ")==0)
		    	{
		    		 
				  Toast.makeText(self.getApplicationContext(), 
                          "Chưa chọn ảnh !", 
                          Toast.LENGTH_SHORT).show();
		    		 return ;
		    	}
			  else
			  {
		    	HttpClient httpClient = new DefaultHttpClient();
				HttpPost httpPostRequest = new HttpPost(url);
				try {

					File file = new File(cropedImagePath);
					FileBody bin = new FileBody(file);
					StringBody tok = new StringBody(token);
					StringBody imageType = new StringBody("jpg");
					MultipartEntityBuilder multiPartEntityBuilder = MultipartEntityBuilder.create();
					multiPartEntityBuilder.addPart("token", tok);
					multiPartEntityBuilder.addPart("imageType",imageType);
					multiPartEntityBuilder.addPart("media", bin);
					httpPostRequest.setEntity(multiPartEntityBuilder.build());

					// Execute POST request to the given URL
					HttpResponse httpResponse = null;
					httpResponse = httpClient.execute(httpPostRequest);
					// receive response as inputStream
					InputStream inputStream = null;
					inputStream = httpResponse.getEntity().getContent();
					
					Log.e("--upload", "Upload complete");
					Toast.makeText(self.getApplicationContext(), 
                            "Upload thành công!", 
                            Toast.LENGTH_SHORT).show();
					String result="";
					if (inputStream != null)
						result = convertInputStreamToString(inputStream);
					else
						result = " ";
					
					Log.e("upload",result);
					setlinkAvata(result);
					cropedImagePath=" ";
					
				} catch (Exception e) {

					Log.e("--Upload--","ko the upload ");
					Toast.makeText(self.getApplicationContext(), 
                            "Có lỗi trong quá trình upload!", 
                            Toast.LENGTH_SHORT).show();
				}
			  }//else
		  }
		});
	//---timer---//
	 stopTimer();
 	//-----------//
  }
private static native String setlinkAvata(String link);
private static String convertInputStreamToString(InputStream inputStream)
		throws IOException {
	BufferedReader bufferedReader = new BufferedReader(
			new InputStreamReader(inputStream));
	String line = "";
	String result = "";
	while ((line = bufferedReader.readLine()) != null)
		result += line;
	inputStream.close();
	return result;

}
private static native void Update();
private void onSessionStateChange(Session session, SessionState state, Exception exception) {
    if (state.isOpened()) {
        Log.e("FACEBOOK","Đã login! ");
    } else if (state.isClosed()) {
    	Log.e("FACEBOOK","Đã logout! ");
    }
    
}
    //// ---timer-- ///}
private static void startTimer()
{
	t = new Timer();
	reconnect = new TimerTask() {
		
		@Override
		public void run() {
			Update();
			Log.e("--update--","up");
		}
	};
	t.scheduleAtFixedRate(reconnect, 0, 5000);
}
private static void stopTimer()
{
	Log.e("--update--","stop");
	if(t!=null)
		t.cancel();
	t=null;
	if(reconnect!=null)
		reconnect=null;
	
}
	
@Override
protected void onPause() {
	startTimer();
	super.onPause();
}
@Override
protected void onResume() {
	stopTimer();
	super.onResume();
}









	
}///main