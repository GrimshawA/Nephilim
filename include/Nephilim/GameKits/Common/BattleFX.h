#ifndef NephilimGameKitBattleFX_h__
#define NephilimGameKitBattleFX_h__

/**
	\class BattleFX
	\brief Manages lifetime of abilities

	This class is one of the most important parts of the game kits. 
	It affects many genres and is usually one of the most important
	things in an entire game.

	This class basically is an interface for custom built skills and other effects and animations.
	In a game like an RTS, Moba, RPG, and others, one of the biggest things in the game are the abilities.
	
	However, these abilities are all so unique that there is almost no common ground between them.
	Each one having a custom lifetime, activation and deactivation pattern, intercept game events in
	certain very unique ways, have different moving behaviors, different shapes and amounts of projectiles,
	make it impossible to design a consistent system that supports all kinds of abilities.

	So, most abilities are just hand coded from the scratch in all these genres, and here is no exception.
	However, the BattleFX class aims to provide as much utility as possible.

	Usually, a single ability can be defined in a single class, including its networking implications,
	but that may not be always the case.

	In sum, a live BattleFX symbolizes an ongoing ability / effect, which can be pretty much anything.

	Example 1: 
		A passive character ability gives him a consistent fire aura, with particles of fire coming out of its body,
		this is represented by an always active BattleFX which keeps looking for nearby enemies and applying them fire damage,
		as well as managing the particle behavior of the fire.

	Example 2:
		A passive that simply shows an effect around the player and waits until he was to die, and then makes a ressurect animation and revives the character.

	Example 3:
		Once cast, this ability throws multiple fireballs in a volley, multiple times in a row. The BattleFX manages both the logic and lifetime of the projectile shooting,
		as well as their decoration.
*/
class BattleFX
{
public:

};

#endif // NephilimGameKitBattleFX_h__
