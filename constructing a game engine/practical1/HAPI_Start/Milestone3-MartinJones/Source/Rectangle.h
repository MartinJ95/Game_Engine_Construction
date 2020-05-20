#pragma once

#include <iostream>
#include <algorithm>

class Rectangle
{
public:
	int left, right, top, bottom;

	Rectangle(const int &l, const int &r, const int &t, const int &b) : left(l), right(r), top(t), bottom(b) {};

	int Width() const { return right - left;}
	int Height() const { return bottom - top;}

	void clipTo(Rectangle &rect)
	{
		left = std::max(this->left, rect.left);
		top = std::max(this->top, rect.top);
		right = std::min(this->right, rect.right);
		bottom = std::min(this->bottom, rect.bottom);
	}

	bool isOnScreen(Rectangle &rect)
	{
		if (this->right < rect.left || this->bottom < rect.top || this->left > rect.right || this->top > rect.bottom)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};