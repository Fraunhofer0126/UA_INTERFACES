cmake_minimum_required(VERSION 3.8)
project(ka_test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(ua_interfaces REQUIRED)

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

add_executable(fric_whl_client src/fric_whl_client.cpp)
ament_target_dependencies(fric_whl_client rclcpp ua_interfaces)
add_executable(shoot_mode_client src/shoot_mode_client.cpp)
ament_target_dependencies(shoot_mode_client rclcpp ua_interfaces)

install(TARGETS
  fric_whl_client
  shoot_mode_client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
