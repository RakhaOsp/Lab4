#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <cmath>
#include <std_msgs/Float64MultiArray.h>

int main(int argc, char **argv)
{
    // Initialize ROS node and a node handle
    ros::init(argc, argv, "circle_motion_example");
    ros::NodeHandle nh;

    // Real-time position publisher
    ros::Publisher position_publisher = nh.advertise<std_msgs::Float64MultiArray>("robot_position", 10);

    // Set up an asynchronous spinner for ROS callbacks
    ros::AsyncSpinner async_spinner(1);
    async_spinner.start();

    // Configure the MoveIt planning group
    const std::string GROUP_NAME = "move_rakhat";
    moveit::planning_interface::MoveGroupInterface robot_mover(GROUP_NAME);

    // Set initial and target poses
    geometry_msgs::PoseStamped initial_pose = robot_mover.getCurrentPose();
    geometry_msgs::PoseStamped target_position = initial_pose;

    // Move to the starting point at the top of the circle (12 o'clock position)
    target_position.pose.position.x -= 0.5;
    robot_mover.setApproximateJointValueTarget(target_position);
    robot_mover.move();

    // Define circle parameters around this initial position
    double center_x = target_position.pose.position.x;
    double center_y = target_position.pose.position.y;
    double radius = 0.5;
    int points_count = 72;
    double angle_step = -2 * M_PI / points_count;

    // Loop through each position on the circle path
    for (int i = 0; i < points_count; ++i)
    {
        double angle = i * angle_step;

        // Calculate and set target position
        target_position.pose.position.x = center_x + radius * cos(angle);
        target_position.pose.position.y = center_y + radius * sin(angle);

        // Publish position data for visualization
        std_msgs::Float64MultiArray position_msg;
        position_msg.data = {target_position.pose.position.x, target_position.pose.position.y};
        position_publisher.publish(position_msg);

        // Move to the target position on the circular path
        robot_mover.setApproximateJointValueTarget(target_position);
        robot_mover.move();

        // Optional pause for smooth visualization
        ros::Duration(0.1).sleep();
    }

    ROS_INFO("Circular motion complete.");
    ros::shutdown();
    return 0;
}

