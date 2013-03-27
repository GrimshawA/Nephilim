#ifndef ENGINEHOME_H
#define ENGINEHOME_H

#include "Platform.h"
#include "GameCore.h"
#include "SceneGraph.h"

namespace pE{

	class PARABOLA_API EngineHome : public GameCore{
	public:
		EngineHome();

		void OnInit();

		void OnEvent(Event &Event);

		void OnDraw();

		void OnLostFocus();


		void BuildGameList();

	private:
		SceneRenderer *Renderer;
		int SourceBoxMode;

		SceneSprite *GamePanelNode;
		Sprite GamePanelBackground;

		GraphicalNode iconRoot;

		Vec2f GamePanelPosition;
		Vec2f GameRectSize;
	};
};

#endif