#include "app.hpp"

int main()
{
	std::unique_ptr<App> app = std::make_unique<App>("Tux Golf : Debug", 800, 600, "data/app/tuxgolf.png");

	app->app_loop();

	return 0;
}