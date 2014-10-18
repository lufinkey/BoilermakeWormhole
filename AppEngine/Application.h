#pragma once
class Application
{
public:
	Application();
	virtual ~Application();

	virtual void Initialize();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(long appTime);
	virtual void Draw(Graphics2D&g, long appTime);
};

