#include <FTM_Manager.hpp>

FTM_SafetyFirst::FTM_SafetyFirst() : FTM_Strategy()
{
	name_="SAFETY_FIRST";
}

void FTM_SafetyFirst::execute(FTM_Manager* myManager)
{
	cout<<endl<<"------------------------------" << endl;
	active_or_recovery_rules_ = myManager->getActiveOrRecoveryRules();
	cout<<"Active or in Recovery rules : ";
	myManager->debugDisplayRulesId(active_or_recovery_rules_);

	if(active_or_recovery_rules_.size()==1)
	{
		cout<<"Only one active or recovery rule, so we just activate its recovery : ";
		myManager->debugDisplayRMId(active_or_recovery_rules_);
		myManager->doRecovery(active_or_recovery_rules_);
	}
	else if(active_or_recovery_rules_.size()>1)
	{
		cout<<"There are more than one active or recovery rules, maybe one dominates the others..."<<endl;
		dominant_=myManager->findDominant(active_or_recovery_rules_);
		cout<<"Dominant rules : ";
		myManager->debugDisplayRulesId(dominant_);

		if(dominant_.size()==1)
		{
			cout<<"Yes, one rule dominates the others, let's activate its recovery :";
			myManager->debugDisplayRMId(dominant_);
			myManager->doRecovery(dominant_);
		}

		else
		{
			cout<<"No, there are no unique dominant rule. Maybe one of their recovery dominates the others..."<<endl;
			dominant_recov_=myManager->findDominantRecovery(dominant_);
			cout<<"Dominant Recovery :";
			myManager->debugDisplayRMId(dominant_recov_);

			if(dominant_recov_.size()==1)
			{
				cout<<"Yes, one RM dominates the others, let's activate it : ";
				myManager->debugDisplayRMId(dominant_recov_);
				myManager->doRecovery(dominant_recov_);
			}

			else
			{
				cout<<"No, there are no unique dominant RM. Let's activate the Lowest Common Dominant"<<endl;
				common_dominant_=myManager->findLowestCommonDominant(dominant_);
				cout<<"The common dominant is :";
				myManager->debugDisplayRulesId({common_dominant_});
				cout<<"so we activate its recovery : ";
				myManager->debugDisplayRMId({common_dominant_});
				myManager->doRecovery({common_dominant_});
			}
		}
	}
}
