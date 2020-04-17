#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>

int main(int argc, char **argv) {
    // Initialize ROS channels
    ros::init(argc, argv, "rosbot");
    ros::NodeHandle nh;

    image_transport::ImageTransport imgTransport(nh);
    auto imgPub = imgTransport.advertise("camera/image", 1);

    // Open camera
    int camDeviceIndex = 0;
    ros::param::param<int>("~cam_device_index", camDeviceIndex, 0);
    cv::VideoCapture cam(camDeviceIndex);

    if (!cam.isOpened()) {
        ROS_FATAL_STREAM("Failed to open camera device: " << camDeviceIndex);
        return 1;
    }

    ROS_INFO_STREAM("Successfully opened camera device: " << camDeviceIndex);
    ROS_INFO_STREAM("Streaming camera images...");

    // Publish camera images
    while (ros::ok()) {
        cv::Mat img;
        if (cam.read(img)) {
            auto msg = cv_bridge::CvImage({}, "bgr8", img).toImageMsg();
            imgPub.publish(msg);
        }

        ros::spinOnce();
    }

    return 0;
}
