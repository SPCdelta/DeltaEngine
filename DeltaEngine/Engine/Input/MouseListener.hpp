#pragma once
struct MouseListener
{
	uint32_t which;
	int8_t button;
	int8_t clicks;
	int mouseY;
	int mouseX;

	// Constructor
	MouseListener(uint32_t w, int8_t b, int8_t c, int y, int x)
		: which(w), button(b), clicks(c), mouseY(y), mouseX(x)
	{
	}
};