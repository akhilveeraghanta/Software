#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <dynamic_reconfigure/Config.h>
#include <dynamic_reconfigure/Reconfigure.h>
#include <util/parameter/parameter.h>
#include <thunderbots/ParamsConfig.h>


void callback(param_server::ParamsConfig &config, uint32_t level) {
	std::cerr<<"GETTING HERE"<<std::endl;
	//save the file here
}


int main(int argc, char **argv) {
    //init node
    ros::init(argc, argv, "dynamic_param");
    ros::NodeHandle node_handle;

    //setup dynamic reconfigure server
    dynamic_reconfigure::Server<param_server::ParamsConfig> server;
    dynamic_reconfigure::Server<param_server::ParamsConfig>::CallbackType f;

    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);

    ros::service::waitForService("/parameters/set_parameters", 1);
    ros::ServiceClient client = node_handle.serviceClient<dynamic_reconfigure::Reconfigure>("/parameters/set_parameters");

    //create configuration message
    dynamic_reconfigure::Reconfigure srv;

    //get all configuration structs
    srv.request.config.ints = Parameter<int>::getConfigStruct().ints;
    srv.request.config.strs = Parameter<std::string>::getConfigStruct().strs;
    srv.request.config.doubles = Parameter<double>::getConfigStruct().doubles;
    srv.request.config.bools = Parameter<bool>::getConfigStruct().bools;

    std::cerr<<srv.request.config<<std::endl;

    //call the service to set params
    ROS_INFO("Spinning node");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    if(client.call(srv)) {
        ROS_INFO("all parameters have been configured");
    } else {
        ROS_FATAL("paramtrs have not been configured, showing cached values");
    }
    ros::waitForShutdown();
    return 0;
}
