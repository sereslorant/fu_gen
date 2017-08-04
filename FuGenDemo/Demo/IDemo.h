#ifndef IDEMO_H
#define IDEMO_H

class IDemo
{
public:
	
	virtual void SetNextDemo() = 0;
	virtual void SetPreviousDemo() = 0;

	virtual void ChangeState() = 0;
	virtual void Draw() = 0;
	
	IDemo() {}
	virtual ~IDemo() {}
};

#endif // IDEMO_H
