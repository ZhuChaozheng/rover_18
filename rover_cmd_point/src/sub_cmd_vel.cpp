
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"


using namespace std;

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
nav_msgs::Odometry odom;
geometry_msgs::Twist new_vel;

void velCallback(const geometry_msgs::Twist::ConstPtr& vel);
void write_callback(const std_msgs::String::ConstPtr& msg);
void serial_write(void);
int main(int argc, char **argv)
{
	// Initiate new ROS node named "rover_garen_node"
	ros::init(argc, argv, "rover_garen_node");
	ros::NodeHandle np;
	pose_subscriber = np.subscribe("/husky_velocity_controller/cmd_vel", 10, velCallback);
	velocity_publisher = np.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);
	ros::Rate loop_rate(5);
   

	ROS_INFO("\n\n\n ********START TESTING*********\n");
	
     
	ros::spin();

	return 0;
}





void velCallback(const geometry_msgs::Twist::ConstPtr& vel) 
{
        new_vel.linear.x=vel->linear.x;
	new_vel.linear.y=vel->linear.y;
	new_vel.angular.z=vel->angular.z;
              ROS_INFO("x : %lf y : %lf thetha : %lf ",new_vel.linear.x,new_vel.linear.y,new_vel.angular.z);
//serial_write();
}

/*

void write_callback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO_STREAM("Writing to serial port" << msg->data);
    ser.write(msg->data);
}

void serial_write(void)
{
    ros::NodeHandle nh;

    ros::Subscriber write_sub = nh.subscribe("write", 1000, write_callback);
    ros::Publisher read_pub = nh.advertise<std_msgs::String>("read", 1000);

    try
    {
        ser.setPort("/dev/ttyACM0");
        ser.setBaudrate(9600);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }

    ros::Rate loop_rate(5);
    while(ros::ok()){

        ros::spinOnce();

        if(ser.available()){
            ROS_INFO_STREAM("Reading from serial port");
            std_msgs::String result;
            result.data = ser.read(ser.available());
            ROS_INFO_STREAM("Read: " << result.data);
            read_pub.publish(result);
        }
        loop_rate.sleep();

    }
}









}






*/

