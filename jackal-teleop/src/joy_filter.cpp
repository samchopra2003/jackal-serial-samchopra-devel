#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>

class JoyFilter : public rclcpp::Node {
public:
  JoyFilter() : Node("joy_filter") {
    sub_ = create_subscription<sensor_msgs::msg::Joy>(
      "/joy_test", 10,
      std::bind(&JoyFilter::cb, this, std::placeholders::_1));

    pub_ = create_publisher<sensor_msgs::msg::Joy>("/joy", 10);
  }

private:
  void cb(const sensor_msgs::msg::Joy::SharedPtr msg) {
    auto out = *msg;

    // Example: force button 0 = estop
    if (out.buttons.size() <= 1)
      out.buttons.resize(2, 0);

    out.buttons[1] = 0;   // FORCE estop OFF

    pub_->publish(out);
  }

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
  rclcpp::Publisher<sensor_msgs::msg::Joy>::SharedPtr pub_;
};


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JoyFilter>());
  rclcpp::shutdown();
  return 0;
}

