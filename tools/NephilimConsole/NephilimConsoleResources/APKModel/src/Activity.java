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
import android.view.WindowManager;
import android.view.MotionEvent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import java.io.IOException;
import android.telephony.gsm.SmsManager;
import android.view.KeyEvent;
import android.view.inputmethod.InputMethodManager;
import android.media.MediaPlayer;
import android.os.Vibrator;
import java.io.File;

%AIRPUSH_IMPORT%

public class %ACTIVITY_CLASS% extends Activity implements SensorEventListener {
	/// Accelerometer related
	private SensorManager mSensorManager;
	private Sensor mAccelerometer;
	private Vibrator mVibrator;
	private static GLSurfaceView mGLView;
	private static %ACTIVITY_CLASS% mGame;
	
	/// Content resolver, for interacting with systems such as SMS
	public static ContentResolver contentResolver;
	/// Asset manager, to get the APK resources
	public static AssetManager assetManager;	

	/// JNI Function - Pass some initial data to C++
	private static native void nativeStorageInfo(String internalData, String externalData, boolean externalDataWritable, boolean externalDataAvailable, String packageName, String activityClassName);
	/// JNI Function - Inform C++ of a key press
	private static native void nativeKeyDown(int keyDown);
	/// JNI Function - Inform C++ of accelerometer detection
	private static native void nativeAccel(float x, float y, float z);
	
	
	/// List assets in a directory. APK resources only. This is called from native code
	public static String[] getAssetList(String path){
		String[] list = null;
		try{	
			list = assetManager.list(path);
		}catch(IOException ioe){
			/// Something went wrong with asset listing. Rare situation, but handle it.
			Log.v("ParabolaEngine", "Asset listing exception: " + ioe.getMessage());
		}
		return list;
	}

	public static void closeActivity(){
		mGame.finish();
		android.os.Process.killProcess(android.os.Process.myPid());
	}
	
	/// JNI Function used to fetch an APK Resource file descriptor. Called from native code
	public static AssetFileDescriptor getAssetFileDescriptor(String assetName){
		AssetFileDescriptor fp = null;
		try{	
			fp = assetManager.openFd(assetName);
		}catch(IOException ioe){
			/// Handle asset loading exception
			Log.v("ParabolaEngine", "Asset file fetch exception: " + ioe.getMessage());
		}
		return fp;
	}
	
	public static boolean createDirectory(String directory)
	{
		return (new File(directory)).mkdir();
	}
	
	// JNI to play music, etc
    public MediaPlayer _music = null;
    public static void playMusic(String fname) {
        Log.v("music_play",fname);
        AssetManager am = mGame.getAssets();
        try {
            AssetFileDescriptor fd = am.openFd(fname);
            mGame._music = new MediaPlayer();
            mGame._music.setDataSource(fd.getFileDescriptor(),fd.getStartOffset(),fd.getLength());
            fd.close();
            mGame._music.setLooping(false);
            mGame._music.prepare();
            mGame._music.start();
        } catch(IOException e) { }
    }
	
	public static void requestFrameRender(){
		mGLView.requestRender();
	}
	
	public static void toggle_keyboard() {
        InputMethodManager mgr = (InputMethodManager)mGame.getSystemService(Context.INPUT_METHOD_SERVICE);
        mgr.toggleSoftInput(InputMethodManager.SHOW_IMPLICIT,0);      
    }
	
	public static void vibrate(long miliseconds)
	{
		mGame.mVibrator.vibrate(miliseconds);
	}


	/// JNI Function to send an SMS through the android device. Called from native code
	public static void sendSMS(String number, String sms){
		SmsManager sm = SmsManager.getDefault();
		sm.sendTextMessage(number, null, sms, null, null);
		ContentValues values = new ContentValues();
		values.put("address", number);
		values.put("body", sms);
		contentResolver.insert(Uri.parse("content://sms/sent"), values);
	}

	/// Keypress event detection. It goes into the engine directly.
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {		
		nativeKeyDown(keyCode);
		if(keyCode == KeyEvent.KEYCODE_BACK)
			return false;
		else
			return super.onKeyDown(keyCode, event);
	}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
		
		mGame = this;
		
        mGLView = new DemoGLSurfaceView(this);
        setContentView(mGLView);
		contentResolver = getContentResolver();
		assetManager = getAssets();

		/// Airpush initialization
		new Airpush(getApplicationContext(), "52201","1337301308105398636",true,true,true);
		
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		/// Accelerometer preparing
		mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		mSensorManager.registerListener(this, mAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);

		mVibrator = (Vibrator) getSystemService(VIBRATOR_SERVICE);
		
		/// Startup information is passed to the engine
		nativeStorageInfo(getFilesDir().getPath(), Environment.getExternalStorageDirectory().getPath(), true, true, getPackageName(), this.getClass().getName());
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
		
		//nativeAccel(x, y, z);		
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// can be safely ignored for this demo
	} 

    static {		 
		/// The native code generated from C++
        System.loadLibrary("%PROJECT_NAME%");    
    }
}

class DemoGLSurfaceView extends GLSurfaceView  {
	
    public DemoGLSurfaceView(Context context) {
        super(context);
		setEGLContextClientVersion(nativeGetGLVersion());
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
			Log.v("ParabolaEngine", "Unhandled touch event");					
		}
	
        return true;
    }

    DemoRenderer mRenderer;

	
   private static native void nativeTouchDown(float x, float y);
   private static native void nativeTouchUp(float x, float y);
   private static native void nativeTouchMove(float x, float y);
   
   public static native int nativeGetGLVersion();
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
    //private static native void nativeDone();
}
