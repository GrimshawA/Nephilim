#ifndef iOS_Bridge_h__
#define iOS_Bridge_h__

/// Objective-C included header for iOS integration
/// Must be included after other Objective C header files.

#include <string>

/// This function returns to the iOS application the preferred OpenGL ES version.
/// Common values to return are either 1 or 2
int ios_bridge_getGLESVersion()
{
	return 1;
}

/// This function is called by iOS to initialize the engine or to inform it is active again
extern void ios_bridge_initialize();

/// This function is called by iOS to inform the engine to unload itself, however some data can still be kept
void ios_bridge_unload()
{

}

/// This function is called by iOS to inform the engine to completely destroy itself
void ios_bridge_destroy()
{

}

/// This function is called by iOS to inform the system is low on memory, to erase data that is not being needed
void ios_bridge_release_data()
{

}

/// This function is called by iOS to inform the engine that the screen was just touched
/// The function is called once for every touch pressed
/// Research: does older presses pop up too when a new one does?
extern void ios_bridge_touch_pressed(int x, int y, int id);

/// This function is called by iOS to inform the engine that the screen was just touched
/// The function is called once for every touch pressed
/// Research: does older presses pop up too when a new one does?
void ios_bridge_touch_released(int x, int y, int id)
{

}

/// This function is called by iOS to inform the engine that the screen was just touched
/// The function is called once for every touch pressed
/// Research: does older presses pop up too when a new one does?
void ios_bridge_touch_moved(int x, int y, int id)
{

}

/// This function is called by iOS when its time to update the state and draw a frame
extern void ios_bridge_update();

/// This function is called by iOS whenever the device changed orientation
/// If it returns true, the view will adjust to the new orientation as well
bool ios_bridge_should_autorotate()
{
	return true;
}

/// This function is called by iOS whenever the view rect changes
void ios_bridge_set_view_size(float width, float height)
{

}

/// Declared as extern by the engine and defined here by iOS
/// This function returns the total size of the device screen
void ios_bridge_get_screen_size(float &width, float &height)
{
	CGRect screenRect = [[UIScreen mainScreen] bounds];
	CGFloat screenWidth = screenRect.size.width;
	CGFloat screenHeight = screenRect.size.height;
	width = screenWidth;
	height = screenHeight;
}


/// This function is to be included from the Objective-C iOS project
/// It will return the absolute path where all assets can be found
/// Always put all assets in the same directory conveniently named 'assets' and drag them to the XCode project so they are found within the bundle.
std::string getResourcesPath(){
	std::string finalPath;

	NSString * dir = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"assets"];
	finalPath = [dir cStringUsingEncoding:1];
	return finalPath;
}

/// Similar to getResourcesPath()
/// Instead of returning the absolute path to the 'assets' directory within the bundle
/// it returns an absolute path to a file within the bundle directly
/// stub: returning empty string only
std::string getAssetPath(std::string assetName)
{
	std::string finalPath;
	/*NSString * path = [[NSBundle mainBundle] pathForResource: @"assets/ui/mainmenu" ofType: @"rml"];
	FILE *f = fopen([dir2 cStringUsingEncoding:1], "r");
	if(f){
		NSLog(@"FUCK YEAH");
	}
	else{
		NSLog(@"OH NOOOOO");
	}
	NSLog(dir2);

	finalPath = [path cStringUsingEncoding:1];*/
	return finalPath;
}


#endif // iOS_Bridge_h__
