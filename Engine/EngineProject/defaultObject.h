#pragma once

class defaultObject {
public:
	virtual void Delete();
};

class drawableObject: public defaultObject {
public:
	virtual void Draw();
};