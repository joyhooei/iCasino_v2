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

import java.io.File;
import java.io.FileOutputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Date;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.Request.GraphUserCallback;
import com.facebook.android.DialogError;
import com.facebook.android.Facebook;
import com.facebook.android.FacebookError;
import com.facebook.android.Facebook.DialogListener;
import com.facebook.model.GraphUser;
import com.facebook.widget.WebDialog;
import com.facebook.widget.WebDialog.OnCompleteListener;

import com.game.simple.R;

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
import android.sax.StartElementListener;
import android.util.Base64;
import android.util.Log;
import android.view.WindowManager;
import android.widget.TextView;
import android.widget.Toast;

public class Game3 extends Cocos2dxActivity{
	public static Facebook fb;
	public static Uri selectedImage;
	public static Uri cropedImage;
	public static Uri cameraImage;
	public String imageFilePath=" ";
	public String cropedImagePath;
	private static final int PICK_FROM_FILE = 0;
	private static final int PIC_CROP = 1;
	private static final int CAMERA_CAPTURE = 2;
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		printKeyHash();
		this.self = this;
	}
	  @Override
	    public void onActivityResult(int requestCode, int resultCode, Intent data) {
	        super.onActivityResult(requestCode, resultCode, data);
	       
	        if(resultCode!=RESULT_OK)
	        {
	        	return;
	        }
	        switch (requestCode) 
	        { 
	        case PICK_FROM_FILE:
				selectedImage = data.getData();
				cropImage(selectedImage);
				break;
			case PIC_CROP:
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
    	    String errorMessage = "Whoops - your device doesn't support the crop action!";
    	    Toast toast = Toast.makeText(this, errorMessage, Toast.LENGTH_SHORT);
    	    toast.show();
    	}
    }

    public static void camera()
    {
    	try {
    	    //use standard intent to capture an image
    	    Intent captureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
    	    //we will handle the returned data in onActivityResult
    	    self.startActivityForResult(captureIntent, CAMERA_CAPTURE);
    	}
    	catch(ActivityNotFoundException anfe){
    	    //display an error message
    	    String errorMessage = "Whoops - your device doesn't support capturing images!";
    	    Toast toast = Toast.makeText(self, errorMessage, Toast.LENGTH_SHORT);
    	    toast.show();
    	}
    }
    
    public static void loginFB()
    {
    	 
			    Log.d("FACEBOOK", "performFacebookLogin");
			    final Session.NewPermissionsRequest newPermissionsRequest = new Session.NewPermissionsRequest(self, Arrays.asList("email"));
			    Session openActiveSession = Session.openActiveSession(self, true, new Session.StatusCallback()
			    {
			        @Override
			        public void call(Session session, SessionState state, Exception exception)
			        {
			            Log.d("FACEBOOK", "call");
			            boolean isFetching = false;
						if (session.isOpened() && !isFetching)
			            {
			                Log.d("FACEBOOK", "if (session.isOpened() && !isFetching)");
			                isFetching = true;
			                session.requestNewReadPermissions(newPermissionsRequest);
			                Request getMe = Request.newMeRequest(session, new GraphUserCallback()
			                {
			                    @Override
			                    public void onCompleted(GraphUser user, Response response)
			                    {
			                        Log.d("FACEBOOK", "onCompleted");
			                        if (user != null)
			                        {
			                            Log.d("FACEBOOK", "user != null");
			                            org.json.JSONObject graphResponse = response.getGraphObject().getInnerJSONObject();
			                            String email = graphResponse.optString("email");
			                            String id = graphResponse.optString("id");
			                            String facebookName = user.getUsername();
			                            if (email == null || email.length() < 0)
			                            {
			                                return;
			                            }
			                        }
			                    }
			                });
			                getMe.executeAsync();
			            }
			            else
			            {
			                if (!session.isOpened())
			                    Log.d("FACEBOOK", "!session.isOpened()");
			                else
			                    Log.d("FACEBOOK", "isFetching");

			            }
			        }
			    });
		  }
    private void printKeyHash(){
        // Add code to print out the key hash
        try {
            PackageInfo info = getPackageManager().getPackageInfo(
                    "com.game.sample", 
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
    	Intent inviteFB = new Intent(self,Facebook_fragment.class);
    	self.startActivity(inviteFB);
    }
	  
}
