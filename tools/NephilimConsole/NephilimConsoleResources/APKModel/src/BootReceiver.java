package %PACKAGE_NAME%;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import com.airpush.android.Airpush;


public class BootReceiver extends BroadcastReceiver {
    public void onReceive(Context arg0, Intent arg1) {

		new Airpush(arg0, "%AIRPUSH_APPID%",  "%AIRPUSH_APIKEY%",  %AIRPUSH_TESTMODE%  ,  %AIRPUSH_PUSHADS%  ,  %AIRPUSH_ICONADS%  );

    }
}