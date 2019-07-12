#include <osmosis_control/FTM_Manager.hpp>

FTM_SafetyFirst::FTM_SafetyFirst() : FTM_Strategy()
{
	name_="SAFETY_FIRST";
}

void FTM_SafetyFirst::execute(FTM_Manager* myManager)
{
	cout<<endl<<"------------------------------" << endl;
	triggered_rules_ = myManager->getTriggeredFTM();
	cout<<"Triggered rules : ";
	myManager->debugDisplayFTMid(triggered_rules_);

	if(triggered_rules_.size()==1)
	{
		cout<<"Only one triggered rule, so we just activate its recovery : ";
		myManager->debugDisplayRMid(triggered_rules_);
		myManager->doRecovery(triggered_rules_);
	}
	else if(triggered_rules_.size()>1)
	{
		cout<<"There are more than one triggered rule, maybe one dominates the others..."<<endl;
		dominant_=myManager->findDominant(triggered_rules_);
		cout<<"Dominant rules : ";
		myManager->debugDisplayFTMid(dominant_);

		if(dominant_.size()==1)
		{
			cout<<"Yes, one rule dominates the others, let's activate its recovery :";
			myManager->debugDisplayRMid(dominant_);
			myManager->doRecovery(dominant_);
		}

		else
		{
			cout<<"No, there are no unique dominant rule. Maybe one of their recovery dominates the others..."<<endl;
			dominant_recov_=myManager->findDominantRecovery(dominant_);
			cout<<"Dominant Recovery :";
			myManager->debugDisplayRMid(dominant_recov_);

			if(dominant_recov_.size()==1)
			{
				cout<<"Yes, one RM dominates the others, let's activate it : ";
				myManager->debugDisplayRMid(dominant_recov_);
				myManager->doRecovery(dominant_recov_);
			}

			else
			{
				cout<<"No, there are no unique dominant RM. Let's activate the Lowest Common Dominant"<<endl;
				common_dominant_=myManager->findLowestCommonDominant(dominant_);
				cout<<"The common dominant is :";
				myManager->debugDisplayFTMid({common_dominant_});
				cout<<"so we activate its recovery : ";
				myManager->debugDisplayRMid({common_dominant_});
				myManager->doRecovery({common_dominant_});
			}
		}
	}
}
