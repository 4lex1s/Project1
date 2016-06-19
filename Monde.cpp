#include "Monde.h"
#include "Maths.h"
#include "afficherVec.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <iostream>
#include <Windows.h>

const int nombreBalles(600);

Monde::Monde() : mWindow(sf::VideoMode(960,720), "Simulation"), TimePerFrame(sf::seconds(1.f/60.f)),
mSpace(0), mDebut(1), mReductionV(0.1)
{
	initBalles();
	mView.reset(sf::FloatRect(0, 0, 640, 480));


	bords[0].setSize(sf::Vector2f(600, 440));
	bords[1].setSize(sf::Vector2f(590, 430));
	bords[0].setFillColor(sf::Color::Black);
	bords[1].setFillColor(sf::Color::White);
	bords[0].setPosition(sf::Vector2f(20, 15));
	bords[1].setPosition(sf::Vector2f(25, 20));
}

Monde::Monde(float reductionV) : mWindow(sf::VideoMode(960, 720), "Simulation"), TimePerFrame(sf::seconds(1.f / 60.f)),
mSpace(0), mDebut(1), mReductionV(reductionV)
{
	initBalles();
	mView.reset(sf::FloatRect(0, 0, 640, 480));


	bords[0].setSize(sf::Vector2f(600, 440));
	bords[1].setSize(sf::Vector2f(590, 430));
	bords[0].setFillColor(sf::Color::Black);
	bords[1].setFillColor(sf::Color::White);
	bords[0].setPosition(sf::Vector2f(20, 15));
	bords[1].setPosition(sf::Vector2f(25, 20));
}



void Monde::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (mWindow.isOpen())
	{
		processEvent();
		
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame && mWindow.isOpen())
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvent();
			update(TimePerFrame);
		}
		render();
	}
}


void Monde::processEvent()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			mSpace = 1;
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			mSpace = 0;
	}
}

void Monde::update(sf::Time deltaTime)
{
	
	if (mSpace && mDebut)
	{
		mDebut = 0;
		balles[0].Init();
	}
	for (int i = 0 ; i < nombreBalles ; i++)
	{
		testCollision(i, deltaTime);
		balles[i].move(deltaTime);
	}
	for (int i = 0; i < nombreBalles; i++)
	{
		balles[i].reduction(deltaTime, mReductionV);
	}
}


void Monde::render()
{
	mWindow.clear(sf::Color::White);
	mWindow.setView(mView);
	AfficherBords();
	for (int i = 0; i < nombreBalles; i++)
	{
		mWindow.draw(balles[i].getShape());
	}
	mWindow.display();
}

void Monde::AfficherBords()
{
	mWindow.draw(bords[0]);
	mWindow.draw(bords[1]);
}

void Monde::testCollision(int numBalle, sf::Time deltaTime)
{
	int numero(0);
	sf::Vector2f cord;
	sf::Vector2f deplacement;
	float radius;
	sf::Vector2f difference;
	bool collision(0);
	int touche(0);


	cord = balles[numBalle].getCord();
	radius = balles[numBalle].getRadius();
	for (float temps = 0 ; temps < deltaTime.asSeconds() && collision == 0 ; temps += 0.02f)
	{
		minMove(cord, deplacement, radius);

		for (int numero = 0; numero < nombreBalles && collision == 0; numero++)
		{
			if (numero != numBalle)
			{

				if (Distance(cord, balles[numero].getCord()) < radius)
				{
					//std::cout << (Distance(cord, balles[numero].getCord())) << "  " << numero << std::endl;
					difference = balles[numero].getCord() - cord;
					//std::cout << "(" << difference.x << ", " << difference.y << ") " << numero << "    " << numBalle << std::endl;
					touche = numero;
					collision = 1;
					
				}
			}
		}

	}


	if (collision && balles[numBalle].getDep().x != 0 && balles[numBalle].getDep().y != 0)
	{
		
		//std::cout << touche << std::endl;
		sf::Vector2f directionPrem;
		directionPrem = balles[numBalle].getDep();
		sf::Vector2f directionSec;
		directionSec = difference;
		

		float va = valeurAbsolue(directionPrem.x) + valeurAbsolue(directionPrem.y);
		//std::cout << "va: " << va << std::endl;
		directionPrem.x = directionPrem.x * (1 / va);
		directionPrem.y = directionPrem.y * (1 / va);
		//std::cout << "directionPrem: ";

		float vitesse = va;

		va = valeurAbsolue(directionSec.x) + valeurAbsolue(directionSec.y);
		//std::cout << "va: " << va << std::endl;
		directionSec.x = directionSec.x * (1 / va);
		directionSec.y = directionSec.y * (1 / va);
		//std::cout << "directionSec: ";


		sf::Vector2f nvDirection;
		nvDirection = ((directionPrem + directionSec) / 2.f);
		

		balles[touche].setDep(nvDirection*vitesse);

		sf::Vector2f directionTr;
		directionTr = directionPrem - (directionTr - directionPrem);

		balles[numBalle].setDep(directionTr);

		balles[numBalle].divise();
	}
}

void Monde::minMove(sf::Vector2f & cord, sf::Vector2f & deplacement, float radius)
{
	cord += deplacement * 0.02f;

	if (cord.y < 20 + radius)
	{
		cord.y = 20 + radius;
		deplacement.y = deplacement.y * -1;
	}

	if (cord.y > 450 - radius)
	{
		cord.y = 450 - radius;
		deplacement.y = deplacement.y * -1;
	}

	if (cord.x < 25 + radius)
	{
		cord.x = 25 + radius;
		deplacement.x = deplacement.x * -1;
	}

	if (cord.x > 615 - radius)
	{
		cord.x = 615 - radius;
		deplacement.x = deplacement.x * -1;
	}
}

void Monde::initBalles()
{
	srand(time(NULL));
	for (int i = 0; i < nombreBalles; i++)
	{
		balles[i].setPos(sf::Vector2f(rand() % 560 + 20, rand() % 400 + 20));
	}

}

