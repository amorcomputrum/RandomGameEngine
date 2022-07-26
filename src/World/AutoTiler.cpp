#include <cstddef>

#include "RGE/World/AutoTiler.h"

std::map<int,std::vector<int>> RGE::AutoTiler::MBRegistry::MAP;

void RGE::AutoTiler::MBRegistry::add(int id, std::vector<int> MBS){
	MAP.insert(std::pair<int, std::vector<int>>(id,MBS));
}

std::vector<int> RGE::AutoTiler::MBRegistry::get(int id){
	if(MAP.find(id) != MAP.end()) return MAP[id];
	else return {};
}

int RGE::AutoTiler::toShape(int sum){
	switch(sum){
		case 1:
			return RGE::AutoTiler::Shape::TOP;
			break;
		case 2:
			return RGE::AutoTiler::Shape::RIGHT;
			break;
		case 3:
			return RGE::AutoTiler::Shape::TOP_RIGHT;
			break;
		case 4:
			return RGE::AutoTiler::Shape::BOTTOM;
			break;
		case 5:
			return RGE::AutoTiler::Shape::TOP_BOTTOM;
			break;
		case 6:
			return RGE::AutoTiler::Shape::RIGHT_BOTTOM;
			break;
		case 7:
			return RGE::AutoTiler::Shape::TOP_RIGHT_BOTTOM;
			break;
		case 8:
			return RGE::AutoTiler::Shape::LEFT;
			break;
		case 9:
			return RGE::AutoTiler::Shape::LEFT_TOP;
			break;
		case 10:
			return RGE::AutoTiler::Shape::LEFT_RIGHT;
			break;
		case 11:
			return RGE::AutoTiler::Shape::LEFT_TOP_RIGHT;
			break;
		case 12:
			return RGE::AutoTiler::Shape::LEFT_BOTTOM;
			break;
		case 13:
			return RGE::AutoTiler::Shape::LEFT_TOP_BOTTOM;
			break;
		case 14:
			return RGE::AutoTiler::Shape::LEFT_RIGHT_BOTTOM;
			break;
		case 15:
			return RGE::AutoTiler::Shape::ALL;
			break;
		case 16:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER;
			break;
		case 18:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_RIGHT;
			break;
		case 20:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_BOTTOM;
			break;
		case 22:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_RIGHT_BOTTOM;
			break;
		case 32:
			return RGE::AutoTiler::Shape::TOPRIGHTCORNER;
			break;
		case 36:
			return RGE::AutoTiler::Shape::TOPRIGHTCORNER_BOTTOM;
			break;
		case 40:
			return RGE::AutoTiler::Shape::TOPRIGHTCORNER_LEFT;
			break;
		case 44:
			return RGE::AutoTiler::Shape::TOPRIGHTCORNER_LEFT_BOTTOM;
			break;
		case 48:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_TOPRIGHTCORNER;
			break;
		case 52:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_TOPRIGHTCORNER_BOTTOM;
			break;
		case 64:
			return RGE::AutoTiler::Shape::BOTTOMRIGHTCORNER;
			break;
		case 65:
			return RGE::AutoTiler::Shape::BOTTOMRIGHTCORNER_TOP;
			break;
		case 72:
			return RGE::AutoTiler::Shape::BOTTOMRIGHTCORNER_LEFT;
			break;
		case 73:
			return RGE::AutoTiler::Shape::BOTTOMRIGHTCORNER_LEFT_TOP;
			break;
		case 80:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_BOTTOMRIGHTCORNER;
			break;
		case 96:
			return RGE::AutoTiler::Shape::TOPRIGHTCORNER_BOTTOMRIGHTCORNER;
			break;
		case 104:
			return RGE::AutoTiler::Shape::LEFT_TOPRIGHTCORNER_BOTTOMRIGHTCORNER;
			break;
		case 112:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_TOPRIGHTCORNER_BOTTOMRIGHTCORNER;
			break;
		case 128:
			return RGE::AutoTiler::Shape::BOTTOMLEFTCORNER;
			break;
		case 129:
			return RGE::AutoTiler::Shape::BOTTOMLEFTCORNER_TOP;
			break;
		case 130:
			return RGE::AutoTiler::Shape::BOTTOMLEFTCORNER_RIGHT;
			break;
		case 131:
			return RGE::AutoTiler::Shape::BOTTOMLEFTCORNER_RIGHT_TOP;
			break;
		case 144:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_BOTTOMLEFTCORNER;
			break;
		case 146:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_RIGHT_BOTTOMLEFTCORNER;
			break;
		case 160:
			return RGE::AutoTiler::Shape::TOPRIGHTCORNER_BOTTOMLEFTCORNER;
			break;
		case 192:
			return RGE::AutoTiler::Shape::BOTTOMRIGHTCORNER_BOTTOMLEFTCORNER;
			break;
		case 193:
			return RGE::AutoTiler::Shape::TOP_BOTTOMRIGHTCORNER_BOTTOMLEFTCORNER;
			break;
		case 240:
			return RGE::AutoTiler::Shape::TOPLEFTCORNER_TOPRIGHTCORNER_BOTTOMRIGHTCORNER_BOTTOMLEFTCORNER;
			break;
		default:
			return RGE::AutoTiler::Shape::NONE;
			break;
	}
}

