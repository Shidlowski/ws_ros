#include <ros/ros.h>
#include "actionlib/client/simple_action_client.h"
#include "actionlib/client/terminal_state.h"
#include "test_action_pkg/testAction.h"

  test_action_pkg::testGoal goal;

  // Called once when the goal completes
  void doneCb(const actionlib::SimpleClientGoalState& state,
               const test_action_pkg::testResultConstPtr& result)
  {
     ROS_INFO("Finished in state [%s]", state.toString().c_str());
     ROS_INFO("Answer: %i", result->rezult.back());
     ros::shutdown();
  } 

  // Called once when the goal becomes active
  void activeCb()
  {
     ROS_INFO_STREAM("Goal just went active = "<<goal.goal);
  }
  
  // Called every time feedback is received for the goal
  void feedbackCb(const test_action_pkg::testFeedbackConstPtr& feedback)
  {
     ROS_INFO("Got Feedback of position %lu", feedback->feadback[feedback->feadback.size()-1]);
  }

int main(int argc, char **argv){

    ros::init(argc,argv, "actionClient1");

    // create the action client
    // true causes the client to spin its own thread
    actionlib::SimpleActionClient<test_action_pkg::testAction> ac("test",true);

    ROS_INFO_STREAM("Waiting for action server to start.");
    //wait for the action server to start
    ac.waitForServer(); //will wait for infinite time

    ROS_INFO_STREAM("Action server started, sending goal");

  
    test_action_pkg::testActionFeedback feedback;
    goal.goal=10;
    ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    
    //wait for the action to return
   /*
    bool finished_before_timeout = ac.waitForResult();


    if (finished_before_timeout){
        actionlib::SimpleClientGoalState state=ac.getState();
        ROS_INFO_STREAM("Action finished: "<<state.toString().c_str());
    }
    else{
        ROS_INFO_STREAM("Action did finish before the time out.");
    }
*/
    ros::spin();
    //exit

    return 0;    
}