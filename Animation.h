#pragma once
#include <SFML/Graphics.hpp>


class Animation
{

public:
	Animation(sf::Texture*texture,sf::Vector2u imageCount,float switchTime);
	sf::IntRect uvRect;  // รับค่า 4 ค่า

	void Update(int row, float deltaTime);
	

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

