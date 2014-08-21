package com.game.simple;

import java.util.Arrays;

import javax.crypto.spec.IvParameterSpec;

import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;
import com.facebook.android.DialogError;
import com.facebook.android.Facebook;
import com.facebook.android.Facebook.DialogListener;
import com.facebook.android.FacebookError;
import com.facebook.model.GraphUser;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.LoginButton;
import com.facebook.widget.ProfilePictureView;
import com.facebook.widget.WebDialog;
import com.facebook.widget.WebDialog.OnCompleteListener;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class Face_book extends Fragment{

	
	private static Face_book self = null;
	private static final String TAG = "MainFragment";
	private UiLifecycleHelper uiHelper;
	private ProfilePictureView ivProfile;
	private TextView tvName;
	private Button btnShare;
	private Button btnInvite;
	private LoginButton btnLogin;
	private TextView tvID;

	private TextView tvEmail;
	private Session.StatusCallback callback = new Session.StatusCallback() {
	    @Override
	    public void call(Session session, SessionState state, Exception exception) {
	        onSessionStateChange(session, state, exception);
	    }
	};
	private Session.StatusCallback statusCallback = 
		    new SessionStatusCallback();
		
		private void onClickLogin() {
		    Session session = Session.getActiveSession();
		    if (!session.isOpened() && !session.isClosed()) {
		        session.openForRead(new Session.OpenRequest(this)
		            .setPermissions(Arrays.asList("public_profile"))
		            .setCallback(statusCallback));
		    } else {
		        Session.openActiveSession(getActivity(), this, true, statusCallback);
		        
		    }
		}
		
		private class SessionStatusCallback implements Session.StatusCallback {
		    @Override
		    public void call(Session session, SessionState state, Exception exception) {
		            // Respond to session state changes, ex: updating the view
		    }
		}
	@Override
	public View onCreateView(LayoutInflater inflater, 
	        ViewGroup container, 
	        Bundle savedInstanceState) {
	    View view = inflater.inflate(R.layout.face_book, container, false);
	    uiHelper = new UiLifecycleHelper(getActivity(), callback);
	    uiHelper.onCreate(savedInstanceState);
	    this.self = this;
	   btnLogin = (LoginButton) view.findViewById(R.id.btnLogin);
	   btnLogin.setFragment(this);
	   btnLogin.setFragment(this);
	   btnLogin.setReadPermissions(Arrays.asList("user_likes", "user_status"));
	    
	   ivProfile = (ProfilePictureView)view.findViewById(R.id.ivProfile);
	   tvName = (TextView)view.findViewById(R.id.tvName);
	   tvID = (TextView)view.findViewById(R.id.tvUserID);
	  
	   tvEmail = (TextView)view.findViewById(R.id.tvEmail);
	
	    //share
	    
	    btnShare = (Button)view.findViewById(R.id.btnShare);
	    btnInvite = (Button)view.findViewById(R.id.btnInvite);
	    Session ses = Session.getActiveSession();
	    if(ses.isOpened())
	    {
	    	btnShare.setVisibility(View.VISIBLE);
        	btnInvite.setVisibility(View.VISIBLE);
	    }
	    else {
	    	btnShare.setVisibility(View.INVISIBLE);
        	btnInvite.setVisibility(View.INVISIBLE);
		}
	    	
	    btnShare.setOnClickListener(new OnClickListener() {
		
		
			public void onClick(View v) {
				// TODO Auto-generated method stub
				shareFB();
			}
		});
	    
	    //invite
	    
	    btnInvite.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v) {
				// TODO Auto-generated method stub
				inviteFB();
			}
		});
	    
	    //sms
	    ImageButton btnSms = (ImageButton)view.findViewById(R.id.btnSms);
	    btnSms.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v) {
				// TODO Auto-generated method stub
				sendSMS("0985610321", "Let's play iCasino");
			}
		});
	    
	    //gmail
	    ImageButton btnGmail = (ImageButton)view.findViewById(R.id.btnGmail);
	    btnGmail.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v) {
				// TODO Auto-generated method stub
				sendEmail("", "Play iCasino", "Let's play iCasino");
			}
		});
	    
	    return view;
	}
	private void onSessionStateChange(Session session, SessionState state, Exception exception) {
		if (state.isOpened()) {
		       // Log.i("Logged in...");
		        // make request to the /me API
			btnShare.setVisibility(View.VISIBLE);
        	btnInvite.setVisibility(View.VISIBLE);
        
		        Request.newMeRequest(session, new Request.GraphUserCallback() {
		            // callback after Graph API response with user object
		            @Override
		            public void onCompleted(GraphUser user, Response response) {
		                if (user != null) {
		                	ivProfile.setProfileId(user.getId());
		                   // Log.d("user.getName : " + user.getName());
		                	tvName.setText(user.getName());
		                   // Log.d("user.getUsername : " + user.getUsername());
		                	tvID.setText(user.getId());
		                  //  Log.d("user.getId : " + user.getId());
		                	
		                    String email = user.getProperty("email").toString();
		                   // Log.d("user.email : " + email);
		                    tvEmail.setText(email);  
		                     
		                }
		                else
		                {
		                	ivProfile.setProfileId(null);
		                	tvName.setText("");
		                	tvID.setText("");
		                	tvEmail.setText("");
		                	btnShare.setVisibility(Button.INVISIBLE);
		                	btnInvite.setVisibility(Button.INVISIBLE);  
		                }
		            }

				
		        }).executeAsync();
		    } else if (state.isClosed()) {
		    	ivProfile.setProfileId(null);
            	tvName.setText("");
            	tvID.setText("");
            	tvEmail.setText("");
            	btnShare.setVisibility(Button.INVISIBLE);
            	btnInvite.setVisibility(Button.INVISIBLE);
		    }
	}
	@Override
	public void onResume() {
	    super.onResume();
	    Session session = Session.getActiveSession();
	    if (session != null &&
	           (session.isOpened() || session.isClosed()) ) {
	        onSessionStateChange(session, session.getState(), null);
	    }
	    uiHelper.onResume();
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
	    super.onActivityResult(requestCode, resultCode, data);
	    //uiHelper.onActivityResult(requestCode, resultCode, data);
	    uiHelper.onActivityResult(requestCode, resultCode, data, new FacebookDialog.Callback() {
	        @Override
	        public void onError(FacebookDialog.PendingCall pendingCall, Exception error, Bundle data) {
	            Log.e("Activity", String.format("Error: %s", error.toString()));
	        }

	        @Override
	        public void onComplete(FacebookDialog.PendingCall pendingCall, Bundle data) {
	            Log.i("Activity", "Success!");
	        }
	    });
	}

	@Override
	public void onPause() {
	    super.onPause();
	    uiHelper.onPause();
	}

	@Override
	public void onDestroy() {
	    super.onDestroy();
	    uiHelper.onDestroy();
	}

	@Override
	public void onSaveInstanceState(Bundle outState) {
	    super.onSaveInstanceState(outState);
	    uiHelper.onSaveInstanceState(outState);
	}

	private void shareFB()
	{
		FacebookDialog shareDialog = new FacebookDialog.ShareDialogBuilder(getActivity())
        .setLink("https://developers.facebook.com/apps/650092181748441")
        .setCaption("Let's play iCasino with me !!!")
        .setName("Play iCasino now!")
        .setDescription("Let's play iCasino with me !!!")
        .setPicture("http://cdn.tain.com/clients/tain/www/wp-content/uploads/2010/07/casino_large.jpg")	
        .build();
uiHelper.trackPendingDialogCall(shareDialog.present());
	}
	 private void inviteFB()
	  {
		    Bundle params = new Bundle();
		    params.putString("message", "Test inviteeeeee");
		    params.putString("data",
		            "{\"badge_of_awesomeness\":\"1\"," +
		            "\"social_karma\":\"5\"}");
		   WebDialog requestsDialog = (
		        new WebDialog.RequestsDialogBuilder(getActivity(),
		            Session.getActiveSession(),
		            params))
		            .setOnCompleteListener(new OnCompleteListener() {

		                @Override
		                public void onComplete(Bundle values,
		                    FacebookException error) {
		                    if (error != null) {
		                        if (error instanceof FacebookOperationCanceledException) {
		                            Toast.makeText(getActivity(), 
		                                "Request cancelled", 
		                                Toast.LENGTH_SHORT).show();
		                        } else {
		                            Toast.makeText(getActivity(), 
		                                "Network Error", 
		                                Toast.LENGTH_SHORT).show();
		                        }
		                    } else {
		                        final String requestId = values.getString("request");
		                        if (requestId != null) {
		                            Toast.makeText(getActivity(), 
		                                "Request sent",  
		                                Toast.LENGTH_SHORT).show();
		                        } else {
		                            Toast.makeText(getActivity(), 
		                                "Request cancelled", 
		                                Toast.LENGTH_SHORT).show();
		                        }
		                    }   
		                }

						

		            })
		            .build();
		    requestsDialog.show();
		}
	 public static void sendSMS(String phoneNumber, String mess)
	    {
	    	Uri uri = Uri.parse("smsto:"+phoneNumber);   
	    	Intent it = new Intent(Intent.ACTION_SENDTO, uri);   
	    	it.putExtra("sms_body",mess); 
	    	it.putExtra("exit_on_sent",true);
	    	self.startActivity(it);  
	        
	     }
	    public static void openURL (String url) {
	        Intent aIntent = new Intent (Intent.ACTION_VIEW);
	        aIntent.setData(Uri.parse(url));
	        self.startActivity(aIntent);
	       
	    }
	    public static void sendEmail(String address, String subject, String content)
	    {
	    	String [] _address ={address.toString()};
	    	Intent email = new Intent(Intent.ACTION_SEND);
	    	email.putExtra(Intent.EXTRA_EMAIL, _address);		  
	    	email.putExtra(Intent.EXTRA_SUBJECT, subject);
	    	email.putExtra(Intent.EXTRA_TEXT,content);
	    	email.setType("message/rfc822");
	    	self.startActivity(Intent.createChooser(email, "Choose an Email client :"));
	       	
	    }
}
