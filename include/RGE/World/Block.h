#pragma once

#include <vector>

#ifndef BLOCKID_NONE
	#define BLOCKID_NONE -1
#endif

namespace RGE{
	class Block{
	public:
		int id = -1;
		int shape = -1;
		Block(){};
		Block(int id, int shape){
			this->id = id;
			this->shape = shape;
		};
	};
};