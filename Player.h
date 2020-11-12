#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player
{
	public:
		
		Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime , float speed );
		//virtual ~Player();

		void Update(float daltaTime);
		void Draw(sf::RenderWindow& window);  //วาดหน้าจอ
		sf::Vector2f getPosition();
		sf::Vector2f GetPosition() { return playerBody.getPosition(); }  //การเซ็ตตำแหน่งของตัวละคร ของหน้า view

	private:  // ไว้ประกาศตัวแปร 

		sf::RectangleShape playerBody;  // การเซ้ทชื่อ playerBody เป็นของตัวละครเราที่เอาชื่อนี้ไปใช้เขียนใน cpp 
		Animation animation; 
		unsigned int row;  // แถวของตัวละครที่ใช้
		float speed;  // ความเร็วตัวละคร
		
};

