#include "Monde.h"
#include <iostream>

int main()
{
	float reductionV(0.f);

	reductionV = -0.1f;
	Monde monde(reductionV);
	monde.run();
}
