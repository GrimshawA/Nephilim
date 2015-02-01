template<typename T>
ComponentManager* World::getComponentManager()
{
	if (componentManagers.find(std::type_index(typeid(T))) == componentManagers.end())
	{
		componentManagers[std::type_index(typeid(T))] = new ComponentArray<T>();
	}

	return componentManagers[std::type_index(typeid(T))];
}

// -- Copy a component to its manager and bind to entity e
template<typename T>
void World::createComponent(T c, Entity e)
{
	ComponentManager* componentManager = getComponentManager<T>();

	T* component = static_cast<T*>(componentManager->createComponentForEntity(e));
	*component = c;
}

/// Instances a new RenderSystem with type T and initializes it
/// T must be a derived type of RenderSystem
template<typename T>
T* World::createRenderSystem()
{
	RenderSystem* renderSystem = new T();
	registerSystem(renderSystem);
	renderSystem->mRenderer = this->graphicsDevice;
	renderSystem->mContentManager = this->contentManager;
	return static_cast<T*>(renderSystem);
}

template<typename T>
void World::createDefaultComponentManager()
{
	if (componentManagers.find(std::type_index(typeid(T))) != componentManagers.end())
	{
		delete componentManagers[std::type_index(typeid(T))];
		componentManagers.erase(componentManagers.find(std::type_index(typeid(T))));
	}

	componentManagers[std::type_index(typeid(T))] = new ComponentArray<T>();
}

/// Spawns an actor with type T (must be a subclass of Actor)
template<typename T>
T* World::spawnActor()
{
	T* myObj = new T(this);
	myObj->_world = this;

	actors.push_back(myObj);

	return myObj;
}

/// Spawns an actor with type T (must be a subclass of Actor)
template<typename T>
T* World::spawnActor(Vector3D location, Quat orientation)
{
	T* actor = spawnActor<T>();
	actor->setActorLocation(location);
	return actor;
}