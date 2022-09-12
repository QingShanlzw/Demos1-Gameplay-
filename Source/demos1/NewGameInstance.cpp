// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGameInstance.h"

UNewGameInstance::UNewGameInstance()
{
    CoinCount =0;
    Level02Move =false;
}
UNewGameInstance* UNewGameInstance::GetInstance()
{
    UNewGameInstance* instance = nullptr;

    if (GEngine)
    {
        FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
        instance = Cast<UNewGameInstance>(context->OwningGameInstance);
    }
    return instance;
}
int  UNewGameInstance::GetCoinCount(){return CoinCount;}
void UNewGameInstance::SetCoinCount(int c)
{
    //UE_LOG(LogTemp,Warning,TEXT("测试set函数 coincount = %d"),CoinCount);
   // UE_LOG(LogTemp,Warning,TEXT("测试set函数 ct = %d"),c);
    CoinCount =c;
}
int UNewGameInstance::PassLevel(FName Level)
{
    //UE_LOG(LogTemp,Warning,TEXT("Level == %s"),Level);
    if(Level=="level_00")return 5;
    else if(Level=="level_01")return 5;
    else if(Level=="level_02")return 5;
    else if(Level=="level_03")return 15;
    else if(Level=="level_04")return -2;
    else if(Level=="level_05")return 5;
    else if(Level=="level_06")return 5;
    UE_LOG(LogTemp,Warning,TEXT("no case"));
    return 1;
}

