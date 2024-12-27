#include "CANService.hpp"

CANService::CANService() : socket_fd(-1), running(false) {}

CANService::~CANService()
{
	stop();
	if (socket_fd >= 0)
		close(socket_fd);
}

void CANService::init()
{
	// app = vsomeip::runtime::get()->create_application("CANService", "/etc/vsomeip.json");
	app = vsomeip::runtime::get()->create_application("CANService");
	if (!app)
        throw std::runtime_error("Failed to create SOME/IP application");
    if (!app->init())
        throw std::runtime_error("Failed to initialize SOME/IP application");
	// app->init();

	//offer service
	app->offer_service(CAN_SERVICE_ID, CAN_INSTANCE_ID);
	//define event group
	std::set<vsomeip::eventgroup_t> event_group;
	event_group.insert(0x01);

	//offer event
	app->offer_event(CAN_SERVICE_ID, CAN_INSTANCE_ID, CAN_EVENT_ID, event_group);
	setup_can_socket();
}

void CANService::start()
{
	running = true;
	can_thread = std::thread(&CANService::read_can_data, this);
	app->start();
}

void CANService::stop()
{
	running = false;
	if (can_thread.joinable())
		can_thread.join();
}

void CANService::setup_can_socket() 
{
    if ((socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) 
        throw std::runtime_error("Error creating socket");

    struct ifreq ifr;
    std::strcpy(ifr.ifr_name, "vcan0");
    ioctl(socket_fd, SIOCGIFINDEX, &ifr);

    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
	{
        close(socket_fd);
        throw std::runtime_error("Error binding socket");
    }
}


void CANService::read_can_data()
{
	while (running)
	{
		struct can_frame frame;
		if (read(socket_fd, &frame, sizeof(struct can_frame)) > 0)
		{
			std::vector<vsomeip::byte_t> data(frame.data, frame.data + frame.can_dlc);
			notify_can_data_received(frame.can_id, data);
			std::cout << "Received CAN frame: ID = 0x" << std::hex << frame.can_id 
                      << ", Data = ";
			for (int i = 0; i < frame.can_dlc; i++) 
			{
                std::cout << std::hex << std::setw(2) << std::setfill('0') 
                          << static_cast<int>(frame.data[i]) << " ";
            }
            std::cout << std::dec << std::endl;
			
		}
	}
}

void CANService::notify_can_data_received(uint32_t can_id, const std::vector<vsomeip::byte_t>& data)
{
	std::shared_ptr<vsomeip::message> notification = vsomeip::runtime::get()->create_notification();
	notification->set_service(CAN_SERVICE_ID);
	notification->set_instance(CAN_INSTANCE_ID);
	notification->set_method(CAN_EVENT_ID);

	std::shared_ptr<vsomeip::payload> payload = vsomeip::runtime::get()->create_payload();

	//prepare payload data
	std::vector<vsomeip::byte_t> combined_data;

	combined_data.push_back((can_id >> 24) & 0xFF);
	combined_data.push_back((can_id >> 16) & 0xFF);
	combined_data.push_back((can_id >> 8) & 0xFF);
	combined_data.push_back(can_id & 0xFF);

	//Add the rest of the data
	combined_data.insert(combined_data.end(), data.begin(), data.end());

	payload->set_data(combined_data);

	notification->set_payload(payload);

	app->notify(CAN_SERVICE_ID, CAN_INSTANCE_ID, CAN_EVENT_ID, payload); // send  notification
}