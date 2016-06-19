#ifndef MONDE_H_INCLUDED
#define MONDE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Balle.h"


class Monde
{
public:
    Monde();
	Monde(float reductionV);
    void run();

private:

	void processEvent();
    void update(sf::Time deltaTime);
    void render();


private:

	///////////////////
	//	Methodes

	void AfficherBords();
	void testCollision(int numBalle, sf::Time deltaTime);
	void minMove(sf::Vector2f& cord, sf::Vector2f& deplacement, float radius);
	void initBalles();

	////////////////////
	//	Attributs

	sf::RectangleShape bords[2];


    sf::RenderWindow mWindow;
	sf::View mView;
	sf::Time TimePerFrame;
	
	float mReductionV;

	bool mSpace;
	bool mDebut;

	Balle balles[600];
};


#endif // MONDE_H_INCLUDED
