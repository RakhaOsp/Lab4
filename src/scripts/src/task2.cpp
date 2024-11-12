#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "custom_move_group_interface");
    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    // Define the planning group name
    const std::string PLANNING_GROUP = "move_rakhat";
    moveit::planning_interface::MoveGroupInterface robot_mover(PLANNING_GROUP);

    const robot_state::JointModelGroup* joint_model_group =
        robot_mover.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

    geometry_msgs::PoseStamped current_position = robot_mover.getCurrentPose();
    geometry_msgs::PoseStamped target_position = current_position;

    // Adjust the target position
    target_position.pose.position.x -= 1.4;

    ros::Rate rate(50);

    while (ros::ok())
    {
        // Set the approximate target position
        robot_mover.setApproximateJointValueTarget(target_position);

        // Command robot to move to the target position
        robot_mover.move();

        // Update current position
        current_position = robot_mover.getCurrentPose();

        // Exit if within tolerance of the target position
        if (fabs(current_position.pose.position.x - target_position.pose.position.x) < 0.01)
        {
            break;
        }
        rate.sleep();
    }

    ROS_INFO("Movement Complete");
    ros::shutdown();
    return 0;
}

