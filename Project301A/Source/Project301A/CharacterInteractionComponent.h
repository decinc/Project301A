// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWorldCustomGravityChangedSignature, FVector, newGravity);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT301A_API UCharacterInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInteraction")
	float RaycastRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInteraction")
	FVector TraceBoxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInteraction")
	TArray<TEnumAsByte<EObjectTypeQuery> > TracingObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInteraction")
	TArray<AActor*> TraceIgnoreList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInteraction")
	bool TraceDebugDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInteraction")
	UMaterialInterface *mat_highlight;

	UPrimitiveComponent *hit_comp_prev;
	UMaterialInterface *mat_org;

	UPROPERTY(BlueprintReadWrite, Category = "CharacterInteraction")
	bool trace_test; 

	UPROPERTY(BlueprintReadWrite, Category = "CharacterInteraction")
	FHitResult hit;

	USceneComponent *CharacterShapeComponent;

public:	
	// Sets default values for this component's properties
	UCharacterInteractionComponent(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(
		float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void OnDestroy(bool AbilityIsEnding);

		
	UFUNCTION(BlueprintCallable, Category = "Character")
	void RegisterCharacterMesh(USceneComponent *Comp) {
		CharacterShapeComponent = Comp;
	}

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void EventLeftMouseClickPressed();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void EventLeftMouseClickReleased();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void EventRightMouseClickPressed();
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void EventRightMouseClickReleased();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FWorldCustomGravityChangedSignature OnWorldCustomGravityChanged;

	UFUNCTION()
	void OnWorldCustomGravityChanged_internal(FVector newGravity);
	
};
