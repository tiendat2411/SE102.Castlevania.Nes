//#include "Scene.h"
//#include "Game.h"
//#include "Textures.h"
//#include "Simon.h"
//#include "GameDefines.h"
//
////#define SCREEN_WIDTH 648
////#define SCREEN_HEIGHT 506
//#define TITLE_BAR_HEIGHT 38
//
//CScene::CScene(float w, float h, float speed, Type idTexture, CSimon* simon)
//{
//    CTextures* cTextures = CTextures::GetInstance();
//
//    this->width = w;
//    this->height = h;
//    this->speedX = speed;
//    this->x = 0;
//    this->y = 0;
//    this->texture = cTextures->Get(idTexture);
//    this->simon = simon;
//}
//
//
//void CScene::LoadResource()
//{
//    CGame* game = CGame::GetInstance();
//    //    texture = game->LoadTexture(filePath);
//}
//
//void CScene::Update()
//{
//
//    // Di chuyển background khi nhân vật di chuyển
//    x = -simon->GetPosX() * speedX;
//
//    if (x < -896) x = -896;
//    if (x > 0) x = 0;  // Không cho background chạy quá giới hạn bên trái
//}
//
//void CScene::Render()
//{
//     CGame* game = CGame::GetInstance();
//
//	 int spriteWidth = 0;
//	 int spriteHeight = 0;
//
//     float scaleY = SCREEN_HEIGHT / height;
//     float scaleX = scaleY;
//
//	 D3DX10_SPRITE sprite;
//
//	 // Set the sprite’s shader resource view
//	 sprite.pTexture = texture->getShaderResourceView();
//	 
//	 sprite.TexCoord.x = 0;
//     sprite.TexCoord.y = 0;
//
//	 spriteWidth = (width - 0 + 1);
//     spriteHeight = (height - 0 + 1);
//
//     sprite.TexSize.x = 1.0f;//640.0f / 1536.0f;
//	 sprite.TexSize.y = 1.0f;
//	 
//
//	 // Set the texture index. Single textures will use 0
//	 sprite.TextureIndex = 0;
//
//	 // The color to apply to this sprite, full color applies white.
//	 sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	 //
//	 // Build the rendering matrix based on sprite location 
//	 //
//
//	 // The translation matrix to be created
//	 D3DXMATRIX matTranslation;
//
//	 // Create the translation matrix
//	 D3DXMatrixTranslation(&matTranslation, x, (SCREEN_HEIGHT - TITLE_BAR_HEIGHT)/2, 0.1f);
//
//	 // Scale the sprite to its correct width and height because by default, DirectX draws it with width = height = 1.0f 
//	 D3DXMATRIX matScaling;
//	 D3DXMatrixScaling(&matScaling, (FLOAT)(width * scaleX), (FLOAT)(SCREEN_HEIGHT - TITLE_BAR_HEIGHT), 1.0f);
//
//	 // Setting the sprite’s position and size
//	 sprite.matWorld = (matScaling * matTranslation);
//
//     game->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
//     
//}
