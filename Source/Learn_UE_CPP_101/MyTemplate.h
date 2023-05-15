// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "UObject/ObjectMacros.h"
//#include "MyTemplate.generated.h"

/*
    - can only exist in .h file , no .cpp file included
    - cannot be directly supported by Reflection System
    - .h file will need to be included in a static function library, or wherever it is needed
*/

//TODO Define Template functions -------------------------------------------------------------------------------------------------------------------------------------
/*
    - if function is short, use FORCEINLINE as an optimization
*/
template <typename MyTType> FORCEINLINE void YourFunction() { return this; }


template <typename MyTType> static FORCEINLINE MyTType* 
SpawnAnyActor(UWorld* TheWorld, UClass* TheActor, const FVector& Loc, const FRotator& Rot, const bool bNoCollisionFail = true, AActor* Owner = NULL, APawn* Instigator = NULL) 
{
   if (!TheWorld) return NULL;
   if (!TheActor) return NULL;

   FActorSpawnParameters SpawnInfo;
   SpawnInfo.bNoFail = bNoCollisionFail;
   SpawnInfo.Owner = Owner;
   SpawnInfo.Instigator = Instigator;
   SpawnInfo.bDeferConstruction = false;
   return TheWorld->SpawnActor<MyTType>(TheActor, Loc ,Rot, SpawnInfo );
}

//TODO Define Template Classes -------------------------------------------------------------------------------------------------------------------------------------
/*
    - can use static functions when you need to call these functions without instantiating a class instance of the template
    - can use non static functions if the template is supposed to be instanced
*/
template <typename MyTType>
class UMyGenericClass : public UObject
{
public:
    /*
        UMyGenericClass()
        {}

        UMyGenericClass(AActor* _actor)
        {}
    */
   

    static FORCEINLINE MyTType* DoSomething(AActor* InActor) {
        UE_LOG(LogTemp, Warning, TEXT("The In Actor via the Template function is: %s"), *InActor->GetName());
        return NewObject<MyTType>(MyTType::StaticClass());
    }
};

template <typename ActorT, typename CompT>
class TMyContainer : public UObject //Can inherit from ue types if template is never instanced
{
public:
    /*
    TMyContainer()
    {}

    TMyContainer(AActor* _actor)
    {}
    */
    

    static FORCEINLINE ActorT* SpawnComponent(ActorT* InActor) {
        static int32 Count = 0;
        
        UE_LOG(LogTemp, Warning, TEXT("SpawnComp: Acotr in Template function is: %s"), *InActor->GetName());
        FName NN(FString::Printf(TEXT("%s_%d"), *CompT::StaticClass()->GetName(), Count));

        FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, false);
        CompT* NewComp = NewObject<CompT>(InActor, NN, EObjectFlags::RF_DefaultSubObject);
        NewComp->AttachToComponent(InActor->GetRootComponent(), TransformRules);
        
        //FString S = NewComp->GetComponentLocation().ToString();
        UE_LOG(LogTemp, Warning, TEXT("SpawnComp: Component in Template function is: %s"), *(NewComp->GetName()));
        UE_LOG(LogTemp, Warning, TEXT("SpawnComp: Component location is: %s"), *NewComp->GetComponentLocation().ToString());
        Count += 1;
        return InActor;
    }
};


template <typename T>
class TMyRealContainer : public TSet<T>  // Can NOT inherit from UObject if template is meant to be instanced
{

public:
    TMyRealContainer()
    {}

    TMyRealContainer(UObject* Obj)
    {}

    //TArray<T*> MyArray;

    

    FORCEINLINE void AddIndex(T Member) {
        //MyArray.Add(Member);
        //(*this).Add(Member);
        //this->Add(&*Member);
        this->Add(Member);
    }


    FORCEINLINE void PrintAll() {
        for (T Item : *this)
        {
            UE_LOG(LogTemp, Warning, TEXT("Index Is: %s"), *Item->GetName());
        }
        
    }
};

