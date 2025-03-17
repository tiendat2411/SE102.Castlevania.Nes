#include "Scene.h"
#include "Game.h"
#include "Textures.h"
#include "Simon.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

CScene::CScene(float w, float h, float speed, int idTexture, CSimon* simon)
{
    CTextures* cTextures = CTextures::GetInstance();

    this->width = w;
    this->height = h;
    this->speedX = speed;
    this->x = 0;
    this->y = 0;
    //this->texture = cTextures->Get(idTexture);
    this->simon = simon;
}


void CScene::LoadResource()
{
    CGame* game = CGame::GetInstance();
    //    texture = game->LoadTexture(filePath);
}

void CScene::Update()
{

    // Di chuyển background khi nhân vật di chuyển
    //x = -simon->GetX() * speedX;

    if (x < -896) x = -896;
    if (x > 0) x = 0;  // Không cho background chạy quá giới hạn bên trái
}

void CScene::Render()
{
     CGame* game = CGame::GetInstance();
     /*
    float scaleY = SCREEN_HEIGHT / height;
    float scaleX = scaleY;
   
    float offsetX = simon->GetX() / (1536.0f - 640.0f);
    offsetX = max(0.0f, min(offsetX, 1.0f - (640.0f / 1536.0f)));

    sprite.pTexture = texture->getShaderResourceView();
    sprite.TexCoord.x = offsetX;
    sprite.TexCoord.y = 0;
    sprite.TexSize.x = 640.0f / 1536.0f;
    sprite.TexSize.y = 1.0f;
    sprite.TextureIndex = 0;
    sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    D3DXMATRIX matTranslation, matScaling;
    D3DXMatrixTranslation(&matTranslation, x, 0, 0.1f);
    D3DXMatrixScaling(&matScaling, scaleX, scaleY, 1.0f);
    sprite.matWorld = matTranslation * matScaling;


    game->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0); */
    /*RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = width;  // Sử dụng kích thước ảnh PNG gốc
    rect.bottom = height;
    
    game->Draw(x, y, texture, NULL); */

	 int spriteWidth = 0;
	 int spriteHeight = 0;

	 D3DX10_SPRITE sprite;

	 // Set the sprite’s shader resource view
	 sprite.pTexture = texture->getShaderResourceView();

	 
		 sprite.TexCoord.x = 0 / (float)texture->getWidth();
		 sprite.TexCoord.y = 0 / (float)texture->getHeight();

		 spriteWidth = (width - 0 + 1);
		 spriteHeight = (height - 0 + 1);

		 sprite.TexSize.x = 1.0f;//640.0f / 1536.0f;
		 sprite.TexSize.y = 1.0f;
	 

	 // Set the texture index. Single textures will use 0
	 sprite.TextureIndex = 0;

	 // The color to apply to this sprite, full color applies white.
	 sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	 //
	 // Build the rendering matrix based on sprite location 
	 //

	 // The translation matrix to be created
	 D3DXMATRIX matTranslation;

	 // Create the translation matrix
	 D3DXMatrixTranslation(&matTranslation, x, (101), 0.1f);

	 // Scale the sprite to its correct width and height because by default, DirectX draws it with width = height = 1.0f 
	 D3DXMATRIX matScaling;
	 D3DXMatrixScaling(&matScaling, (FLOAT)960, (FLOAT)202, 1.0f);

	 // Setting the sprite’s position and size
	 sprite.matWorld = (matScaling * matTranslation);

     game->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
     
}
