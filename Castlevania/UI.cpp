#include "UI.h"

UI::UI() :
    font(nullptr),
    simon(nullptr),
    simonHP(0),
    bossHP(0),
    uiHP(0),
    score(0),
    time(0),
    item(0),
    energy(0),
    life(0),
    stage(0),
    subWeapon(0)
{
    // Initialize all sprite pointers to nullptr
    heart = weapon = black = axe = holyWater = cross = knife = stopWatch = upgrade1 = upgrade2 = nullptr;
    simonHPList = enemyHPList = noHPList = nullptr;
}

UI::~UI()
{
    // Release font
    if (font) font->Release();

    // Delete sprite lists
    if (simonHPList) {
        for (auto sprite : *simonHPList) delete sprite;
        delete simonHPList;
    }
    if (enemyHPList) {
        for (auto sprite : *enemyHPList) delete sprite;
        delete enemyHPList;
    }
    if (noHPList) {
        for (auto sprite : *noHPList) delete sprite;
        delete noHPList;
    }

    // Delete individual sprites
    if (heart) delete heart;
    if (weapon) delete weapon;
    if (black) delete black;
    if (axe) delete axe;
    if (holyWater) delete holyWater;
    if (cross) delete cross;
    if (knife) delete knife;
    if (stopWatch) delete stopWatch;
    if (upgrade1) delete upgrade1;
    if (upgrade2) delete upgrade2;
}

bool UI::Initialize(ID3D10Device* gDevice, SimonDemo* simon, int bossHP)
{
    this->bossHP = bossHP;
    this->simon = simon;

    
    // Initialize black background
    LPSPRITE black = new CSprite(200, 0, 0, 30, 30, CTextures::GetInstance()->Get(Type::BLACK_UI));
    black->SetPosition(0, 0);
    D3DXMatrixScaling(&black->matScaling, 640.0f, 116.0f, 1.0f);

    // Initialize HP sprites
    simonHPList = new std::vector<LPSPRITE>();
    for (int i = 0; i < 16; i++)
    {
        LPSPRITE sprite = new CSprite(501 + i, 0, 0, 5, 10, CTextures::GetInstance()->Get(Type::SIMON_HP_UI));
        sprite->SetPosition(120 + 12 * (i + 1), 43);
        D3DXMatrixScaling(&sprite->matScaling, 8.0f, 15.0f, 1.0f);
        simonHPList->push_back(sprite);
    }

    enemyHPList = new std::vector<LPSPRITE>();
    for (int i = 0; i < 16; i++)
    {
        LPSPRITE sprite = new CSprite(517 + i, 0 , 0, 5, 10, CTextures::GetInstance()->Get(Type::ENEMY_HP_UI));
        sprite->SetPosition(120 + 12 * (i + 1), 67);
        D3DXMatrixScaling(&sprite->matScaling, 8.0f, 15.0f, 1.0f);
        enemyHPList->push_back(sprite);
    }

    noHPList = new std::vector<LPSPRITE>();
    for (int i = 0; i < 16; i++)
    {
        LPSPRITE sprite = new CSprite(533 + i, 0, 0, 5, 10, CTextures::GetInstance()->Get(Type::NO_HP_UI));
        sprite->SetPosition(120 + 12 * (i + 1), 43);
        D3DXMatrixScaling(&sprite->matScaling, 8.0f, 15.0f, 1.0f);
        noHPList->push_back(sprite);
    }

    // Initialize other UI elements
    heart = new CSprite(549, 0, 0, 16, 16, CTextures::GetInstance()->Get(Type::HEART_UI));
    D3DXMatrixScaling(&heart->matScaling, 16.0f, 16.0f, 1.0f);
    heart->SetPosition(420, 43);

    axe = new CSprite(550, 0, 0, 30, 28, CTextures::GetInstance()->Get(Type::AXE_ICON_UI));
    axe->SetPosition( 350, 43);

    holyWater = new CSprite(551, 0, 0, 32, 32, CTextures::GetInstance()->Get(Type::HOLY_WATER_ICON_UI));
    holyWater->SetPosition(350, 55);

    cross = new CSprite(552, 0, 0, 30, 28, CTextures::GetInstance()->Get(Type::CROSS_UI));
    cross->SetPosition(350, 55);

    knife = new CSprite(553, 0, 0, 30, 28, CTextures::GetInstance()->Get(Type::KNIFE_UI));
    knife->SetPosition(350, 55);

    stopWatch = new CSprite(554, 0, 0, 30, 28, CTextures::GetInstance()->Get(Type::STOP_WATCH_UI));
    stopWatch->SetPosition(350, 55);

    upgrade1 = new CSprite(555, 0, 0, 30, 28, CTextures::GetInstance()->Get(Type::DOUBLE_SHOT_UI));
    upgrade1->SetPosition(350, 55);

    upgrade2 = new CSprite(556, 0, 0, 30, 28, CTextures::GetInstance()->Get(Type::TRIPLE_SHOT_UI));
    upgrade2->SetPosition(350, 55);

    // Initialize font (DirectX 10 version)
    AddFontResourceEx(GAME_FONT, FR_PRIVATE, NULL);

    D3DX10_FONT_DESC fontDesc;
    fontDesc.Height = 20;
    fontDesc.Width = 0;
    fontDesc.Weight = FW_NORMAL;
    fontDesc.MipLevels = 1;
    fontDesc.Italic = false;
    fontDesc.CharSet = DEFAULT_CHARSET;
    fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fontDesc.Quality = ANTIALIASED_QUALITY;
    fontDesc.PitchAndFamily = FF_DONTCARE;
    wcscpy_s(fontDesc.FaceName, L"Press Start");

    HRESULT result = D3DX10CreateFontIndirect(gDevice, &fontDesc, &font);
    if (FAILED(result))
        return false;

    SetRect(&rect, 0, 20, GAME_WIDTH, GAME_HEIGHT);
    information = "SCORE_000000 TIME 0000 STAGE 00\n";
    information += "PLAYER                =62\n";
    information += "ENEMY                P=3\n";

    return true;
}

