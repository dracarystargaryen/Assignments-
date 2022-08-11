#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

Game::Game() 
	: m_pStateMachine(nullptr)
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine != nullptr)
	{
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}
}


bool Game::Load() {
	return m_level.Load("Level8.txt", m_player.GetXPositionPointer(), m_player.GetXPositionPointer());

}
void Game::Run() {
	Draw();

	m_isGameOver = Update();

	if (m_isGameOver) {
		Draw();
	}
}

void Game::Deinitialize()
{
	if (m_pStateMachine != nullptr)
		m_pStateMachine->Cleanup();
}


bool Game::IsGameOver() {
	return m_isGameOver;
}

bool Game::Update() {

}

void Game::Draw() {
	m_pStateMachine->DrawCurrentState();
}