#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Windows.h>
#include "Player.h"
#include "Bullet.h"
#include "background.h"
#include <vector>
using namespace sf;

static const float VIEW_HEIGHT = 864.0f;
static const float VIEW_WIDHT = 564.0f;

int pst = 0, pst1[6];   // position กระสุนกับ   pst1 ไว้เก็บ []
int chk_1[6] = { 0 }; // เอาไว้เช็คว่าเลยขอบไหม 
int x=0, y=0;
int playerSizeX;
int playerSizeY;

float detalTime = 0.0f;       // ตั้งค่าความเร็วให้ตัวละครเดิน 
float totaltime = 0;		  // ตั้งค่าความเร็วให้ตัวละครเดิน 	
float speed_player = 150.0f;  // ตั้งค่าความเร็วให้ตัวละครเดิน
int   animationFrame = 0; // แฟรมของตัวละคร ที่ 0 

clock_t start = -0.2, end = 0;

///////////////////////////////// VIEW //////////////////////////////////////////
//ฟังชั่น ในการเซ้ทค่า display ให้คงที่ตลอดหลังจากปรับขยายหรือหดหน้า
void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	// aspectRatio คือการเซ้ทค่าของหน้าจอให้คงที่ตลอดหลังจากมีการขยายหน้าจอ เป็นต้น
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_WIDHT * aspectRatio);  // การให้มันคงที่ค่าในแกน x ภาพหน้าจะเหมือนเดิม
}

///////////////////////////////// SHOT //////////////////////////////////////////

sf::Texture BULLET;
sf::Texture playerTexture;
sf::Sprite player;


void Control();
void shot();

class Bulletz // การยิง
{

public:

	sf::Sprite bulletzz;

	void set(int x, int y)
	{
		bulletzz.setTexture(BULLET);
		bulletzz.setTextureRect(sf::IntRect(0, 0, 30, 30));
		bulletzz.setPosition(x, y);
		
	}
};
Bulletz bulletzz[6];

///////////////////////////////// SHOT3 //////////////////////////////////////////

class Bullett
{
public:
		
	sf::CircleShape shot;
	float maxSpeed;
	sf::Vector2f curveVelocity;
	sf::Vector2f position;
	Bullett(float radius = 5.0f)
		: curveVelocity(0.0f, 0.0f), maxSpeed(10.0f)
	{
		this->shot.setRadius(radius);
		this->shot.setFillColor(sf::Color::White);

	}

	
};




///////////////////////////////// MAIN //////////////////////////////////////////

