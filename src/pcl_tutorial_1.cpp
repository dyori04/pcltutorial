#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/point_cloud.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloudRGB;

class pcl_tutorial_1{

private:
    ros::NodeHandle nh;
    int i;
    ros::Publisher graypclPub;
    ros::Publisher RGBpclPub;

    PointCloud::Ptr graypcl;
    PointCloudRGB::Ptr rgbpcl;

public:
    pcl_tutorial_1(){
        graypclPub = nh.advertise<PointCloud> ("point2",100);
        RGBpclPub = nh.advertise<PointCloudRGB> ("rgbpoint2",100);

        graypcl.reset(new PointCloud);
        rgbpcl.reset(new PointCloudRGB);

        graypcl = PointCloud::Ptr(new PointCloud);
        graypcl->header.frame_id = "tf_frame_1";
        graypcl->height = graypcl->width = 1;
        //graypcl->points.push_back(pcl::PointXYZ(1.0,2.0,3.0));
 
        rgbpcl = PointCloudRGB::Ptr(new PointCloudRGB);
        rgbpcl->header.frame_id = "tf_frame_1";
        rgbpcl->height = graypcl->width = 1;

        i = 0;
        }

    void pushbackTutorial(){
    pcl::PointXYZRGB rgbpoint;
            rgbpoint.x = float(-i);
            rgbpoint.y = float(-i);
            rgbpoint.z = float(-i);
            rgbpoint.r = i*10;
            rgbpoint.g = 0;
            rgbpoint.b = 255 -i*10;
            graypcl->points.push_back(pcl::PointXYZ(float(i),float(i),float(i)));
            rgbpcl->points.push_back(rgbpoint);
            i++;
            std::cout<<i<<std::endl;
        if(i==20){
        graypcl->points.clear();
        rgbpcl->points.clear();
        i=0;
        }
        else{
        graypclPub.publish(graypcl);
        RGBpclPub.publish(rgbpcl);
        }
    }

    void spin(){
        pcl_conversions::toPCL(ros::Time::now(), graypcl->header.stamp);
        pcl_conversions::toPCL(ros::Time::now(), rgbpcl->header.stamp);
        ros::Rate r(3);
        while(ros::ok()){
            pushbackTutorial();
            r.sleep();
            ros::spinOnce();
        }
    }
};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "pcl_tutorial_1");
    pcl_tutorial_1 *pt1 = new pcl_tutorial_1;
    pt1->spin();
  if(!ros::ok()){
      delete pt1;
  }
}