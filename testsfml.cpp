/*#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <stdio.h>


int main()
{
	int hit_again = 0, hit = 0;
	float detaltime = 0.0f;       // ตั้งค่าความเร็วให้ตัวละครเดิน 
	float totaltime = 0;		  // ตั้งค่าความเร็วให้ตัวละครเดิน 	
	float speed_player = 100.0f;  // ตั้งค่าความเร็วให้ตัวละครเดิน
	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(1080, 720), "Game");  //ขนาดหน้าจอ "ชื่อหัวเกม"

	// เป็นของวงกลม
	sf::CircleShape shape(70, 5);  // (ขนาด,มุมที่ให้เกิด เช่นอันนี้เป็น 5 มุม)
	shape.setPosition({ 450,400 });  // ตำแหน่งวงกลม (x,y)
	shape.setFillColor(sf::Color::White);  //สีของรูป


	// ของตัวละครหลัก
	sf::RectangleShape player(sf::Vector2f(70.0f, 70.0f)); //ขนาดของตัวละคร
	player.setPosition(100.0f, 100.0f); //ตน. ของตัวละครตอนเริ่ม
	sf::Texture playerTexture;
	playerTexture.loadFromFile("sprite/playermain.png"); // ดึงรูปมาจากในไฟล์
	player.setTexture(&playerTexture); // แอดรูปเข้าไปใน 4 เหลี่ยม
	//256   / 4
	int playerSizeX = playerTexture.getSize().x / 4; // ตัดส่วนของตัวละคร แกน x
	int playerSizeY = playerTexture.getSize().y / 4; // ตัดส่วนของตัวละคร แกน y
	player.setTextureRect(sf::IntRect(0, 0, playerSizeX, playerSizeY));
	int animationFrame = 0; // แฟรมของตัวละคร ที่ 0 



	while (window.isOpen())
	{
		detaltime = clock.restart().asSeconds(); // คำสั่งหน่วงให้น้องเดินช้า

		if (hit_again < 2) {
			window.draw(player); // ให้ตัวละครเคลื่อนที่ได้
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.move(speed_player * detaltime, 0.f * speed_player);
			player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 2, playerSizeX, playerSizeY));  //ปรับให้ตัวละครเดินตามทิศทาง
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.move(-speed_player * detaltime, 0.f * speed_player);
			player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 1, playerSizeX, playerSizeY));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.move(0.f * speed_player, -speed_player * detaltime);
			player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 3, playerSizeX, playerSizeY));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player.move(0.f * speed_player, speed_player * detaltime);
			player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 0, playerSizeX, playerSizeY));
		}


		window.draw(shape); // ให้วงกลมเคลื่อนที่
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))

		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			shape.setPosition((float)mousePos.x, (float)mousePos.y);
		}


		if (!(shape.getGlobalBounds().intersects(player.getGlobalBounds())))
		{
			
			printf("hit %d\n", hit);
			hit = 0;
		}

		if (shape.getGlobalBounds().intersects(player.getGlobalBounds()))
		{

			player.setFillColor(sf::Color::Red);	

			if (hit == 0)
			{
				hit++;
				hit_again += hit;
				printf("hit_again %d\n", hit_again);
			}
		}


		if (shape.getGlobalBounds().intersects(player.getGlobalBounds()) && hit_again == 2) {
			player.setFillColor(sf::Color::Transparent);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) { return 0; }  // กด x เพื่อออกจากโปรแกรม

		totaltime += detaltime;
		if (totaltime >= 0.1) {
			totaltime -= 0.1;
			animationFrame++;   // ให้น้องตัวละครไม่เดินเร็วเกิน เป็นการเซ้ทค่าความหน่วงให้น้อง
		}

		if (animationFrame > 3) {   // ทำเอนิเมชั่นให้มันเคลื่อนไหว ตลอด
			animationFrame = 0;
		}

		window.display();
		window.clear();
	}


	//player.setFillColor(sf::Color::White);
	return 0;
} */