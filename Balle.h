#ifndef BALLE_H_INCLUDED
#define BALLE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Balle
{
public:
	Balle();
	Balle(sf::Vector2f cord);
	sf::CircleShape getShape();

	void setPos(sf::Vector2f pos);
	void Init();
	void move(sf::Time deltaTime);
	void setDep(sf::Vector2f dep);
	void reduction(sf::Time deltaTime, float reductionV);
	void divise();
	sf::Vector2f getCord();
	sf::Vector2f getDep();
	void dispCord();
	void dispDep();
	float getRadius();

private:
	sf::CircleShape mShape;
	float radius;


	sf::Vector2f mDeplacement;
	sf::Vector2f mCord;
};

#endif // BALLE_H_INCLUDED
