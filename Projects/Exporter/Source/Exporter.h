#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <iostream>
#include <string>

namespace ai
{
	class Exporter
	{
	public:
		static bool ExportTexture(const std::string& file);
	};
}

#endif
