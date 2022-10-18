// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInterface.h"

// Add default functionality here for any IMyInterface functions that are not pure virtual.



void IMyInterface::Communicate()
{
	GEngine->AddOnScreenDebugMessage(-1, 19.0f, FColor::Red, __FUNCTION__);
}

/*
void IMyInterface::CommunicateBP()
{
	GEngine->AddOnScreenDebugMessage(-1, 19.0f, FColor::Red, __FUNCTION__);
}
*/