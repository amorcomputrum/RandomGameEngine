#pragma once

#include "RGE/Window/Events/Events.h"

namespace RGE{
	/**
	 * MouseEvent is a struct that stores what button was used and where it happened
	*/
	struct MouseEvent{
		enum Button{
			Left=0,Right=1,Middle=2,Four=3,Five=4,Six=5,Seven=6,Eight=7,NONE=-1
		};
		/**
		 * The button that was used
		*/
		RGE::MouseEvent::Button button;
		/**
		 * The position that it happened
		*/
		int x, y;

		RGE::Event::Type type;
	};
}
