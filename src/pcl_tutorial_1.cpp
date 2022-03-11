#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/point_cloud.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud; //PointXYZ를 Point로 쓰는 PointCloud
typedef pcl::PointCloud<pcl::PointXYZRGB> PointCloudRGB; //PointXYZRGB를 point로 쓰는 PointCloud

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
        graypclPub = nh.advertise<PointCloud> ("point2",100); //PointXYZ Publisher
        RGBpclPub = nh.advertise<PointCloudRGB> ("rgbpoint2",100); //PointXYZRGB Publisher

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
        graypcl->resize(i+1); //Point Cloud의 Point 수 확대
        rgbpcl->resize(i+1);
        rgbpoint.x = float(-i);
        rgbpoint.y = float(-i);
        rgbpoint.z = float(-i);
        rgbpoint.r = i*10;
        rgbpoint.g = 0;
        rgbpoint.b = 255 -i*10;
        graypcl->points.push_back(pcl::PointXYZ(float(i),float(i),float(i))); //Point 삽입
        rgbpcl->points.push_back(rgbpoint);
        i++;
        std::cout<<i<<std::endl;
        if(i==20){
        graypcl->points.clear(); //i가 20이 될때마다 Poitnt Cloud 리셋
        rgbpcl->points.clear();
        i=0;
        }
        else{
        graypclPub.publish(graypcl); //Point Cloud Publish
        RGBpclPub.publish(rgbpcl);
        }
    }

    void spin(){
        ros::Rate r(3);
        while(ros::ok()){
            pcl_conversions::toPCL(ros::Time::now(), graypcl->header.stamp);
            pcl_conversions::toPCL(ros::Time::now(), rgbpcl->header.stamp);
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
