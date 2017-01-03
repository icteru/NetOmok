#pragma once

#include <memory>

namespace omok
{
	class Application : public std::enable_shared_from_this<Application>
	{
	public:
		Application();
		~Application();

		bool init();
		void run();
		void quit();
		void clean();

	private:
		bool system_inited;
		bool exit;
	};

	using ApplicationSP = std::shared_ptr<Application>;
}










