#include <array>
#include <utility>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

#define ACTION_NUM 3
#define STATE_NUM 3


enum State { STABLE = 0, TOO_MUCH_PRESSURE, TOO_LITTLE_PRESSURE };
enum Action { WAIT = 0, ADD_WATER, RELEASE_WATER };
std::array<std::array<float, ACTION_NUM>, STATE_NUM> Q = { {0} };
std::array<std::string, ACTION_NUM> action_to_string = { "WAIT", "ADD WATER", "RELEASE WATER" };
std::array<std::string, ACTION_NUM> state_to_string = { "STABLE", "TOO MUCH PRESSURE", "TOO LITTLE PRESSURE" };


void printMatrix()
{
	using namespace std;
	cout << "Q Matrix" << endl << endl;
	for (int i = 0; i < STATE_NUM; i++)
	{
		for (int j = 0; j < ACTION_NUM; j++)
		{
			cout << "For state \"" << state_to_string[i] << "\" the action \"" << action_to_string[j] << "\" has a value of: " << Q[i][j] << endl;
		}
	}
}

State descState(float DescState) {
	if (DescState < 25.f) 
	{
		return State::TOO_LITTLE_PRESSURE;
	}
	else if (DescState > 75.f) 
	{
		return State::TOO_MUCH_PRESSURE;
	}
	else 
	{
		return State::STABLE;
	}
}

Action descAction(State Current_State) {
	
	float bestValue = Q[Current_State][0];
	
		for (size_t i = 0; i < ACTION_NUM; i++)
		{
			if (Q[Current_State][i] > bestValue) {
				bestValue = Q[Current_State][i];
			}
		}
		return static_cast<Action>(int(bestValue));
}

int main()
{
	srand(time(NULL));

	float system_pressure = 50.f;
	int iterator = 0;
	double reward = 0.5;

	while (system_pressure > 0)
	{
		std::cout << "System pressure is sitting at: " << system_pressure << "." << std::endl;
		std::cout << "reward is at: " << reward << "." << std::endl;

		// Describe State
		// TODO: Store a local variable that describes the current state

		  State Current_State = descState(system_pressure);
	

		// Choose Action
		// TODO: Store a local variable that explains what action the AI will perform

		  Action chosen_action = descAction(Current_State);		

		  std::cout << "current Action = \"" << action_to_string[chosen_action] << std::endl;
	

		switch (Current_State)
		{
		case State::STABLE:
			reward = 0.05;
			break;
		case State::TOO_MUCH_PRESSURE :
			reward = -0.05;
			break;
		case State::TOO_LITTLE_PRESSURE :
			reward = -0.05;
			break;
		default:
			// We should never reach this point
			// but its good to prepare for it just in case
			break;
		}

		//Update the Q-Matrix
		Q[Current_State][chosen_action] += reward;


		switch (chosen_action)
		{
		case Action::WAIT:
			break;
		case Action::ADD_WATER:
			system_pressure += (5);
			break;
		case Action::RELEASE_WATER:
			system_pressure -= (5);
			break;
		default:
			// We should never reach this point
			// but its good to prepare for it just in case
			break;
		}
		
		system_pressure -= (rand() % 4);
		std::cout << "System has lost some pressure." << std::endl;
		std::this_thread::sleep_for(500ms);
		iterator++;
	}
	printMatrix();

	std::cin.get();
}