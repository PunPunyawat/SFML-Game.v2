#include "Player.h"
#include <conio.h>
#include <Windows.h>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;  
	row = 5; // เริ่มมาให้หันหลัง ตามคอลั่มรูป

	// ของตัวละครหลัก
     playerBody.setSize(sf::Vector2f(90.0f, 90.0f)); //ขนาดของตัวละคร
	 playerBody.setPosition(282.0f,741.0f); //ตน. ของตัวละครตอนเริ่ม
	 playerBody.setTexture(texture);  // รับรูปมาจาก main
	 playerBody.setOrigin(playerBody.getSize() / 2.0f);  

}


void Player::Draw(sf::RenderWindow& window)
{
	window.draw(playerBody);  // วาดตัวละครของเรา
}

sf::Vector2f Player::getPosition()
{
	return this->playerBody.getPosition();
}


void Player::Update(float deltaTime)
{

	sf::Vector2f movement(0.0f, 0.0f);  // ไว้ขยับ ซ้าย ขวา

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (playerBody.getPosition().x < 470)
		{
			row = 4; //row = 3;
			movement.x += speed * deltaTime;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (playerBody.getPosition().x > 100) // ใช้ฟิคขอบของหน้าจอ ที่ใช้ 30 คือ ตนตัวละคร - ขนาดที่ขยายตัวละคร 
		{
			row = 4; //row = 2;     // เอาแถวของรูปมาใข้ 
			movement.x -= speed * deltaTime;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (playerBody.getPosition().y > 30)
		{
			row = 4;
			movement.y -= speed * deltaTime;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (playerBody.getPosition().y < 756)
		{
			row = 1;
			movement.y += speed * deltaTime;      // เป็นการให้ตัวละครเราเดินช้าๆ หน่วงๆ
		}
	}




	animation.Update(row, deltaTime);  // การรันเฟรมของรูปภาพให้ตัวละครขยับ
	playerBody.setTextureRect(animation.uvRect);  // ตัดรูปแค่ละเฟรมมาใช้   ถ้าไม่ตัดคือเป็นรูปทั้งไฟล์เลย
	playerBody.move(movement);   // ทำให้ตัวละครเคลื่อนที่



}
