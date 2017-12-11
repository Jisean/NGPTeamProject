#include "Bullets.h"


Bullets::Bullets()
{
}


Bullets::~Bullets()
{
}

void Bullets::SetClient(int c)
{
	client = c;
}

int Bullets::GetClient()
{
	return client;
}

void Bullets::SetVector(int dx, int dy)
{
	vX = dx;
	vY = dy;
}

void Bullets::Update()
{
	Move(vX, vY);
}