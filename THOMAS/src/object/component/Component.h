#pragma once
#include "../Object.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class THOMAS_API Component : public Object
			{
			private:
			public:
				Component(std::string name) : Object(name){}
			private:
			protected:

			};
		}
	}
}