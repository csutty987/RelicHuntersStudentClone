#ifndef _RENDER_OBJECT_H
#define _RENDER_OBJECT_H

class RenderObject
{
public:
	
	RenderObject();
	virtual ~RenderObject();

	virtual void Render() = 0;

private:

};

#endif
