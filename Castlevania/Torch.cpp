#include "Torch.h"


void CTorch::Render()
{
	//DebugOut(L"health: %d", health);
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(TORCH_ANI_BEGIN)->Render(x, y);
}


void CTorch::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (dynamic_cast<CAxe*>(e->obj)) {
	//	delete this;
	//}
}


void CTorch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	Width = tex->getWidth() / tex->_col;
	Height = tex->getHeight() / tex->_row;
	l = x - Width / 2;
	t = y - Height / 2;
	r = l + Width;
	b = t + Height;
           
}
