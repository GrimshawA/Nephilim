#ifndef PARABOLA_CONTENTLIST_H
#define PARABOLA_CONTENTLIST_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

class ContentBank;
class ContentLoader;

namespace ContentType{
	enum Type{
		TEXTURE = 0,
		IMAGE,
		PARTICLESYSTEM,
		SOUND,
		LOCALIZATION,

	};

	enum Source{
		FILE = 0,
		PACKAGE,
		MEMORY
	};
}

/**
	\ingroup Content
	\class ContentList
	\brief Represents a list of resources and details about them

	This class is used to store a list of resources, and how they are supposed to be loaded.

	Just note you can't load anything with this class, it must be used in pair with a ContentBank.

	Lets say you have a ContentList per each level of your game, or even each streaming sector,
	You would be able to load and unload resources from your ContentBank at will, thanks to these lists.

	Also, these lists can be loaded from a text file, which really helps managing resources.

	ContentList resource entries support internationalization by default.
*/
class PARABOLA_API ContentList{
public:
	/// Creates an yet empty list of content
	/// Please note that only a named ContentList will be recorded by ContentBank.
	/// Being recorded means that you can get rid of the content list after inserting it into the ContentBank.
	/// Then you can load/unload at will.
	ContentList();

	/// Creates an yet empty list of content
	ContentList(const String &name);

private:
	friend class ContentBank;
	friend class ContentLoader;
	/// Locks this content list, to prevent removal - Bank utilities
	void lock();
	/// Unlocks this content list, allowing removal - Bank utilities
	void unlock();
	/// Check if it is locked
	bool locked();

	bool myLocked;

	/// The prefix is preappended to all resources added from this list
	/// This prefix is an empty string by default
	String myPrefix;
};

PARABOLA_NAMESPACE_END
#endif