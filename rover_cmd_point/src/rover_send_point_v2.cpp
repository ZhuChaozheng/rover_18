
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "nav_msgs/Odometry.h"
#include <sstream>
#include "std_msgs/String.h"

using namespace std;

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
nav_msgs::Odometry odom;
void poseCallback(const nav_msgs::Odometry::ConstPtr & pose_message);
void moveTogoal( double xGoal, double yGoal);
void move(double speed, double distance, bool isForward);
int main(int argc, char **argv)
{
	// Initiate new ROS node named "talker"
	ros::init(argc, argv, "rover_garen_node2");
	ros::NodeHandle n;
	pose_subscriber = n.subscribe("/husky_velocity_controller/odom", 10, poseCallback);
	velocity_publisher = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);

	ros::Rate loop_rate(10);
        double x,y ;
	

	ROS_INFO("\n\n\n ********START TESTING*********\n");
          
        do {
  cout<<"goal pose x ?: ";
	cin>>x;	
	cout<<"goal pose y ?: ";
	cin>>y;	      
        moveTogoal(x ,y);
       }while (ros::ok());
	ros::spin();
     
	
	ros::spinOnce();

	return 0;
}

void move(double speed, double distance, bool isForward){
   geometry_msgs::Twist vel_msg;
  ROS_INFO("move");
   //set a random linear velocity in the x-axis
   if (isForward)
	   vel_msg.linear.x =abs(speed);
   else
	   vel_msg.linear.x =-abs(speed);
   vel_msg.linear.y =0;
   vel_msg.linear.z =0;
   //set a random angular velocity in the y-axis
   vel_msg.angular.x = 0;
   vel_msg.angular.y = 0;
   vel_msg.angular.z =0;

   double t0 = ros::Time::now().toSec();
   double current_distance = 0.0;
   ros::Rate loop_rate(100);
   do{
	   velocity_publisher.publish(vel_msg);
	   double t1 = ros::Time::now().toSec();
	   current_distance = speed * (t1-t0);
	   ros::spinOnce();
	   loop_rate.sleep();

	   //cout<<(t1-t0)<<", "<<current_distance <<", "<<distance<<endl;
   }while((current_distance<distance) &&(ros::ok()));
   vel_msg.linear.x =0;
   velocity_publisher.publish(vel_msg);

}
void moveTogoal( double xGoal, double yGoal)

{   ros::Rate loop_rate(5);
   
 actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "odom";
  goal.target_pose.header.stamp = ros::Time::now();
 
   goal.target_pose.pose.position.x =  xGoal;
   goal.target_pose.pose.position.y =  yGoal;
   goal.target_pose.pose.position.z =  0.0;
   goal.target_pose.pose.orientation.x = 0.0;
   goal.target_pose.pose.orientation.y = 0.0;
   goal.target_pose.pose.orientation.z = 0;
   goal.target_pose.pose.orientation.w = 1.0;

   
  ROS_INFO("Sending goal " );
  std::cout<<"x:"<<xGoal<<" y:"<<yGoal ;
  std::cout<<"angle"<< (odom.pose.pose.position.x *180.0/3.14 );
   //  ROS_INFO("x: %s y: %s" , odom.pose.pose.position.x  ,odom.pose.pose.position.y  );
  ac.sendGoal(goal);

	
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray!");
  else
    ROS_INFO("The base failed to move for some reason");
	loop_rate.sleep();
}
void send_vel(void){
ros::Rate loop_rate(5);
   
 actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }  




}
void poseCallback(const nav_msgs::Odometry::ConstPtr & pose_message){
	odom.pose.pose.position.x=pose_message->pose.pose.position.x;
	odom.pose.pose.position.y=pose_message->pose.pose.position.y;
	odom.pose.pose.position.z=pose_message->pose.pose.position.z;

	odom.pose.pose.orientation.w=pose_message->pose.pose.orientation.w;
	odom.pose.pose.orientation.x=pose_message->pose.pose.orientation.x;
	odom.pose.pose.orientation.y=pose_message->pose.pose.orientation.y;
	odom.pose.pose.orientation.z=pose_message->pose.pose.orientation.z;
        
ROS_INFO("a");




}








