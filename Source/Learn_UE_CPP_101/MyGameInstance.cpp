// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"
#include "UObject/ConstructorHelpers.h"



UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructed!!!!!!!!!!!!!!!!!!!!!!!"));
	//static ConstructorHelpers::FObjectFinder<UWorld> World2(TEXT("/Game/NewWorld"));

	//NextWorld = World2.Object;
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Initialized!!!!!!!!!!!!!!!!!!!!!!!"));
	//UGameplayStatics::DeleteGameInSlot("Slot_00", 0);
	SaveSlot = FString("Slot_00");
	LoadStats();
	
	
	
}

void UMyGameInstance::Shutdown()
{
	SaveStats();
	Super::Shutdown();
	
}

void UMyGameInstance::SaveStats()
{
	
	if (!SaveGameObject)
	{
		SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		SaveGameObject->bAbility = bAbilities;
		SaveGameObject->Threshold = Thershold;
		const bool bSaveSuccess = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlot, 0);
	}
	else
	{
		SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		SaveGameObject->bAbility = bAbilities;
		SaveGameObject->Threshold = Thershold;
		const bool bSaveSuccess = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlot, 0);
	 } 
}	

void UMyGameInstance::LoadStats()
{
	if(UGameplayStatics::DoesSaveGameExist(SaveSlot, 0))
	{ 
		USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveSlot, 0);
		SaveGameObject = Cast<UMySaveGame>(LoadedGame);
		bAbilities = SaveGameObject->bAbility;
		Thershold = SaveGameObject->Threshold;
	}
	else if (!SaveGameObject) //will only execute in the first time ever that a savegame was created with a particular slot name
	{
		SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		const bool bSaveSuccess = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlot, 0);
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("SaveGameObject Created!!!!!!!!!!!!!!!!!"));
	}
	
}

void UMyGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString("World Has now Changed!!!"));
	
	/*
	
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue,
	FString::Printf(TEXT("World Has now Changed!!! INTO: %s"), *(GetWorld()->PersistentLevel->LevelScriptActor.GetClass()->GetName())));


		THE IMPORATANT THING: " GetWorld()->PersistentLevel->LevelScriptActor.Get... "
	*/


	/*
	Levels:
		
		- a level (ULevel) is a collection of actors and objects. levels are contained within a world.
		  the current ULevel we are in is the PersistantLevel("GetWorld()->PersistentLevel->..."). This value will be updated when the level changes

		-  The World (UWorld) is the top level object representing a map or a sandbox in which Actors and Components will exist and be rendered.  
		   A World can be a single Persistent Level with an optional list of streaming levels that are loaded and unloaded via volumes and blueprint functions
		   or it can be a collection of levels organized with a World Composition/Partition.
		   In a standalone game, generally only a single World exists except during seamless area transitions when both a destination and current world exists.
		   In the editor many Worlds exist: The level being edited, each PIE instance, each editor tool which has an interactive rendered viewport, and many more.
		   another way  think of the UWorld as the rendered result of a UE viewport, which may contain any actor(s) in it - while these actors would all be attributed to the 
		   level they are actually in.

		- LevelScriptActor is the c++ version of a level BP.
		  The level scripting actor, initialized under the Persistant level ULevel, ("GetWorld()->PersistentLevel->LevelScriptActor").  
		  This handles all level scripting, where all of your level functionality will exist in.
		  This will be the only class you will need to subclass in order to establish and control level related functionality.
		  The LSA is best used to create blueprint callable functions that can be inherited by the level blueprint.

		- AWorldSettings is the container for many settings related with this world, AI navigation, Audio reverbs submixes, lighting settings, and many more...
		  it is initialized on runtime by the ULevel/UWorld object
		  ?This class should be subclassed only if you need to use World Partition, or in an online scenario that needs the PauserPlayerState info for pause in an online game setup.
		   Otherwise, you should simply use the WorldSettings tab provided in the Editor.

		- FWorldContext is a struct that is defined under GEngine. 
		  It is a context for dealing with UWorlds at the engine level. As the engine brings up and destroys world, we need a way to keep straight
		  what world belongs to what.
		 
			WorldContexts can be thought of as a track. By default we have 1 track that we load and unload levels on. Adding a second context is adding
			a second track; another track of progression for worlds to live on.
		 
				For the GameEngine, there will be one WorldContext until we decide to support multiple simultaneous worlds.
				For the EditorEngine, there may be one WorldContext for the EditorWorld and one for the PIE World.
		 
						FWorldContext provides both a way to manage 'the current PIE UWorld*' as well as state that goes along with connecting/travelling to
						new worlds.
		 
							FWorldContext should remain internal to the UEngine classes. Outside code should not keep pointers or try to manage FWorldContexts directly.
							Outside code can still deal with UWorld*, and pass UWorld*s into Engine level functions. The Engine code can look up the relevant context
							for a given UWorld*.
		 
								For convenience, FWorldContext can maintain outside pointers to UWorld*s. For example, PIE can tie UWorld* UEditorEngine::PlayWorld to the PIE
								world context. If the PIE UWorld changes, the UEditorEngine::PlayWorld pointer will be automatically updated. This is done with AddRef() and
								SetCurrentWorld().
	
	
	*/
	FSoftObjectPath path = FSoftObjectPath("/Game/NewWorld.NewWorld");

	TSoftObjectPtr<UWorld> NewMap(path);
	const UWorld* MyWorld = NewMap->GetWorld();
	if (NewWorld == MyWorld)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("New World IS TRUE"));
		//UE_LOG(LogTemp, Warning, TEXT("New World IS TRUE"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("New World FAIL"));
		//UE_LOG(LogTemp, Warning, TEXT("New World FAIL"));
	}
	
}

