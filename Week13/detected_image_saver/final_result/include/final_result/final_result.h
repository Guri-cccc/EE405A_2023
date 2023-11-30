#include <ros/ros.h>
#include <ros/package.h>
#include <sstream>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

#include "final_result_msgs/save_image.h"

class EE405A_FINAL_RESULT
{
    public:
      EE405A_FINAL_RESULT();
      ~EE405A_FINAL_RESULT();

      double target_x, target_y;
      int target_class_id;
      std::vector<int> detected_num_list; 


    private:
      ros::NodeHandle node_handle_;

      ros::Subscriber target_detection_img;

      void initPublisher();
      void initSubscriber();
      void targetDetectionCallback(const final_result_msgs::save_image::ConstPtr& msg);
};
