#include "stdafx.h"
#include "AIController.h"

#include "../World/TurnBasedState.h"
#include "Ship.h"
#include "../Component/FireControlComponent.h"
#include "Projectile.h"

#include <random>
#include <chrono>
#include <ctime>

void AIController::OnBegin()
{
	Controller::OnBegin();

	//Save state pointer (static is fine since this should only happen once, and is crucial)
	State = static_cast<TurnBasedGameState*>(ThisWorld->GetWorldGameState());
}

//Main logic loop
void AIController::Update(float DeltaTime)
{

	//Not my turn, return
	if (State->GetCurrentPlayerID() != PlayerID) return;

	//Increment
	WaitTimer += DeltaTime * 0.001f;


	//Check if we can actually move
	if (WaitTimer >= WaitLength)
	{
		//Reset clock
		WaitTimer = 0.f;
		
		if (!PossessedShip)
		{
			//Check if we have actions left
			bool HasAction = false;
			//Case 1: find a ship
			for (Ship* ThisShip : State->GetCurrentPlayer().Fleet)
			{
				if (ThisShip->CanUseAction())
				{
					Possess(ThisShip);
					State->SetTurnState(ETurnState::Action);
					HasAction = true;
					return;
				}
			}

			//Case 2: end turn
			//No more actions! End
			if (!HasAction)
			{
				State->SetTurnState(ETurnState::End);
				//TODO end turn function
				return;
			}
		}

		//Case 3: do ship stuff
		if (PossessedShip) {
			//Set location
			SetActorLocation(PossessedShip);

			//Can use ship? Then use
			if (PossessedShip->CanUseAction())
			{
				
				std::uniform_real_distribution<> RandomGen(-0.9f, 0.9f);


				//Use a point
				PossessedShip->UseAction();
				//Get a random firing solution
				PossessedShip->FireControlComponent->AddAzimuth(-acosf(DifferenceToTarget.x));
				TrackedShot = PossessedShip->FireControlComponent->Fire();

				//Do trajectory calc
				EstimateTrajectory();

				//UnPossess();
				return;
			}
			
			//Back to selection
			UnPossess();
			State->SetTurnState(ETurnState::Select);
			


		}


	}
}

void AIController::SelectPhase(float DeltaTime)
{

}

void AIController::ActionPhase(float DeltaTime)
{
	if (PossessedShip->CanUseAction())
	{

	}
	else 
	{
		State->SetTurnState(ETurnState::Select);
	}
}


//Save ship
void AIController::OnPossess(Actor* InActor)
{
	Controller::OnPossess(InActor);

	PossessedShip = dynamic_cast<Ship*>(InActor);
}

void AIController::OnUnPossess()
{
	//Super
	Controller::OnUnPossess();

	PossessedShip = nullptr;
}

Vector2 AIController::EstimateTrajectory()
{

	DistanceToTarget = FLT_MAX;

	//Nullguard
	if (!TrackedShot) return Vector2(-1.f);

	Vector2 QueryPosition = TrackedShot->GetActorLocation();
	Vector2 Velocity = TrackedShot->GetComponentOfClass<CRigidBody>()->GetVelocity();

	for (int i = 0; i < 200; i++)
	{
		Velocity += 0.2f * 9.8f;
		QueryPosition += Velocity * 0.2f;

		//Get ships
		std::vector<Actor*> IgnoredActors;
		//Convert
		for (auto& Actors : State->GetCurrentPlayer().Fleet)
		{
			IgnoredActors.push_back(Actors);
		}

		Actor* Nearest = GetWorld()->GetNearestActor(QueryPosition, IgnoredActors);

		float DistanceToNearest = Nearest->GetActorLocation().DistanceFromSquared(QueryPosition);

		if (DistanceToNearest < DistanceToTarget)
		{
			DistanceToTarget = DistanceToNearest;
			DifferenceToTarget = QueryPosition - Nearest->GetActorLocation();
		}

	}

}