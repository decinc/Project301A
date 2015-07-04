// Fill out your copyright notice in the Description page of Project Settings.

#include "Project301A.h"
#include "DynamicActor.h"
//#include "Character/CharacterInteractionComponent.h"
#include "Character/GravityCharacter.h"
ADynamicActor::ADynamicActor(const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer), IsHold(false)
{
}



void ADynamicActor::LiftKeyPressed_Implementation(const FHitResult &hit)
{
	//************************
	// to write
	// hold object code (carry)

	AGravityCharacter* myCharacter = dynamic_cast<AGravityCharacter*>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (myCharacter == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("There isn't a GravityCharacter or it is not the derived class of GravityCharacter"));
		return;
	}
	
	if (!IsHold)
	{
		for (UStaticMeshComponent* MeshComponent : MeshComps)
		{
			MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			MeshComponent->SetSimulatePhysics(false);
		}

		this->K2_AttachRootComponentTo(myCharacter->GetMesh(), "RightHandSocket", EAttachLocation::SnapToTarget, true);
		IsHold = true;
		myCharacter->CharacterInteraction->SetHoldingActor(this);
	}
	else
	{
		for (UStaticMeshComponent* MeshComponent : MeshComps)
		{
			MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			MeshComponent->SetSimulatePhysics(true);
		}
		this->DetachRootComponentFromParent(true);
		IsHold = false;
		myCharacter->CharacterInteraction->SetHoldingActor(NULL);
	}

}

void ADynamicActor::CacheAllSMComponents()
{
	MeshComps.Empty();
	this->GetComponents<UStaticMeshComponent>(MeshComps);
}