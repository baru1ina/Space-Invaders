#pragma once

using namespace sf;

class Animation {
	unsigned short animation_iterator; // ����� �������� ���������� �������� �������� ��������, �� ������ ����� � �������� ��������
	unsigned short animation_speed; // ��� ������ �������� ��������, ��� �������� �������� (������ �������� ����������)
	unsigned short current_frame;
	unsigned short frame_width; // ������ ������ ������� ������
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