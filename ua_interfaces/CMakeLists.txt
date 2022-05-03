cmake_minimum_required(VERSION 3.8)
project(ua_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/GameStatus.msg"
  "msg/GameResult.msg"
  "msg/GameRobotHP.msg"
  "msg/GameRobotBullet.msg"
  "msg/GameZone.msg"
  "msg/GameZoneArray.msg"
  "msg/RobotStatus.msg"
  "msg/RobotHeat.msg"
  "msg/RobotDamage.msg"
  "msg/RobotShoot.msg"
  "msg/LurkStatus.msg"
  "srv/FricWhl.srv"
  "srv/ShootCmd.srv"
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(FILES mapping_rules.yaml
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
