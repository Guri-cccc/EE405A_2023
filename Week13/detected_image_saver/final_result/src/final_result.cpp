#include "final_result/final_result.h"

EE405A_FINAL_RESULT::EE405A_FINAL_RESULT()
: node_handle_("")
{
    initPublisher();
    initSubscriber();

    ROS_INFO("WAITING TO SAVE IMAGE");
}

EE405A_FINAL_RESULT::~EE405A_FINAL_RESULT()
{
    ROS_INFO("TERMINATE FINAL RESULT NODE");
    ros::shutdown();
}

void EE405A_FINAL_RESULT::initPublisher()
{

}

void EE405A_FINAL_RESULT::initSubscriber()
{
    target_detection_img = node_handle_.subscribe("/target_detection", 1, &EE405A_FINAL_RESULT::targetDetectionCallback, this);
}

void EE405A_FINAL_RESULT::targetDetectionCallback(const final_result_msgs::save_image::ConstPtr& msg)
{
    target_class_id = msg->class_id;
    target_x = msg->x_pose;
    target_y = msg->y_pose;
    try
    {
        if(detected_num_list.empty())
        {
            cv_bridge::CvImagePtr cv_ptr;
            cv_ptr = cv_bridge::toCvCopy(msg->save_img, sensor_msgs::image_encodings::BGR8);
            std::stringstream filename;
            
            double final_x = floor(target_x*100.0)/100.0;
            double final_y = floor(target_y*100.0)/100.0;
                                
            /*
            example: user name = hyungjoo (you can check your device information)
            example: workspace name = catkin_ws
            */
            filename << "/home/(user_name)/(workspace_name)/src/final_result/results/" << target_class_id << "_" << final_x << "_" << final_y << ".jpg";

            std::cout << filename.str() << std::endl;

            cv::imwrite(filename.str(), cv_ptr->image);
            detected_num_list.push_back(target_class_id);
        }
        else
        {
            if(std::find(detected_num_list.begin(), detected_num_list.end(), target_class_id) == detected_num_list.end())
            {
                cv_bridge::CvImagePtr cv_ptr;
                cv_ptr = cv_bridge::toCvCopy(msg->save_img, sensor_msgs::image_encodings::BGR8);
                std::stringstream filename;
                
                double final_x = floor(target_x*100.0)/100.0;
                double final_y = floor(target_y*100.0)/100.0;
                                    
                /*
                example: user name = hyungjoo (you can check your device information)
                example: workspace name = catkin_ws
                */
                filename << "/home/(user_name)/(workspace_name)/src/final_result/results/" << target_class_id << "_" << final_x << "_" << final_y << ".jpg";

                        
                std::cout << filename.str() << std::endl;

                cv::imwrite(filename.str(), cv_ptr->image);
                detected_num_list.push_back(target_class_id);
            }
            else
            {
                // std::cout << "You Already Found " << target_class_id << ", so Waiting the Next Number" << std::endl;
            }
        }
        
    }
    catch(const std::exception& e)
    {
        std::cout << "Error to Subscribe your Target IMAGE from YOLO DETECTION MODEL" << std::endl;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "final_result");
    EE405A_FINAL_RESULT final_result;
    ros::Rate loop_rate(10);

    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
}
