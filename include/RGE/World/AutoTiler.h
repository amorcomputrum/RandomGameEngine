#pragma once
#pragma GCC diagnostic ignored "-Wpointer-arith"

#include <vector>
#include <map>

namespace RGE{
	namespace AutoTiler{
		static bool corners = false;
		enum Shape{
			NONE                                                             = 0,
			LEFT                                                             = 1,
			TOP                                                              = 2,
			RIGHT                                                            = 3,
			BOTTOM                                                           = 4,
			LEFT_RIGHT                                                       = 5,
			TOP_BOTTOM                                                       = 6,
			LEFT_TOP                                                         = 7,
			TOP_RIGHT                                                        = 8,
			RIGHT_BOTTOM                                                     = 9,
			LEFT_BOTTOM                                                     = 10,
			LEFT_TOP_RIGHT                                                  = 11,
			TOP_RIGHT_BOTTOM                                                = 12,
			LEFT_RIGHT_BOTTOM                                               = 13,
			LEFT_TOP_BOTTOM                                                 = 14,
			ALL                                                             = 15,
			TOPLEFTCORNER                                                   = 16,
			TOPRIGHTCORNER                                                  = 17,
			BOTTOMLEFTCORNER                                                = 18,
			BOTTOMRIGHTCORNER                                               = 19,
			TOPLEFTCORNER_RIGHT_BOTTOM                                      = 20,
			TOPLEFTCORNER_RIGHT                                             = 21,
			TOPLEFTCORNER_BOTTOM                                            = 22,
			TOPRIGHTCORNER_LEFT_BOTTOM                                      = 23,
			TOPRIGHTCORNER_LEFT                                             = 24,
			TOPRIGHTCORNER_BOTTOM                                           = 25,
			BOTTOMLEFTCORNER_RIGHT_TOP                                      = 26,
			BOTTOMLEFTCORNER_RIGHT                                          = 27,
			BOTTOMLEFTCORNER_TOP                                            = 28,
			BOTTOMRIGHTCORNER_LEFT_TOP                                      = 29,
			BOTTOMRIGHTCORNER_LEFT                                          = 30,
			BOTTOMRIGHTCORNER_TOP                                           = 31,
			TOPLEFTCORNER_TOPRIGHTCORNER                                    = 32, 
			TOPLEFTCORNER_TOPRIGHTCORNER_BOTTOMRIGHTCORNER                  = 33,
			TOPLEFTCORNER_TOPRIGHTCORNER_BOTTOMRIGHTCORNER_BOTTOMLEFTCORNER = 34,
			TOPLEFTCORNER_BOTTOMRIGHTCORNER                                 = 35,
			TOPLEFTCORNER_BOTTOMRIGHTCORNER_BOTTOMLEFTCORNER                = 36,
			TOPLEFTCORNER_BOTTOMLEFTCORNER                                  = 37,
			TOPRIGHTCORNER_BOTTOMRIGHTCORNER                                = 38,
			TOPRIGHTCORNER_BOTTOMLEFTCORNER                                 = 39,
			BOTTOMRIGHTCORNER_BOTTOMLEFTCORNER                              = 40,
			TOPLEFTCORNER_TOPRIGHTCORNER_BOTTOM                             = 41,
			TOPLEFTCORNER_RIGHT_BOTTOMLEFTCORNER                            = 42,
			LEFT_TOPRIGHTCORNER_BOTTOMRIGHTCORNER                           = 43,
			TOP_BOTTOMRIGHTCORNER_BOTTOMLEFTCORNER                          = 44
		};

		class MBRegistry{
		public:
			static void add(int id, std::vector<int> MBS);
			static std::vector<int> get(int id);
		private:
			static std::map<int,std::vector<int>> MAP;
		};

		int toShape(int sum);

		bool interacts(int id, std::vector<int> interactions);

		int tile(int currentBlockID, int topBlock, int bottomBlock, int prevBlock, int nextBlock, int topLEFTBlock, int topRIGHTBlock, int bottomLEFTBlock, int bottomRIGHTBlock);
	};
};