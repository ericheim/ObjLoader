package com.objLoader;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.opengl.GLSurfaceView;

public class MyRenderer implements GLSurfaceView.Renderer {
	private Context context;

	public MyRenderer(Context _context) {
		super();
		this.context = _context;
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		AppLib.renderFrame(); 
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		//System.out.println("surface changed");
		
		AppLib.resize(width, height);

	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		//System.out.println("surface created");

		String apkFilePath = null;
		ApplicationInfo appInfo = null;
		PackageManager packMgmr = context.getPackageManager();
		
		try {
			appInfo = packMgmr.getApplicationInfo("com.objLoader", 0);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			throw new RuntimeException("Unable to locate assets, aborting...");
		}
		apkFilePath = appInfo.sourceDir;
		AppLib.onSurfaceCreated(apkFilePath);
		
	}

}
