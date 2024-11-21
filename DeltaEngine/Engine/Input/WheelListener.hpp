#pragma once

//struct WheelListener
//{
//	int h; /**< The amount scrolled horizontally, positive to the right and negative to the left */
//	int v; /**< The amount scrolled vertically, positive away from the user and negative toward the user */
//	uint32_t direction; /**< Set to one of the SDL_MOUSEWHEEL_* defines. When FLIPPED the values in X and Y will be opposite. Multiply by -1 to change them back */
//	float preciseX; /**< The amount scrolled horizontally, positive to the right and negative to the left, with float precision */
//	float preciseY; /**< The amount scrolled vertically, positive away from the user and negative toward the user, with float precision */
//	int mouseX; /**< X coordinate, relative to window */
//	int mouseY; /**< Y coordinate, relative to window */
//
//	WheelListener(int hScroll, int vScroll, uint32_t dir, float pX, float pY,
//				  int mX, int mY)
//		: h(hScroll),
//		  v(vScroll),
//		  direction(dir),
//		  preciseX(pX),
//		  preciseY(pY),
//		  mouseX(mX),
//		  mouseY(mY)
//	{
//	}
//};