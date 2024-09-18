#pragma once

class Vec2 {
public:
	Vec2();
	Vec2(const float& fx, const float& fy);
	~Vec2();

	bool operator == (const Vec2& vec);
	bool operator != (const Vec2& vec);

	Vec2 operator + (const Vec2& vec);
	Vec2 operator - (const Vec2& vec);
	Vec2 operator * (const float& value);
	Vec2 operator / (const float& value);

	void operator += (const Vec2& vec);
	void operator -= (const Vec2& vec);	
	void operator *= (const float& value); 
	void operator /= (const float& value);

	float x = 0;
	float y = 0;
};