void UMyGameInstance::DoSomething()
{
	FTimerHandle UnusedHandle;
	GetTimerManager().SetTimer(UnusedHandle, this, &UMyGameInstance::ActuallyDoSomething, 3.0f, false);
	if (GetWorld()->GetTimerManager().TimerExists(UnusedHandle))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString("TimerManger is global - and the GameInstance and the World share the same one"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("TimerManager is local - an object that contains an FTimerManager member in it, will not know of timers and handles that belong to a different object"));
	}
	FTimerDelegate TD;
	TD.BindUFunction(this, FName("Manipulate"), EVariantTypes::Custom);
	GetTimerManager().SetTimerForNextTick(TD);
}

void UMyGameInstance::ActuallyDoSomething()
{
	//UGameplayStatics::OpenLevel(GetWorld(), "NewWorld");

	
	FSoftObjectPath path = FSoftObjectPath("/Game/NewWorld.NewWorld");

	TSoftObjectPtr<UWorld> NewMap(path);
	const UWorld* MyWorld = NewMap->GetWorld();

	
	//UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NewMap);
	
	//WorldContext->AddRef(NewMap->ToSoft);
	
	//WorldContext->AddRef(MyWorld);
	//WorldContext->SetCurrentWorld(MyWorld);

	/*
	for (FWorldContext Element : GEngine->GetWorldContexts())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("World Context: %s"), *Element.StaticStruct()->GetName()));
	}
	*/
	/*
	So we have to understand what are:
		-UWorld
		-WorldContext
		-LevelScript (+ULevel?)
		-AWorldSettings
		-Where does "GetWorld()->GetCurrentLevel()->" goes on to?
	
	
	But in the order of:
		-LevelScriptActor and it's connection wo the Level BP
		-How to do level changes in the game instance, how to use the OnWorldChanged() function
		-What are UWorlds and Ulevels, and what is the difference between them? how are they used?
		-FWorldContext vs. UWorld
		-AWorldSettings/UWorldSettings 


	*/
}

void UMyGameInstance::Manipulate()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 2.5f);
}

