#ifndef CAN_SERVICE_HPP
#define CAN_SERVICE_HPP

#include <vsomeip/vsomeip.hpp>
#include <thread>
#include <atomic>


#include <iostream>
#include <iomanip>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <csignal>

class CANService
{
	public:
		CANService();
		~CANService();

		void init();
		void start();
		void stop();
	private:
		void read_can_data();
		void setup_can_socket();

		std::shared_ptr<vsomeip::application> app;
		int socket_fd;
		std::atomic<bool> running;
		std::thread can_thread;
		void notify_can_data_received(uint32_t can_id, const std::vector<vsomeip::byte_t>& data);

		static const vsomeip::service_t CAN_SERVICE_ID = 4660; // SomeIpServiceID
		static const vsomeip::instance_t CAN_INSTANCE_ID = 0x5678;
		static const vsomeip::method_t CAN_METHOD_ID = 3000;
		static const vsomeip::event_t CAN_EVENT_ID = 33000;

};


#endif