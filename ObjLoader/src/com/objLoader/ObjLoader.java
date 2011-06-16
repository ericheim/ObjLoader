package com.objLoader;


import android.app.Activity;
import android.os.Bundle;

public class ObjLoader extends Activity {
	
	private CustomView view;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
    	
        super.onCreate(savedInstanceState);
   
        view = new CustomView(this);
        setContentView(view);
    }
}