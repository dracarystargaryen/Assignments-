#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

Game::Game() {
	: m_isGameOver(false)
}
Game::~Game() {

}

bool Game::Load() {

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


bool Game::IsGameOver() {
	return m_isGameOver;
}

bool Game::Update() {

}

void Game::Draw() {

}