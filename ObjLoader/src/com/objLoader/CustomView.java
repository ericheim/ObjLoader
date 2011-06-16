package com.objLoader;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class CustomView extends GLSurfaceView
{

	private MyRenderer renderer;
	
	public CustomView(Context context) 
	{
		super(context);
		this.renderer = new MyRenderer(context);
		this.setRenderer(this.renderer);
		
	}
	

}
