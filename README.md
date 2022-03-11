# pcltutorial
detection team's pcl tutorial pkg

# how to use

package.xml and CMakelist is ready to build source file using opencv and pcl

you may need to install opencv library to use opencv things (opencv need to be installed before installing ros)

add your source to Cmakelist like this :

add_executable([excutable_name] src/[sourcename].cpp)
target_link_libraries([excutable_name]
  ${catkin_LIBRARIES}
  ${OpenCV_INCUDE_DIRS}
)

## pcl_tutorial_1

simple tutorial making pointcloud object and publish to ros topic

### result

![Screenshot from 2022-03-11 15-26-35](https://user-images.githubusercontent.com/65892441/157814324-55a5fb1d-189d-48fa-801a-78d562872d78.png)

### RVIZ setup

1. Add - By topic - /point2, /rgbpoint2
2. modify Size(m) of both cloud to 0.1
