#ifndef __BOARDMODEL_HPP__
#define __BOARDMODEL_HPP__

namespace lib
{
	namespace board
	{
		struct BoardModelOptions
		{
			unsigned int w;
			unsigned int h;
		};
		class BoardModel
		{
		public:
			BoardModel();
			virtual ~BoardModel();

			void create(const BoardModelOptions &options);
		};
	}
}

#endif
