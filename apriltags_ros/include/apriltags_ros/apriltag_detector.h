#ifndef APRILTAG_DETECTOR_H
#define APRILTAG_DETECTOR_H

#include <ros/ros.h>
#include <image_transport/image_transport.h>

#include <AprilTags/TagDetector.h>
#include <tf/transform_broadcaster.h>

namespace apriltags_ros{


class AprilTagDescription{
 public:
  AprilTagDescription(int id, double size, std::string &frame_name):id_(id), size_(size), frame_name_(frame_name){}
  double size(){return size_;}
  int id(){return id_;} 
  std::string& frame_name(){return frame_name_;} 
 private:
  int id_;
  double size_;
  std::string frame_name_;
};


class AprilTagDetector{
 public:
  AprilTagDetector(ros::NodeHandle& nh, ros::NodeHandle& pnh);
  ~AprilTagDetector();
 private:

  void cam_info(const sensor_msgs::CameraInfoConstPtr& cam_info);
  void imagePicture(const sensor_msgs::ImageConstPtr& msg);
  std::map<int, AprilTagDescription> parse_tag_descriptions(XmlRpc::XmlRpcValue& april_tag_descriptions);

  std::map<int, AprilTagDescription> descriptions_;
  std::string sensor_frame_id_;
  std::string tf_prefix_;
  ros::Subscriber image_sub_;
  ros::Subscriber cam_info_;
  ros::Publisher image_pub_;
  ros::Publisher detections_pub_;
  ros::Publisher pose_pub_;
  tf::TransformBroadcaster tf_pub_;
  boost::shared_ptr<AprilTags::TagDetector> tag_detector_;
  bool projected_optics_;
  double fx;
  double fy;
  double px;
  double py;
};



}


#endif