void UI::Update(int bossHP, int time, int life, int stage)
{

#pragma region Calculate boss HP in UI

    if (bossHP <= 0)
        this->uiHP = 0;
    else {
        int x = bossHP / (this->bossHP / 16);
        int y = bossHP % (this->bossHP / 16);

        if (y == 0)
            this->uiHP = x;
        else
            this->uiHP = x + 1;
    }

#pragma endregion

    this->time = time;
    this->stage = stage;


    std::string scoreString = std::to_string(simon->GetScore());
    while (scoreString.length() < 6)
        scoreString = "0" + scoreString;


    std::string timeString = std::to_string(this->time);
    while (timeString.length() < 4)
        timeString = "0" + timeString;


    std::string stageString = std::to_string(this->stage);
    while (stageString.length() < 2)
        stageString = "0" + stageString;


    information = "SCORE_" + scoreString + " TIME " + timeString + " STAGE " + stageString + "\n";
    information += "PLAYER                =" + std::to_string(simon->GetEnergy()) + "\n";
    information += "ENEMY                P=" + std::to_string(simon->GetLife()) + "\n";


    switch (simon->currentWeapon)
    {
    case ITEM_AXE:
        weapon = nullptr;
        weapon = axe;
        break;
    case ITEM_HOLY_WATER:
        weapon = nullptr;
        weapon = holyWater;
        break;
    case ITEM_CROSS:
        weapon = nullptr;
        weapon = cross;
        break;
    case ITEM_KNIFE:
        weapon = nullptr;
        weapon = knife;
        break;
    case ITEM_STOP_WATCH:
        weapon = nullptr;
        weapon = stopWatch;
        break;
    default:
        break;
    }
}

void UI::Render()
{
    RECT newRect;

    black->Draw();

    // Draw text (DirectX 10 version)
    if (font)
    {
        font->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
    }


    for (std::vector<LPSPRITE>::iterator i = noHPList->begin(); i != noHPList->end(); i++)
    {
        SetRect(&newRect, 0, 0, 8, 15);
        (*i)->Draw();
        D3DXVECTOR2 newPosition = (*i)->GetPosition();
        (*i)->SetPosition(newPosition.x, 67);
        (*i)->Draw();
    }


    int count = 0;
    for (std::vector<LPSPRITE>::iterator i = simonHPList->begin(); i != simonHPList->end(); i++)
    {
        if (count < simon->GetHP())
        {
            (*i)->Draw();
        }
        count++;
    }


    count = 0;
    for (std::vector<LPSPRITE>::iterator i = enemyHPList->begin(); i != enemyHPList->end(); i++)
    {
        if (count < uiHP)
        {
            (*i)->Draw();
        }
        count++;
    }


    //D3DXVECTOR2 newPosition = { 330, 45 };
    //SetRect(&newRect, 0, 0, 70, 45);
    //(*enemyHPList)[0]->Render(newPosition, newRect);

    heart->Draw();

    weapon->Draw();

    switch (simon->GetNoSubWeapon()) {
    case 2: upgrade1->Draw(); break;
    case 3: upgrade2->Draw(); break;
    }
}