package com.game.simple;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;

public class Facebook_fragment extends FragmentActivity {
	private Face_book mainFragment;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);

	    if (savedInstanceState == null) {
	        // Add the fragment on initial activity setup
	        mainFragment = new Face_book();
	        getSupportFragmentManager()
	        .beginTransaction()
	        .add(android.R.id.content, mainFragment)
	        .commit();
	    } else {
	        // Or set the fragment from restored state info
	        mainFragment = (Face_book)getSupportFragmentManager()
	        .findFragmentById(android.R.id.content);
	    }
	}

	
}

