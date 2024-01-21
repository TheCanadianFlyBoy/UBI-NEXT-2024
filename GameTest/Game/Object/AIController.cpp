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
	if (PossessedShip)
		PossessedShip->FireControlComponent->AddAzimuth(PI / 2.f);
}

//Main logic loop
void AIController::Update(float DeltaTime)
{

	Debug::PrintLine(std::to_string(AngleAdjustment));
	Debug::PrintLine(std::to_string(DistanceToTarget));
	Debug::PrintLine(std::to_string(DistanceToNearest));
	Debug::PrintLine(std::to_string(Impact.x));
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
				
				std::uniform_real_distribution<> RandomGen(-0.2f, 0.2f);


				//Use a point
				PossessedShip->UseAction();
				//Get a random firing solution
				PossessedShip->FireControlComponent->AddAzimuth(ENGINE->RandRangeF(-0.3f, 0.3f));
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

	//
	////Get ships
	//std::vector<Actor*> IgnoredActors;
	////Convert
	//for (auto& Actors : State->GetCurrentPlayer().Fleet)
	//{
	//	IgnoredActors.push_back(Actors);
	//}
	//Vector2 Origin = PossessedShip->GetActorLocation();
	//Actor* Nearest = GetWorld()->GetNearestActor(Origin, IgnoredActors);
	//Vector2 Target = Nearest->GetActorLocation();
	//float InitialSpeed = 10.f;
	//
	//
	//Vector2 Delta = Target - Origin;
	//float Distance = Delta.x;
	////Get elevation
	//float Height = Delta.y;
	//float EstTime = Distance / 10
	//
	//float DirectAngle

	return Vector2(0.f);
}