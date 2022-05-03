#include "rclcpp/rclcpp.hpp"
#include "ua_interfaces/srv/shoot_cmd.hpp"        // CHANGE

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 3) { // CHANGE
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: shoot_mode_client MODE(0=stop 1=once 2=continue) NUMBER");      // CHANGE
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("shoot_mode_client"); // CHANGE
  rclcpp::Client<ua_interfaces::srv::ShootCmd>::SharedPtr client =                        // CHANGE
    node->create_client<ua_interfaces::srv::ShootCmd>("ua_cmd_shoot");                  // CHANGE

  auto request = std::make_shared<ua_interfaces::srv::ShootCmd::Request>();               // CHANGE
  request->mode = atoi(argv[1]);
  request->number = atoi(argv[2]);

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "IF RECEIVED?: %d", result.get()->received);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service shoot_mode_client");    // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}