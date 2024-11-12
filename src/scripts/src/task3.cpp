#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

int main(int argc, char **argv)
{
    // Initialize ROS node
    ros::init(argc, argv, "custom_move_group_interface");
    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    // Specify planning group for MoveIt
    const std::string PLANNING_GROUP = "move_rakhat";
    moveit::planning_interface::MoveGroupInterface robot_controller(PLANNING_GROUP);

    const robot_state::JointModelGroup* joint_group =
        robot_controller.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

    geometry_msgs::PoseStamped current_position = robot_controller.getCurrentPose();
    geometry_msgs::PoseStamped target_position = current_position;

    // Function to move to specified offsets
    auto executeMove = [&robot_controller, &current_position](geometry_msgs::PoseStamped& target_position, double x_offset, double y_offset, double tolerance = 0.01) {
        target_position.pose.position.x += x_offset;
        target_position.pose.position.y += y_offset;
        
        ros::Rate rate(50);

        while (ros::ok()) {
            robot_controller.setApproximateJointValueTarget(target_position);
            robot_controller.move();

            current_position = robot_controller.getCurrentPose();

            // Verify target position with specified tolerance
            if (fabs(current_position.pose.position.x - target_position.pose.position.x) < tolerance &&
                fabs(current_position.pose.position.y - target_position.pose.position.y) < tolerance) {
                break;
            }
            rate.sleep();
        }
    };

    // Define rectangular path
    executeMove(target_position, -0.3, 0.0);  // Move along x-axis
    executeMove(target_position, 0.0, 0.3);   // Move along y-axis
    executeMove(target_position, -0.5, 0.0);  // Further along x-axis
    executeMove(target_position, 0.0, -0.6);  // Down along y-axis
    executeMove(target_position, 0.5, 0.0);   // Back along x-axis
    executeMove(target_position, 0.0, 0.6);   // Back to starting y position

    ROS_INFO("Rectangle path completed successfully");
    ros::shutdown();
    return 0;
}

