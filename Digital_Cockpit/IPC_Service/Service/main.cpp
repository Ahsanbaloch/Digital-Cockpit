#include "CANService.hpp"

CANService *service = nullptr;

void signal_handler(int signal)
{
	if (service)
	{
		std::cout << "stopping can service..." << std::endl;
		service->stop();
		delete service;
		service = nullptr;
		exit(0);
	}
}

int main()
{
	signal(SIGINT, signal_handler);

	try
	{
		service = new CANService();
		service->init();
		std::cout << "can service started..." << std::endl;
		service->start();

		// Keep the main thread alive while the service runs
        while (true)
            std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	catch (const std::exception& e) 
	{
        std::cerr << "Error: " << e.what() << std::endl;
        delete service;
        return 1;
    }
	delete service;
	return 0;
}