// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Ball.h"


// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick"));
	SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetBoxExtent(FVector(25.0f, 10.0f, 10.0f));

	RootComponent = BoxCollision;

	//new agregation of the class ballbound



}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
	

	
}

void ABrick::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweet, const FHitResult& SweepResult)
{

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABrick::OnOverlapBegin);
	

		if (OtherActor->ActorHasTag("Ball")) {
			ABall* MyBall = Cast<ABall>(OtherActor);

			FVector BallVelocity = MyBall->GetVelocity();
			BallVelocity *= (SpeedModifierOnBounce - 1.0f);

			MyBall->GetBall()->SetPhysicsLinearVelocity(BallVelocity, true);

			this->Destroy();

		
		}
		
		


}


void ABrick::DestroyBrick()
{
	this->Destroy();

}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	 
	const FVector Movimiento = Direccion * Velocity * DeltaTime;
	if (Movimiento.SizeSquared() <= 25.0f) {
		const FRotator NewRotacion = FRotator(0.0f, -180.0f, 0.0f);
		FHitResult hit(1.0f);
		RootComponent->MoveComponent(Movimiento, NewRotacion, true, &hit);
		Direccion = FVector(-1.0f, 0.0f, 0.0f);
	}
	else {
		const FRotator NewRotacion = FRotator(90.0f, 180, 0.0f);
		FHitResult hit(1.0f);
		RootComponent->MoveComponent(Movimiento, NewRotacion, true, &hit);
		Direccion = FVector(1.0f, 0.0f, 0.0f);
		
	}
}

