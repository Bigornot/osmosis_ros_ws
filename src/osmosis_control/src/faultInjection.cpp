#include "faultInjection.hpp"

void FaultInjection::FaultInjectionFSM()
{
	switch(state_)
	{
		case IDLE:
			if(askFI())
				state_=FAULT_INJECTION;
			break;

		case FAULT_INJECTION:
			doFI();
			state_=IDLE;
			break;

		default: break;
	}
}

bool FaultInjection::askFI()
{
	bool ok=false;

	list_FI_.clear();
	string select;

	cout << endl << endl;
	cout << "Select the desired fault to inject :" << endl;
	cout << "0-Reset fault injection" << endl;
	cout << "1-Prohibited Area" << endl;
	cout << "2-Cmd not updated" << endl;
	cout << "3-WrongValue cmd" << endl;
	cout << "4-Node Crash Control" << endl;
	cout << "5-Node Crash" << endl;
	cout << "6-Loc not updated" << endl;
	cout << "7-Node Crash Loc" << endl;
	cout << "12-Rate no cmd" << endl;
	cout << "13-Rate WrongValue cmd" << endl;
	cout << "16-Rate Loc" << endl << endl;

	cout << "Selected : ";
	getline(cin, select);
	if(parse(select))
		ok=true;

	else
		cout << "ERROR" << endl;

	return ok;
}

bool FaultInjection::parse(string select)
{
	vector<string> infos;
	infos.push_back("");

	cout << "select : " << select << endl;

	for(int i=0; i<select.size(); i++)
	{
		if(select[i]!=' ')
			infos[infos.size()-1].push_back(select[i]);
		else
		{
			infos.push_back("");
		}
	}

	for(int i=0; i<infos.size(); i++)
		list_FI_.push_back(stoi(infos[i]));

	return infos.size()>0;
}

void FaultInjection::doFI()
{
	string command;
	std_msgs::Bool data;
	ros::Duration wrong_value_on(0.5);
	ros::Duration wrong_value_off(3);
	ros::Duration cmd_on(3);
	ros::Duration cmd_off(2);
	ros::Duration loc_on(3);
	ros::Duration loc_off(3);

	for(int i=0; i<list_FI_.size(); i++)
	{
		switch(list_FI_[i])
		{
			case 0:
				data.data=false;
				FI1_pub_.publish(data);
				FI2_pub_.publish(data);
				FI3_pub_.publish(data);
				FI6_pub_.publish(data);
				break;
			case 1:
				data.data=true;
				FI1_pub_.publish(data);
				break;
			case 2:
				data.data=true;
				FI2_pub_.publish(data);
				break;
			case 3:
				data.data=true;
				FI3_pub_.publish(data);
				break;
			case 4:
				command="rosnode kill /HMI_node /mission_manager_node /graph_planner_node /osmosis_control_node";
				system(command.c_str());
				break;
			case 5:
				command="rosnode kill /safety_pilot_node /joy_node /joy_teleop_node /teleop_node";
				system(command.c_str());
				break;
			case 6:
				data.data=true;
				FI6_pub_.publish(data);
				break;

			case 7:
				command="rosnode kill /localization_node";
				system(command.c_str());
				break;

			case 12:
				data.data=true;
				while(1)
				{
					if(data.data)
					{
						data.data=false;
						FI2_pub_.publish(data);
						cmd_off.sleep();
					}
					else
					{
						data.data=true;
						FI2_pub_.publish(data);
						cmd_on.sleep();
					}
				}
				break;

			case 13:
				data.data=true;
				while(1)
				{
					if(data.data)
					{
						data.data=false;
						FI3_pub_.publish(data);
						wrong_value_off.sleep();
					}
					else
					{
						data.data=true;
						FI3_pub_.publish(data);
						wrong_value_on.sleep();
					}
				}
				break;

			case 16:
				data.data=true;
				while(1)
				{
					if(data.data)
					{
						data.data=false;
						FI6_pub_.publish(data);
						loc_off.sleep();
					}
					else
					{
						data.data=true;
						FI6_pub_.publish(data);
						loc_on.sleep();
					}
				}
				break;

			defaul: break;
		}
	}
}

FaultInjection::FaultInjection()
{
	FI1_pub_ = nh_.advertise<std_msgs::Bool>("fault_injection_prohibited_area", 1);
	FI2_pub_ = nh_.advertise<std_msgs::Bool>("fault_injection_cmd_not_updated", 1);
	FI3_pub_ = nh_.advertise<std_msgs::Bool>("fault_injection_wrong_value_cmd", 1);
	FI6_pub_ = nh_.advertise<std_msgs::Bool>("fault_injection_loc_not_updated", 1);

	state_=IDLE;

	freq_=10;
}

void FaultInjection::run()
{
	ros::Rate loop_rate(freq_);
	while (nh_.ok())
	{
		FaultInjectionFSM();
		ros::spinOnce();
		loop_rate.sleep();
	}
}

int main(int argc, char** argv)
{
	//init the ROS node
	ros::init(argc, argv, "fault_injection_node");

	FaultInjection faultInjection;
	faultInjection.run();
}
