//========================================                                                                            
2.1 Создание простых нод писателя и читателя
//========================================
#include "ros/ros.h"                                                            
#include "std_msgs/Int32.h"                                                     
#include <iostream>                                                             
using namespace std;                                                            
                                                                                
int main(int argc, char **argv)                                                 
{                                                                               
ros::init(argc, argv,"node");                                                   
ros::NodeHandle n;                                                              
ros::Publisher pub = n.advertise<std_msgs::Int32>("/topic",1000);               
ros::Rate loop_rate(0.5);                                                       
int x;                                                                          
std_msgs::Int32 a;                                                              
ros::Duration(3).sleep();                                                      
while(cin>>x)                                                                   
{                                                                               
ros::Duration(1).sleep();                                                       
a.data = x;                                                                     
ROS_INFO("Data: %d",a.data);
pub.publish(a);                                                                 
loop_rate.sleep();                                                              
}                                                                               
ros::spinOnce();                                                                
return 0;                                                                       
}                                                                               
//========================================
#include "ros/ros.h"                                                            
#include "std_msgs/Int32.h"                                                     
#include <iostream>
using namespace std;
void fun(const std_msgs::Int32& a)
{
cout<<"/subscriber: data: "<<a.data<<endl;
}

int main(int argc , char **argv)
{
ros::init(argc,argv,"subscriber");
ros::NodeHandle n;
ros::Subscriber sub = n.subscribe("/topic",1000,fun);
ros::spin();
return 0;
}



//========================================                                                                            
2.2 Обмен сообщениями собственного типа        
//========================================	 
rosmsg show sensor_msgs/NavSatStatus >>out.txt

//========================================
2.3 Понятие и создание собственного сервиса
rosservice list >>out.txt
//========================================

#include "ros/ros.h"                                                            
#include "my_service/AddStrings.h"                                              
                                                                                
bool add(service::AddStrings::Request &req,service::AddStrings::Response &res)  
{                                                                               
res.sum = req.first + req.second;                                               
ROS_INFO("Request: 1= %c, 2=%c,req.first,req.second);                           
ROS_INFO("Sending Back : %c, res.sum);                                          
                                                                                
}                                                                               
int main(int argc,char** argv)                                                  
{                                                                               
ros::init(argc,argv,"add_two_strings_server");                                  
ros::NodeHandle n;                                                              
ros::ServiceServer service = n.advertiseService("add_two_strings",add);         
ROS_INFO("Ready to add two ints.");                                             
ros::spin();                                                                    
}    

#include "ros/ros.h"
#include "my_service/AddStrings.h"

bool add(my_service::AddStrings::Request &req,my_service::AddStrings::Response $
{
res.sum=req.first+req.second;
ROS_INFO("Sending back : %s", res.sum);

}

int main(int argc, char **argv)
{
ros::init(argc,argv,"add_two_strings_server");
ros::NodeHandle n ;
ros::ServiceServer service = n.advertiseService("/meow/add_two_strings",add);
ROS_INFO("Ready to add");
ros::spin();
return 0;
}

//========================================
3.1 Визуализация с помощью RVIZ
//========================================
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>
static uint32_t cnt=0;
class SubscribeAndPublish
{
public:
SubscribeAndPublish()
{
pub_=n_.advertise<visualization_msgs::Marker>("/output",100);
sub_=n_.subscribe("/input",100,&SubscribeAndPublish::callback,this);
}
void callback(const geometry_msgs::Point& input)
{
visualization_msgs::Marker mk;
mk.header.frame_id="/point_on_map";
mk.header.stamp=ros::Time::now();
mk.ns="A_point";
mk.id=cnt++;
mk.action=visualization_msgs::Marker::ADD;
mk.type=visualization_msgs::Marker::POINTS;
mk.scale.x=0.5;
mk.scale.y=0.5;
mk.scale.z=0.5;
mk.color.r=1.0;
mk.color.g=0.0;
mk.color.b=0.0;
mk.color.a=1.0;
mk.points.push_back(input);
pub_.publish(mk);
sleep(2);
}
private:
ros::NodeHandle n_;
ros::Publisher pub_;
ros::Subscriber sub_;

};
int main(int argc, char **argv)
{
ros::init(argc, argv,"point_publisher");
SubscribeAndPublish ASPObject;
ros::spin();
return 0;
}
//========================================
3.2 Использование launch-файлов
//========================================
<launch>                                                                        
                                                                                
<node pkg = "example_pkg" type="node1" name="node1" required = "true" output="screen" >
<param name="cost" type="int" value="1"/>
</node>                                                                         
<node pkg = "sample_pkg" type="node2" name"node2" output="screen">
<remap from="input_aray" to="input_array" />                                    
</node>                                                                         
<arg name="max_size" default="-1">
<node pkg = "example_pkg" type="node3" name"node3" output="screen">
<param name ="max_size" type="int" value="$(arg max_size)" />
</node>                                                                         
                                                                                
</launch>                                                                                                                                                                                           

