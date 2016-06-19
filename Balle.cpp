#include "Balle.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Balle::Balle() : mDeplacement(sf::Vector2f(0.f,0.f)), radius(3)
{
	mShape.setFillColor(sf::Color::Black);
	mCord = sf::Vector2f(0.f,0.f);
	mShape.setRadius(radius/2);
}

Balle::Balle(sf::Vector2f cord) : radius(3)
{
	mShape.setFillColor(sf::Color::Black);
	mCord = cord;
	mShape.setRadius(radius/2);
	mShape.setPosition(cord-sf::Vector2f(mShape.getRadius(),mShape.getRadius()));
}

sf::CircleShape Balle::getShape()
{
	return mShape;
}

void Balle::setPos(sf::Vector2f pos)
{
	mCord = pos;
	mShape.setPosition(sf::Vector2f(300.f, 300.f) - sf::Vector2f(mShape.getRadius(), mShape.getRadius()));
}

void Balle::Init()
{
	mDeplacement = sf::Vector2f(0.2f, -0.8f);
	mDeplacement *= 100.f;
}

void Balle::move(sf::Time deltaTime)
{
	mCord += mDeplacement * deltaTime.asSeconds();

	if (mCord.y < 20 + mShape.getRadius())
	{
		mCord.y = 20 + mShape.getRadius();
		mDeplacement.y = mDeplacement.y * -1;
	}

	if (mCord.y > 450 - mShape.getRadius())
	{
		mCord.y = 450 - mShape.getRadius();
		mDeplacement.y = mDeplacement.y * -1;
	}

	if (mCord.x < 25 + mShape.getRadius())
	{
		mCord.x = 25 + mShape.getRadius();
		mDeplacement.x = mDeplacement.x * -1;
	}

	if (mCord.x > 615 - mShape.getRadius())
	{
		mCord.x = 615 - mShape.getRadius();
		mDeplacement.x = mDeplacement.x * -1;
	}

	mShape.setPosition(mCord - sf::Vector2f(mShape.getRadius(), mShape.getRadius()));
}

void Balle::setDep(sf::Vector2f dep)
{
	mDeplacement += dep;
}

void Balle::reduction(sf::Time deltaTime, float reductionV)
{
	float reduction = 1-(reductionV*deltaTime.asSeconds());
	mDeplacement = mDeplacement*reduction;
}

void Balle::divise()
{
	mDeplacement = mDeplacement / 2.f;
}

sf::Vector2f Balle::getCord()
{
	return mCord;
}

sf::Vector2f Balle::getDep()
{
	return mDeplacement;
}

void Balle::dispCord()
{
	std::cout << "Cord: (" << mCord.x << ", " << mCord.y << ")" << std::endl;
}

void Balle::dispDep()
{
	std::cout << "Dep: (" << mDeplacement.x << ", " << mDeplacement.y << ")" << std::endl;
}

float Balle::getRadius()
{
	return radius;
}
