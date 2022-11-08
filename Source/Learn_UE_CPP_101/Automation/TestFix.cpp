// Fill out your copyright notice in the Description page of Project Settings.


#include "../Automation/TestFix.h"

#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(MyAutomationSpec, "System.Automation.Spec", EAutomationTestFlags::SmokeFilter | EAutomationTestFlags::ApplicationContextMask)
FString RunOrder;
END_DEFINE_SPEC(MyAutomationSpec)
void MyAutomationSpec::Define()
{
	xDescribe("A spec using BeforeEach and AfterEach", [this]()
		{
			BeforeEach([this]()
				{
					RunOrder = TEXT("A");
				});

			It("will run code before each spec in the Describe and after each spec in the Describe", [this]()
				{
					TestEqual("RunOrder", RunOrder, TEXT("A"));
				});

			AfterEach([this]()
				{
					RunOrder += TEXT("Z");
					TestEqual("RunOrder", RunOrder, TEXT("AZ"));
				});
		});
}
