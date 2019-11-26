#pragma once
class snake;
class estado
{
public:
	estado();
	virtual void up(snake*),down(snake*),left(snake*),right(snake*);
	~estado();
};

