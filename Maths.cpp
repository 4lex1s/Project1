#include "Maths.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

float Distance(sf::Vector2f point1, sf::Vector2f point2)
{
	float diffX;
	float diffY;

	diffX = (point1.x - point2.x)*(point1.x - point2.x);
	diffY = (point1.y - point2.y)*(point1.y - point2.y);
	float resultat = sqrt(diffX + diffY);
	//std::cout << resultat << std::endl;
	return resultat;
}

float valeurAbsolue(float valeur)
{
	if (valeur < 0)
	{
		return valeur * -1;
	}
	else
	{
		return valeur;
	}
}
