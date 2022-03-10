# pcltutorial
detection team's pcl tutorial pkg

# how to use

package.xml and CMakelist is ready to build source file using opencv and pcl

add your source to Cmakelist like this :

add_executable([excutable_name] src/[sourcename].cpp)
target_link_libraries([excutable_name]
  ${catkin_LIBRARIES}
  ${OpenCV_INCUDE_DIRS}
)
