#include <ros/ros.h>
#include "actionlib/server/simple_action_server.h"
#include "test_action_pkg/testAction.h"

class TestAction{
    protected:
        ros::NodeHandle nh;
        //Node handle instance must be created before this line. Otherwise strange error occurs.
        actionlib::SimpleActionServer<test_action_pkg::testAction> as;

        std::string action_name;
        //create message that are used to published feedback/rezult
        test_action_pkg::testFeedback feedback;
        test_action_pkg::testResult result;

    public:

        TestAction(std::string name):
        as(nh,name,boost::bind(&TestAction::executeCB,this, _1),false),
        action_name(name)
        {
            as.start();
            ROS_INFO_STREAM("Server start!!!");
        }

        ~TestAction(void){
            ROS_INFO_STREAM("Server deleted!!!");
        }

        void executeCB(const test_action_pkg::testGoalConstPtr &goal)
        {

            
            //helper variables
            ros::Rate rate(1);
            bool success=true;

            //push_back the seeds for the test feedback
            feedback.feadback.clear(); //clear feadback
            feedback.feadback.push_back(0); //first

            //publich info to the console for the user
            ROS_INFO_STREAM(action_name.c_str()<<" Executing, creating test of goal "<< goal->goal);

            //start executing the action
            for(int i=0;i<goal->goal;i++){
                //check that preempt has not been requested by
                //the client
                if(as.isPreemptRequested() || !ros::ok()){
                    ROS_INFO_STREAM(action_name.c_str()<<" Preemted");
                    as.setPreempted();
                    success=false;
                    break;
                }
                feedback.feadback.push_back(feedback.feadback[i]+1);
                // publish the feedback
                as.publishFeedback(feedback);
                
                ROS_INFO_STREAM(action_name.c_str()<<" Executing, creating test of goal "<< goal->goal<<"\n");

                //this sleep is not necessary, the sequence is comuted at 1 Hz for demonstration purposes
                rate.sleep();
            } 

            if(success){
                result.rezult=feedback.feadback;
                ROS_INFO_STREAM(action_name.c_str()<<" Succeded");
                //set the action state to succeeded
                as.setSucceeded(result);
            }
        }
};

int main(int argc, char **argv){
    
    ros::init(argc,argv,"test");
    TestAction test("test");

    ros::spin();

    return 0;    
}