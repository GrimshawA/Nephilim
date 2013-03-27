#ifndef PARABOLA_FACTORY_H
#define PARABOLA_FACTORY_H

#include "Platform.h"
#include <vector>

PARABOLA_NAMESPACE_BEGIN
	
/**

*/
class PARABOLA_API Factory{
public:


protected:
	/// Protected constructor, only usable by inheriting
	Factory();








		Window* CreateWindow();
		SceneRenderer* CreateRenderer(Window* window = NULL);

		void SetPreferredWindow();

		/// Creates a new resource list in the global content manager.
		ResourceList* CreateResourceList(String id);
		/// Destroys all resource lists with name equal to 'id' that it owns
		void DestroyResourceList(String id);
		/// Destroys the specific list if it exists
		void DestroyResourceList(ResourceList *list);

		/// Creates a sound manager binded to a ResourceList
		SoundManager* CreateSoundManager(ResourceList* list);
		void DestroySoundManager(SoundManager *soundManager);

	private:
		vector<Window*> windows;
		vector<SceneRenderer*> renderers;
		vector<ResourceList*> resourceLists;
		vector<SoundManager> soundManagers;
	};

PARABOLA_NAMESPACE_END
#endif