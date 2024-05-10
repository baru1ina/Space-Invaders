#pragma once

using namespace sf;

class Animation {
	unsigned short animation_iterator; // когда итератор достикгает значения скорости анимации, мы меняем фрейм и ресетаем итератор
	unsigned short animation_speed; // чем больше значение скорости, тем медленне анимация (больше проходок итератором)
	unsigned short current_frame;
	unsigned short frame_width; // ширина одного кусочка взрыва
	unsigned short total_frames;

	Sprite sprite;
	Texture texture;

public:
	Animation(unsigned short animation_speed_, unsigned short frame_width_, const std::string& texture_location_);

	bool change_current_frame();
	bool update();

	void draw(short x_, short y_, RenderWindow& window_, const Color& color_ = Color(255, 255, 255));
	void reset();
};