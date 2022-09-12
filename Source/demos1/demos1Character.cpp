// Copyright Epic Games, Inc. All Rights Reserved.

#include "demos1Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "PickUp1.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NewGameInstance.h"
#include "NewSaveGame.h"
//#include "OriginPlayerController.h"
#include "CantTouch.h"
#include "NewPlayerController.h"
#include "obstacel.h"
#include "PickUp2.h"
#include "PickUp3.h"
#include "Portal.h"
#include "Kismet/KismetSystemLibrary.h"
//#include "StatsViewer/Public/StatsViewerUtils.h"

//////////////////////////////////////////////////////////////////////////
// Ademos1Character

Ademos1Character::Ademos1Character()
{

	//

	MyCoin = 0;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
    //
	UE_LOG(LogTemp,Warning,TEXT("构造"));
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void Ademos1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//
	//PlayerInputComponent->BindAction("Pause",IE_Pressed,this,&Ademos1Character::PauseIf);
	PlayerInputComponent->BindAction("Over",IE_Pressed,this,&Ademos1Character::SaveGame);
	PlayerInputComponent->BindAction("readFile",IE_Pressed,this,&Ademos1Character::LoadGame);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &Ademos1Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &Ademos1Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &Ademos1Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &Ademos1Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &Ademos1Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &Ademos1Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &Ademos1Character::OnResetVR);
}


void Ademos1Character::OnResetVR()
{
	// If demos1 is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in demos1.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}
void Ademos1Character::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&Ademos1Character::BeginOverlap);
	//GetCapsuleComponent()->AddForce(FVector(a,b,c));
	
}
void Ademos1Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void Ademos1Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void Ademos1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void Ademos1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void Ademos1Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void Ademos1Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
void Ademos1Character::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UNewGameInstance* GI = Cast<UNewGameInstance>(GetGameInstance());
		if (GetGameInstance())
		{
			if (OtherActor->IsA(APickUp1::StaticClass()))
			{
			GI->SetCoinCount(GI->GetCoinCount()+1);
			temp = GI->PassLevel(CurLevel);
			UE_LOG(LogTemp,Warning,TEXT("CoinCOunt = %d"),GI->CoinCount);
			MyCoin++;
			OtherActor->Destroy();
		     }
			else if(OtherActor->IsA(APickUp2::StaticClass()))
			{
				GI->SetCoinCount(GI->GetCoinCount()+3);
				temp = GI->PassLevel(CurLevel);
				MyCoin+=3;
				OtherActor->Destroy();
			}
			else if(OtherActor->IsA(Aobstacel::StaticClass()))
			{
				GI->Level02Move =true;
			}
			else if(OtherActor->IsA(APickUp3::StaticClass()))
			{
				GI->SetCoinCount(GI->GetCoinCount()+5);
				temp = GI->PassLevel(CurLevel);
				MyCoin+=5;
				OtherActor->Destroy();
			}
			else if(OtherActor->IsA(ACantTouch::StaticClass()))
			{
				GI->SetCoinCount(GI->GetCoinCount()-1);
				temp = GI->PassLevel(CurLevel);
				MyCoin--;
			}
			
	    }
	//UE_LOG(LogTemp,Warning,TEXT("temp = %d"),temp);
	if(MyCoin>=GI->PassLevel(CurLevel)&&OtherActor->IsA(APortal::StaticClass())){
		UWorld * World = GetWorld();
		UGameplayStatics::OpenLevel(World,NextLevel);
	}
}

void Ademos1Character::newPlay()
{
	UWorld * World = GetWorld();
	UGameplayStatics::OpenLevel(World,"Level_00");
}

void Ademos1Character::SaveGame()
{
	UNewSaveGame* Instance = Cast<UNewSaveGame>(UGameplayStatics::CreateSaveGameObject(UNewSaveGame::StaticClass()));
	if(Instance)
	{
		UE_LOG(LogTemp,Warning,TEXT("Instance is not null"));
		UNewGameInstance* GI = Cast<UNewGameInstance>(GetGameInstance());
		Instance->PlayerSlot.CoinBank =GI->CoinCount;
		Instance->PlayerSlot.CurLevel = CurLevel;
	}
	UGameplayStatics::SaveGameToSlot(Instance,TEXT("SaveFile"),0);
	//游戏结束
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("QUIT");
}
void Ademos1Character::LoadGame()
{
	UNewSaveGame* Instance = Cast<UNewSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveFile"),0));
	if(Instance)
	{
		CurLevel = Instance->PlayerSlot.CurLevel;
		UNewGameInstance* GI = Cast<UNewGameInstance>(GetGameInstance());
		GI->SetCoinCount(Instance->PlayerSlot.CoinBank);
		UWorld * World = GetWorld();
		UGameplayStatics::OpenLevel(World,CurLevel);
	}
}
int Ademos1Character::CurCoin()
{
	return MyCoin;
}
int Ademos1Character::AllCoin()
{
	UNewGameInstance* GI = Cast<UNewGameInstance>(GetGameInstance());
	return GI->CoinCount;
}
FString Ademos1Character::GetCurLevel()
{
	return CurLevel.ToString();
}
void Ademos1Character::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp,Warning,TEXT("%f"),GetActorLocation().Z);
	if((GetActorLocation().Z<-500.f&&((CurLevel=="Level_03"||CurLevel=="Level_04")||CurLevel=="Level_02")||CurCoin()<-2))
	{
		DeadGame();
		//UE_LOG(LogTemp,Warning,TEXT("character location is down"));
	}
}
FString Ademos1Character::GetCurLevelManage()
{
	if(CurLevel =="Level_00")return  L"关卡一：杀出新手村  任务：收集五枚铜币 （注意可以浮动的踏板）";
	 else if(CurLevel =="Level_01")return  L"关卡二：旋转跳跃 任务：得到5个积分（两条线路，注意消失的踏板）";
	 else if(CurLevel =="Level_02")return  L"关卡三：摩天大厦  任务：冲向塔顶，拾取金币（小心有些踏板可不简单）";
	 else if(CurLevel =="Level_03")return  L"关卡四：无尽之路  任务：拾取所有硬币并到达终点（不要跳入深渊）";
	 else if(CurLevel =="Level_04")return L"关卡五：诸神黄昏   任务：到达终点，不要被炸弹碰到3次（注意躲避移动的炸弹）";
	return  L" ";
}
void Ademos1Character::DeadGame()
{
	UNewSaveGame* Instance = Cast<UNewSaveGame>(UGameplayStatics::CreateSaveGameObject(UNewSaveGame::StaticClass()));
	if(Instance)
	{
		UE_LOG(LogTemp,Warning,TEXT("Instance is not null"));
		UNewGameInstance* GI = Cast<UNewGameInstance>(GetGameInstance());
		Instance->PlayerSlot.CoinBank =GI->CoinCount;
		Instance->PlayerSlot.CurLevel = CurLevel;
	}
	UGameplayStatics::SaveGameToSlot(Instance,TEXT("SaveFile"),0);
	UWorld * World = GetWorld();
	UGameplayStatics::OpenLevel(World,"down");
}
