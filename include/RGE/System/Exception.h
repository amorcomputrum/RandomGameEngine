#pragma once

#include <iostream>

namespace RGE{
	class exception {
	public:
		/**
		 * When thrown the message will be outputed and program stopped
		 * throw RGE::exception("That didn't work");
		 * 
		 * @param message The message to output
		*/
		exception(std::string message);
	};
}