bool RGE::AutoTiler::interacts(int id, std::vector<int> interactions){
	for(int i = 0; i < interactions.size(); i++){
		if(id == interactions[i]) return true;
	}
	return false;
}

int RGE::AutoTiler::tile(int currentBlockID, int topBlock, int bottomBlock, int prevBlock, int nextBlock, int topLEFTBlock, int topRIGHTBlock, int bottomLEFTBlock, int bottomRIGHTBlock){
	int shape = 0;
	int top = 1, right = 2, bottom = 4, left = 8, topLeft = 16, topRight = 32, bottomRight = 64, bottomLeft = 128;
	bool rightApplied = false, leftApplied = false, topApplied = false, bottomApplied = false;
	std::vector<int> interactions = RGE::AutoTiler::MBRegistry::get(currentBlockID);
	//top block
	if(topBlock != NULL){
		//exists
		if(!interacts(topBlock, interactions)   ){
			shape += top   ;
			topApplied    = true;
		}
	}else{
		shape += top;
		topApplied = true;
	}

	//bottom Block
	if(bottomBlock != NULL){
		//exists
		if(!interacts(bottomBlock, interactions)){
			shape += bottom;
			bottomApplied = true;
		}
	}else{
		shape += bottom;
		bottomApplied = true;
	}

	//PrevBlock
	if(prevBlock != NULL){
		//exists
		if(!interacts(prevBlock, interactions)  ){
			shape += left ;
			leftApplied  = true;
		}
	}else{
		shape += left ;
		leftApplied  = true;
	}

	//NextBlock
	if(nextBlock != NULL){
		//exists
		if(!interacts(nextBlock, interactions)  ){
			shape += right;
			rightApplied = true;
		}
	}else{
		shape += right;
			rightApplied = true;
	}
	if(corners){
		//check corners
		if(!topApplied){
			//FIX THESE
			if(!(topLEFTBlock     == NULL)){
				if(!leftApplied){
					if(!interacts(topLEFTBlock, interactions)    ) shape += topLeft;
				}
			}else{
				if(!leftApplied) shape += topLeft;
			}
			if(!(topRIGHTBlock    == NULL)){
				if(!rightApplied){
					if(!interacts(topRIGHTBlock, interactions)   ) shape += topRight;
				}
			}else{
				if(!rightApplied) shape += topRight;
			}
		}
		if(!bottomApplied){
			if(!(bottomLEFTBlock  == NULL)){
				if(!leftApplied){
					if(!interacts(bottomLEFTBlock, interactions) ) shape += bottomLeft;
				}
			}else{
				if(!leftApplied) shape += bottomLeft;
			}
			if(!(bottomRIGHTBlock == NULL)){
				if(!rightApplied){
					if(!interacts(bottomRIGHTBlock, interactions)) shape += bottomRight;
				}
			}else{
				if(!rightApplied) shape += bottomRight;
			}
		}
	}
	return toShape(shape);
}