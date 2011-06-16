package com.objLoader;



public class AppLib 
{

	static {
        System.loadLibrary("app");
    }
	
	public static native void renderFrame();
	public static native void resize(int width, int height);
	public static native void onSurfaceCreated(String apkPath);
}
