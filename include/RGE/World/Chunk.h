#pragma once

#include "RGE/World/Block.h"

namespace RGE{
	class Chunk
	{
	public:
		int width, height, layers;
		
		RGE::Block*** data;
		Chunk(){}
		Chunk(int width, int height, int layers);
	private:
		void makeData();
	};
};