//Attempt to support Reflection Sys ------------------------------------------------------------------------------------------------------
/*
UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UMyTemplateBase : public UObject
{
    GENERATED_BODY()
};

template <typename T>
class UMyTemplate : public UMyTemplateBase
{
   
public:
    UMyTemplate()  
    {
        
    }

    int32 Count = 5431;
    TArray<T*> Indices;

    FORCEINLINE void AddIndex(T* Member) {
        Indices.Add(Member);
    }

    FORCEINLINE void PrintAll() {
        for (T* Index : Indices)
        {
            UE_LOG(LogTemp, Warning, TEXT("Index Is: %s"), *Index->GetName());
        }
    }

    FORCEINLINE T* DoSomething(T* InObj) {
        UE_LOG(LogTemp, Warning, TEXT("The In OBJ via the Template function is: %s"), *InObj->GetName());
    }
    
};

template<typename T>
struct TStructOpsTypeTraits<UMyTemplate<T>> : public TStructOpsTypeTraitsBase2<UMyTemplate<T>>
{
    enum
    {
        WithSerializer = true,
        WithCopy = true,
        WithIdenticalViaEquality = true
    };

    static void Serialize(FArchive& Ar, UMyTemplate<T>& Obj)
    {
        Ar << Obj.Count;
        Ar << Obj.Indices;
        UE_LOG(LogTemp, Warning, TEXT("Serializing: %d"), Obj.Count);
    }
};
*/
//TODO SHIT -------------------------------------------------------------------------------------------------------------------------------------
/*
class UMyGenericClass
{
public:
    UMyGenericClass()
    {}

    UMyGenericClass(AActor* _actor)
    {}
};

template<class T>
class UMyTemplateClass : public UMyGenericClass
{
public:
    UMyTemplateClass(AActor* _actor)
        : UMyGenericClass()
    {
        if (_actor)
        {
            MyComponent = _actor->CreateDefaultSubobject<T>("MyComp");
        }
    }

public:
    T* MyComponent = nullptr;
};

template<class T>
struct STag { using type = T; };

UCLASS()
class LEARN_UE_CPP_101_API UMyTemplate : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    UMyTemplate();
    template<class T>
    UMyTemplate(STag<T> _tag);

public:
    UMyGenericClass GenericClass;
};

template<class T>
UMyTemplate::UMyTemplate(STag<T> _tag)
{
    GenericClass = UMyTemplateClass<T>(this);
    PrimaryActorTick.bCanEverTick = true;
}*/

//TODO AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
/*
template<class T> //This is the argument list that the Template receives
//UCLASS(BlueprintType, Within=T) // Needed for reflection & serialization
class UMyTemplate : public UObject
{
	//GENERATED_BODY()
	
public:
    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Value;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray <TSubclassOf<T>> MyArray;

    //UFUNCTION(BlueprintCallable)
       T GetValue() const { return Value; }

    //UFUNCTION(BlueprintCallable)
    void SetValue(T InValue) { Value = InValue; }
    // Add more class members and methods here
};


// Define the serialization functions for your template class
template<class T>
struct TStructOpsTypeTraits<UMyTemplate<T>> : public TStructOpsTypeTraitsBase2<UMyTemplate<T>>
{
    enum
    {
        WithSerializer = true,
        WithCopy = true,
        WithIdenticalViaEquality = true
    };

    static void Serialize(FArchive& Ar, UMyTemplate& Obj)
    {
        Ar << Obj.MyArray;
    }
};
*/
//Make sure to replace MYGAME_API with the appropriate macro for your project.If you're still experiencing issues, it may be helpful to post a few of the error messages you're seeing.



//TODO AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
/*
template<typename T>
class LEARN_UE_CPP_101_API UMyTemplate : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        T MyProperty;

    // Add more members and methods here
};

struct LEARN_UE_CPP_101_API FTempStruct;

USTRUCT(BlueprintType, meta = (DisplayName = "Template Struct"))
struct LEARN_UE_CPP_101_API FTempStruct : public UMyTemplate<int32>
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Name;

    // Add more members and methods here
};

template<typename T>
struct TStructOpsTypeTraits<UMyTemplate<T>> : public TStructOpsTypeTraitsBase2<UMyTemplate<T>>
{
    enum
    {
        WithSerializer = true,
        WithCopy = true,
        WithIdenticalViaEquality = true
    };

    static void Serialize(FArchive& Ar, UMyTemplate<T>& Obj)
    {
        Ar << Obj.MyProperty;
    }
};

*/

//TODO AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
/*
template<typename T>
UCLASS(BlueprintType) // Needed for reflection & serialization
class LEARN_UE_CPP_101_API UMyTemplate : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        T MyProperty;

    // Add more members and methods here
};

template<typename T>

USTRUCT(BlueprintType, meta = (DisplayName = "Template Struct"))
struct LEARN_UE_CPP_101_API FTempStruct : public UMyTemplate<T>
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString Name;

    // Add more members and methods here
};

template<typename T>
struct TStructOpsTypeTraits<UMyTemplate<T>> : public TStructOpsTypeTraitsBase2<UMyTemplate<T>>
{
    enum
    {
        WithSerializer = true,
        WithCopy = true,
        WithIdenticalViaEquality = true
    };

    static void Serialize(FArchive& Ar, UMyTemplate<T>& Obj)
    {
        Ar << Obj.MyProperty;
    }
};


*/





