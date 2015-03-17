#include "ros/ros.h"
//#include "turtlesim/Velocity.h"
#include "signal.h"
#include "termios.h"
#include "stdio.h"
#include "std_msgs/Int8.h"
#include <sstream>
	
#define KEYCODE_R 0x43
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71
	
class TeleopTurtle
{
public:
  TeleopTurtle();
  void keyLoop();

private:

	 
  ros::NodeHandle nh_;
  int linear_, angular_, l_scale_, a_scale_;
  ros::Publisher vel_pub_;
 
};

TeleopTurtle::TeleopTurtle():
  linear_(0),
  angular_(0),
  l_scale_(2),
  a_scale_(2)
{
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  //vel_pub_ = nh_.advertise<turtlesim::Velocity>("turtle1/command_velocity", 1);
}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}


int main(int argc, char** argv)
{
   
   

while (ros::ok())
  {

    ros::init(argc, argv, "keyboard_read");
  //TeleopTurtle teleop_turtle;
	//  signal(SIGINT,quit);

	 // teleop_turtle.keyLoop();

   ros::NodeHandle n;
    
   std_msgs::Int8 msg;

    msg.data = linear_;

    ROS_INFO("%i", msg.data);

 
    chatter_pub.publish(msg);

  
	ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("linear_", 1000);

	ros::Rate loop_rate(10);

    ros::spinOnce();

    loop_rate.sleep();
    
  }

while (ros::ok())
{

ros::init(argc, argv, "keyboard_read");
  //TeleopTurtle teleop_turtle;
	//  signal(SIGINT,quit);

	 // teleop_turtle.keyLoop();

   ros::NodeHandle n;

	std_msgs::Int8 msg;

    msg.data = angular_;

    ROS_INFO("%i", msg.data);

 
    chatter_pub.publish(msg);
	ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("angular_", 1000);

	ros::Rate loop_rate(10);

    ros::spinOnce();

    loop_rate.sleep();




}
 
  return(0);
}


void TeleopTurtle::keyLoop()
{
  char c;
  bool dirty=false;

	
  // get the console in raw mode                                                             
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move Field Robot");


  for(;;)
  {
    // get the next event from the keyboard 
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

    linear_=angular_=0;
    ROS_DEBUG("value: 0x%02X\n", c);
 
    switch(c)
    {
      case KEYCODE_L:
        ROS_DEBUG("LEFT");
        angular_ = 1;
        dirty = true;
        break;
      case KEYCODE_R:
        ROS_DEBUG("RIGHT");
        angular_ = -1;
        dirty = true;
        break;
      case KEYCODE_U:
        ROS_DEBUG("UP");
        linear_ = 1;
        dirty = true;
        break;
      case KEYCODE_D:
        ROS_DEBUG("DOWN");
        linear_ = -1;
        dirty = true;
        break;
    }
   


  



  


  


  // turtlesim::Velocity vel;
  // vel.angular = a_scale_*angular_;
  // vel.linear = l_scale_*linear_;
  // if(dirty ==true)
  //  {
  //   vel_pub_.publish(vel);   
  //    dirty=false;
  //  }
 }


  return;	
}
	
