// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "demos1Character.generated.h"

UCLASS(config=Game)
class Ademos1Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	Ademos1Character();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//
	UPROPERTY(EditAnywhere,Category="varibles")
	int MyCoin;
	UPROPERTY(EditAnywhere,Category="varibles")
	FName NextLevel;
	UPROPERTY(EditAnywhere,Category="varibles")
	FName CurLevel;

	
	
protected:
	//
	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		

	/** Resets HMD orientation in VR. */
	void OnResetVR();
	 

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);


	

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	virtual void Tick(float DeltaTime) override;
	//
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame();
	UFUNCTION(BlueprintCallable)
	void newPlay();
	UFUNCTION(BlueprintCallable)
	int CurCoin();
	UFUNCTION(BlueprintCallable)
	int AllCoin();
	UFUNCTION(BlueprintCallable)
	FString GetCurLevel();
	UFUNCTION(BlueprintCallable)
	FString GetCurLevelManage();
	UPROPERTY(EditAnywhere)
	int temp;
	UPROPERTY(EditAnywhere)
	float a;
	UPROPERTY(EditAnywhere)
	float b;
	UPROPERTY(EditAnywhere)
	float c;
	UFUNCTION()
	void DeadGame();
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

