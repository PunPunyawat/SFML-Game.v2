#include "Animation.h"
// เรียกเป็นชื่อ class ก่อนแล้วค่อยใช้ ฟังชั่น				//	(เซ้ตแถว,คอลั่ม)  iamgecount รับคู่อันดับ
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	{
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	totalTime = 0.0f;
	currentImage.x = 0;
							// รับค่าแกน x        // imagecount คือค่าที่เอามาตัดรูป เป็นเฟรม
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

	}

void Animation::Update(int row, float deltaTime)
	{

	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
		{

		totalTime -= switchTime;
		currentImage.x++;
		
		if (currentImage.x >= imageCount.x) 
			{

			currentImage.x = 0;
			
			}

		}

	uvRect.left = currentImage.x * uvRect.width;   // ให้รันภาพของแกน x ในเฟรมรูป ทำให้มีเอนิเมชั่น
	uvRect.top = currentImage.y * uvRect.height;   // ใผ้รันเดินได้ แต่ไม่มีเอนิเมชั่น

	}

