#pragma once

#include "Players.h"

class Bullets : public Player
{
private:
	int client;

	float vX;
	float vY;

public:
	Bullets();
	~Bullets();

	int GetClient();
	void SetClient(int c);
	void SetVector(int dx, int dy);

	void Update(Timer time);
	
};