int main()
{	
	int screen = 0; // หน้าจอตอนให้ตัวละครเดินขึ้นมา
	sf::Clock clock;

	///////////////////////////////// DISPLAY ///////////////////////////////////////
	
	sf::RenderWindow window(sf::VideoMode(564.0f, 864.0f), "Game_pp" );  //ขนาดหน้าจอ "ชื่อหัวเกม"
	//sf::RenderWindow window(sf::VideoMode(VIEW_WIDHT, VIEW_HEIGHT), "GamePUNPUN");  //ขนาดหน้าจอ "ชื่อหัวเกม"

	///////////////////////////////// VIEW //////////////////////////////////////////
	sf::View viewCharacter;
	viewCharacter.setSize(sf::Vector2f(564.0f, 864.0f));
	viewCharacter.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));   // ให้พอดีขนาดหน้าจอ
	//viewCharacter.zoom(1.2f);  // ขยายภาพพื้นหลัง
	//sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(564.0f, 864.0f));   // ทำให้การปรับหน้าจอภาพให้มีขนาดตงที่

	///////////////////////////////// SHOT //////////////////////////////////////////
	//sf::Texture BULLET;
	//bulletzz.loadFromFile("sprite/weapon.png");

	/////////////////////////////// BACKGROUND /////////////////////////////////////
	// ลองใส่พื้นหลัง
	//sf::RectangleShape background(sf::Vector2f(564.0f, 864.0f)); // ให้รูปใหญ่เท่าไหร่ ก็เลือกขนาดเอา
	sf::Texture backgroundTexture[2];
	backgroundTexture[0].loadFromFile("./sprite/background_gamed.png");
	//backgroundTexture[1].loadFromFile("./sprite/background_game2.jpg");
	std::vector<Background>backgrounds;
	backgrounds.push_back(Background(&backgroundTexture[0], 80.0f));
	//backgrounds.push_back(Background(&backgroundTexture[1], 80.0f));


	///////////////////////////////// ITEM //////////////////////////////////////////
	// Item
	sf::RectangleShape Heart(sf::Vector2f(72.0f, 73.0f));
	sf::Texture Heartlove;
	Heartlove.loadFromFile("sprite/heart_main.png");
	Heart.setTexture(&Heartlove);
	Heart.setPosition({ 270,340 });
	//Heart.setOrigin(Heart.getSize() / 2.0f);

	///////////////////////////////// HP //////////////////////////////////////////
	//Hp

	sf::RectangleShape HP(sf::Vector2f(230.0f, 70.0f));
	sf::Texture HPplayer;
	HPplayer.loadFromFile("sprite/HP_1_100p.png");
	HP.setTexture(&HPplayer);
	HP.setPosition({ 50,30 });
	
	///////////////////////////////// SHAPE //////////////////////////////////////////
	// เป็นของวงกลม
	sf::CircleShape shape(70,5);  // (ขนาด,มุมที่ให้เกิด เช่นอันนี้เป็น 5 มุม)
	shape.setPosition({ 450,400 });  // ตำแหน่งวงกลม (x,y)
	shape.setFillColor(sf::Color::White);  //สีของรูป

	
	///////////////////////////////// PLAYER //////////////////////////////////////////

	//ตัวละคร
	/*sf::Texture playerTexture;                            /////////////////////// class player ////////////////////////
	playerTexture.loadFromFile("sprite/playermainful.png"); // ดึงรูปมาจากในไฟล์
	int animationFrame = 0; // แฟรมของตัวละคร ที่ 0 

	// animation ใน class		//การแบ่งสโคปของรูปภาพ (4,4)	//ความเร็วในการรันเฟรม (0.5f)	// ความเร็วของตัวละคร (100.0f)
	Player player(&playerTexture, sf::Vector2u(4, 6), 0.2f , 120.0f);*/

	sf::RectangleShape player(sf::Vector2f(90.0f, 90.0f)); //ขนาดของตัวละคร
	player.setPosition(240.0f, 1000.0f); //ตน. ของตัวละครตอนเริ่ม
	sf::Texture playerTexture;													////////////////////////  main //////////////////////////////
	playerTexture.loadFromFile("sprite/playermainful.png"); // ดึงรูปมาจากในไฟล์
	player.setTexture(&playerTexture); // แอดรูปเข้าไปใน 4 เหลี่ยม
	//256   / 4
	int playerSizeX = playerTexture.getSize().x / 4; // ตัดส่วนของตัวละคร แกน x
	int playerSizeY = playerTexture.getSize().y / 6; // ตัดส่วนของตัวละคร แกน y
	player.setTextureRect(sf::IntRect(0, 0, playerSizeX, playerSizeY));
	//player.setOrigin(player.getSize() / 2.0f);
	//int animationFrame = 0; // แฟรมของตัวละคร ที่ 0 


	///////////////////////////////// SHOT 2 //////////////////////////////////////////
	/*sf::Texture weaponZl;
	weaponZl.loadFromFile("sprite/weapon.png");
	int effect = 0;
	double timeEffect = 0;
	Bullet bulletList(&playerTexture, &effect);
	sf::Event event;
	bulletList.evnt = &event;
	bool isSpacebarPrees = false;*/

	///////////////////////////////// SHOT 3 //////////////////////////////////////////

	Bullett b1;
	std::vector<Bullett> bullets;
	bullets.push_back(Bullett(b1));

	sf::Vector2f playerCenter;
	sf::Vector2f mousePosition;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormalize;
	//sf::Vector2f getPosition();
	sf::Texture weaponshot;
	weaponshot.loadFromFile("sprite/weapon.png");     // รูปยังไม่ขึ้น
	//shot.setTexture(&weaponshot);


	///////////////////////////////// SOUND //////////////////////////////////////////
	
	sf::Music start_sound; // เพลงเริ่มเกม
	if (!start_sound.openFromFile("sound/songstart.ogg"))
	{
		printf("ERROR\n");
	}
	start_sound.play(); //เปิดเพลง

	//******************************************************************************

	while (window.isOpen())
	{
		/////////////////////////////  DRAW //////////////////////////////////////////
		
		Control();
		shot();

		if (screen == 0) {
			if (player.getPosition().y >= 720) {   // ถ้าตำแหน่งน้อยกว่า 721 ให้ตัวละครเดินขึ้นมาเองจนไม่น้อยกว่า 721
				player.move(0.0f, - 0.15f);
			}
			else {
				screen = 1;
			}
		}

		if (screen == 1) {   // เดี๋ยวเอาการรับค่าปุ่มการเดินมาใส่ เพราะตอนเริ่มเกมจะได้กดปุ่มไม่ได้

			for (int i = 0; i < 6; i++)
			{
				if (chk_1[i] == 1)
				{
					window.draw(bulletzz[i].bulletzz);
				}
			}

		}
			for (Background& background : backgrounds) {   // ลูปให้รูปวน 
				background.Draw(window);
			}
		
			detalTime = clock.restart().asSeconds(); // คำสั่งหน่วงให้น้องเดินช้า
			window.draw(shape); // ให้วงกลมเคลื่อนที่
			window.draw(Heart);
			window.draw(HP);
			//player.Draw(window); // ให้ตัวละครเคลื่อนที่ได้	///////// class player ////////////////

			if (TRUE) {  // ให้หันหน้าอยู่เสมอ
				window.draw(player);
				player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 4, playerSizeX, playerSizeY));
			}


			//end = clock();
			//float dif = (float)(end - start) / CLOCKS_PER_SEC;  //หน่วงหน่วยเวลากระสุน

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (player.getPosition().x < 380) {

					player.move(speed_player * detalTime, 0.f * speed_player);
					player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 3, playerSizeX, playerSizeY));  //ปรับให้ตัวละครเดินตามทิศทาง
					pst = 1;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (player.getPosition().x > 100) {

					player.move(-speed_player * detalTime, 0.f * speed_player);
					player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 2, playerSizeX, playerSizeY));
					pst = 2;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (player.getPosition().y > 120) {

					player.move(0.f * speed_player, -speed_player * detalTime);
					player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 4, playerSizeX, playerSizeY));
					pst = 3;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (player.getPosition().y < 730) {

					player.move(0.f * speed_player, speed_player * detalTime);
					player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 1, playerSizeX, playerSizeY));
					pst = 4;
				}
			}



			x = player.getPosition().x;  // รับค่าตำแหน่งตัวละครไว้ เอาให้ตัวแปร x 
			y = player.getPosition().y;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) /*&& dif > 0.5*/)
			{
				for (int i = 0; i < 6; i++)
				{
					if (chk_1[i] == 0)
					{
						if (pst == 1) { bulletzz[i].set(x, y - 20); } //ให้กระสุนออกลดขึ้นด้านบนไปเรื่อยๆ
						if (pst == 2) { bulletzz[i].set(x, y - 20); }
						if (pst == 3) { bulletzz[i].set(x, y - 20); }
						if (pst == 4) { bulletzz[i].set(x, y - 20); }

						pst1[i] = pst;
						chk_1[i] = 1;
						//start = clock();
						break;
					}
				}
			}

			sf::Event evnt;
			while (window.pollEvent(evnt))	// while นี้ทำให้สามารถใช้เม้ากดเต็มจอหรือใช้ขยาย กว้างยาวได้
			{
				switch (evnt.type)
				{

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::Resized:
					ResizeView(window, viewCharacter);
					break;

				}
			}



			/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))    // Mouse

			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				shape.setPosition((float)mousePos.x, (float)mousePos.y);
			}*/

			//bulletList.positionPlayer = player.getPosition();
			//detalTime = clock.restart().asSeconds();
			//if(b1().intersects(Heart.getGlobalBounds()))



			if (player.getGlobalBounds().intersects(Heart.getGlobalBounds()))
			{
				Heart.setFillColor(sf::Color::Transparent);
			}


			/*if (event.type == sf::Event::EventType::TextEntered
				and event.text.unicode == ' '
				and isSpacebarPrees == false)
			{
				//std::cout << "set isSpacebarPrees: true" << std::endl;
				isSpacebarPrees = true;
				if (bulletList.canAttack()) {              // BY ploy
					//player.actionAttack();

				}
			}

			if (event.type == sf::Event::EventType::KeyReleased && isSpacebarPrees == true)
			{
				isSpacebarPrees = false;
				//std::cout << "set isSpacebarPrees: false" << std::endl;
			}*/

			///////////////////////////////// LOOP BG //////////////////////////////////////////	

			for (Background& background : backgrounds) {
				background.Update(detalTime);
			}

			/// ///////////////////////////////////////////////////////////////////////////////

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();  // กด esc เพื่อออกจากโปรแกรม
			}

			//player.Update(detalTime); // เป็นทุกอย่างของตัวละคร ทั้งการตัดภาพ การเดิน เอนิเมชั่น    // class player
			//viewCharacter.setCenter(player.GetPosition());  //กล้องตามตัวละครของเรา เซ้ทค่าให้อยุ่ตรงกลางหรือค่าที่เราเซ้ทไว้    /// class player

			totaltime += detalTime; // ให้น้องวิ่งเป็นเอนิเมชั่น
			if (totaltime >= 0.2) {  // ทำให้น้องสิ่งเร็วหรือช้า แบบเอนิเมชั่น
				totaltime -= 0.2;
				animationFrame++;   // ให้น้องตัวละครไม่เดินเร็วเกิน เป็นการเซ้ทค่าความหน่วงให้น้อง
			}

			if (animationFrame > 3) {   // ทำเอนิเมชั่นให้มันเคลื่อนไหว ตลอด
				animationFrame = 0;
			}


			///////////////////////////////////////////////////////////////////////
			//Update shot

			playerCenter = sf::Vector2f(player.getPosition().x+40, player.getPosition().y+10); // ตำแหน่งกระสุนออกจากตัว

			mousePosition = sf::Vector2f(Mouse::getPosition(window));
			//int distanct =player.getPosition().y;
			aimDirection = mousePosition - playerCenter;  // ทิศทางการยิง
			aimDirectionNormalize = aimDirection / sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2));
			
			if (//sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				sf::Mouse::isButtonPressed(sf::Mouse::Left))    // Mouse ยิง
			{
				b1.shot.setPosition(playerCenter);
				b1.curveVelocity = aimDirectionNormalize * b1.maxSpeed;
				bullets.push_back(Bullett(b1));
			}

			
			for (size_t i = 0; i < bullets.size(); i++)
			{
			
				bullets[i].shot.move(bullets[i].curveVelocity);
			}

			for (size_t i = 0; i < bullets.size(); i++)   // ลูปการวาดกระสุน 
			{

				window.draw(bullets[i].shot);
				
			}


			/// //////////////////////////////////////////////////////////////
			
			window.draw(player);
			window.display();
			window.clear(sf::Color(240, 185, 246));
			//window.setView(viewCharacter);
			//bulletList.Draw(window);

		}
	
	return 0;
}

void Control() {


}

void shot() {

	for (int i = 0; i < 6; i++) {
		if (chk_1[i] == 1) {

			float speed = 1;
			if (pst1[i] == 1)
			{
				bulletzz[i].bulletzz.move(0, -speed);
			}
			if (pst1[i] == 2)
			{
				bulletzz[i].bulletzz.move(0, -speed);
			}
			if (pst1[i] == 3)
			{
				bulletzz[i].bulletzz.move(0, speed);
			}
			if (pst1[i] == 4)
			{
				bulletzz[i].bulletzz.move(0, speed);
			}

			if (bulletzz[i].bulletzz.getPosition().y < 0 || bulletzz[i].bulletzz.getPosition().y>864)
			{
				chk_1[i] = 0;
			}
			if (bulletzz[i].bulletzz.getPosition().x < 0 || bulletzz[i].bulletzz.getPosition().x>0)
			{
				chk_1[i] = 0;
			}
		}
	}
}