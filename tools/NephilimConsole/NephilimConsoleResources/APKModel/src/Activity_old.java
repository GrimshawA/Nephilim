package %PACKAGE_NAME%;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.content.ContentValues;
import android.content.ContentResolver;
import android.content.res.AssetManager;
import android.content.res.AssetFileDescriptor;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.net.Uri;
import android.view.MotionEvent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import java.io.IOException;
import android.telephony.gsm.SmsManager;
import android.view.KeyEvent;

%AIRPUSH_IMPORT%

public class %ACTIVITY_CLASS% extends Activity implements SensorEventListener {

	private boolean mInitialized;

	private SensorManager mSensorManager;
	private float mLastX;
	private float mLastY;
	private float mLastZ;
	public static ContentResolver contentResolver;
	public static AssetManager assetManager;
	private Sensor mAccelerometer;

	String mInternalDataPath;
	String mExternalDataPath;

	private final float NOISE = (float) 2.0;

	private static native void nativeStorageInfo(String internalData, String externalData, boolean externalDataWritable, boolean externalDataAvailable);

	public static String[] getAssetList(String path){
		String[] list = null;
		try{	
			list = assetManager.list(path);
			/*for(String s : list){
				Log.v("TEEEEEEEEST", s);
			}*/

		}catch(IOException ioe){
			//Handle exception here, most of the time you will just log it.
			Log.v("ASSETS", "Exception: " + ioe.getMessage());
		}
		return list;
	}

	public static AssetFileDescriptor getAssetFileDescriptor(String assetName){
		AssetFileDescriptor fp = null;
		try{
			fp = assetManager.openFd(assetName);
		}catch(IOException ioe){
			//Handle exception here, most of the time you will just log it.
			Log.v("%ACTIVITY_CLASS%", "Exception: " + ioe.getMessage());
		}
		return fp;
	}

	%ACTIVITY_FEATURE_SENDSMS%

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		
		nativeKeyDown(keyCode);

		/*switch(keyCode)
		{
		    /case KeyEvent.KEYCODE_CAMERA:
		        Log.v("KEYS", "Pressed Camera");
		        return true;
		}*/
		return super.onKeyDown(keyCode, event);
	}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLView = new DemoGLSurfaceView(this);
        setContentView(mGLView);

		contentResolver = getContentResolver();

		//AIRPUSH
		new Airpush(getApplicationContext(), "52201","1337301308105398636",true,true,true);

		mInitialized = false;
		mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);


		nativeStorageInfo(getFilesDir().getPath(), Environment.getExternalStorageDirectory().getPath(), true, true);

		assetManager = getAssets();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
		mSensorManager.unregisterListener(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
    }

	@Override
	public void onSensorChanged(SensorEvent event) {		
		float x = event.values[0];
		float y = event.values[1];
		float z = event.values[2];
		if (!mInitialized) {
			mLastX = x;
			mLastY = y;
			mLastZ = z;	
			mInitialized = true;
		} else {
			float deltaX = Math.abs(mLastX - x);
			float deltaY = Math.abs(mLastY - y);
			float deltaZ = Math.abs(mLastZ - z);
			if (deltaX < NOISE) deltaX = (float)0.0;
			if (deltaY < NOISE) deltaY = (float)0.0;
			if (deltaZ < NOISE) deltaZ = (float)0.0;
			mLastX = x;
			mLastY = y;
			mLastZ = z;	
		
			//nativeAccel(x, y, z);
		}
		
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// can be safely ignored for this demo
	}

    private GLSurfaceView mGLView;

    static {
        System.loadLibrary("%PROJECT_NAME%");
    }


	private static native void nativeKeyDown(int keyDown);
	//private static native void nativeAccel(float x, float y, float z);
}

class DemoGLSurfaceView extends GLSurfaceView  {

	
    public DemoGLSurfaceView(Context context) {
        super(context);
        mRenderer = new DemoRenderer();
        setRenderer(mRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event) {
		switch(event.getAction()){
			case MotionEvent.ACTION_DOWN:
				nativeTouchDown(event.getX(), event.getY());
			break;
			
			case MotionEvent.ACTION_UP:
				nativeTouchUp(event.getX(), event.getY());
			break; 
			
			case MotionEvent.ACTION_MOVE:
				nativeTouchMove(event.getX(), event.getY());
			break;

			default:
			//Log.v("%ACTIVITY_CLASS%", "Unhandled touch event: Multitouch");					
		}
	
        return true;
    }

    DemoRenderer mRenderer;

	
   private static native void nativeTouchDown(float x, float y);
   private static native void nativeTouchUp(float x, float y);
   private static native void nativeTouchMove(float x, float y);
}

class DemoRenderer implements GLSurfaceView.Renderer {
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {	
       
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
		nativeResize(w, h);
		nativeInit();
    }

    public void onDrawFrame(GL10 gl) {
        nativeRender();
    }

   private static native void nativeInit();
   private static native void nativeResize(int w, int h);
   private static native void nativeRender();
}
