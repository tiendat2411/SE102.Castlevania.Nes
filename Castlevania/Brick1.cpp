//#include "Brick1.h"
//
//
//
//
//CBrick1::CBrick1(float X, float Y, int W, int H, int Model)
//{
//	model = Model;
//	switch (Model)
//	{
//	case BRICK_ID_1:
//		texture = CTextures::GetInstance()->Get(Type::BRICK_MODEL_1); // loại màn 1
//		break;
//	case BRICK_ID_2:
//		texture = CTextures::GetInstance()->Get(Type::BRICK_MODEL_2); // loại màn 2
//		break;
//	case BRICK_ID_3:
//		texture = CTextures::GetInstance()->Get(Type::BRICK_MODEL_3); // loại nhỏ 16px
//		break;
//	case BRICK_ID_TRANSPARENT:
//		texture = CTextures::GetInstance()->Get(Type::BRICK_TRANSPARENT);// loại trong suốt 
//		break;
//	case BRICK_ID_3_3_32:
//		texture = CTextures::GetInstance()->Get(Type::BRICK_MODEL_3_3_32);// loại 3 ô nhỏ - 32px 
//		break;
//	case BRICK_ID_3_4_32:
//		texture = CTextures::GetInstance()->Get(Type::BRICK_MODEL_3_4_32);// loại đủ 4 ô nhỏ - 32px
//		break;
//	default:
//		DebugOut(L"[BRICK] Get Texture that bai! Ko nhan dang duoc Model!\n");
//		break;
//	}
//
//	type = Type::BRICK;
//	sprite = new CSprite(texture, 1000);
//	this->x = X;
//	this->y = Y;
//	this->width = W;
//	this->height = H;
//}
//
//void CBrick1::Render(CCamera* camera)
//{
//	//if (IS_DEBUG_RENDER_BBOX)
//	//	RenderBoundingBox(camera);
//
//	if (model == BRICK_ID_TRANSPARENT)
//		return;
//
//	D3DXVECTOR2 pos = camera->Transform(x, y);
//
//	for (int i = 0; i < (int)ceil(width / texture->getWidth()); i++)
//		for (int j = 0; j < (int)ceil(height / texture->getHeight()); j++)
//			sprite->Draw(pos.x + i * texture->getWidth(), pos.y + j * texture->getHeight());
//
//}
//
//void CBrick1::GetBoundingBox(float& l, float& t, float& r, float& b)
//{
//	l = x;
//	t = y;
//	r = x + (float)ceil(width / texture->GetFrameWidth()) * texture->GetFrameWidth();
//	b = y + (float)ceil(height / texture->GetFrameHeight()) * texture->GetFrameHeight();
//}
//
//int CBrick1::GetModel()
//{
//	return model;
//}
