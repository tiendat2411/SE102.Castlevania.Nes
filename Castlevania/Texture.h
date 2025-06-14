#pragma once

#include <d3d10.h>
#include <d3dx10.h>

//
// Warpper class to simplify texture manipulation. See also CGame::LoadTexture
//
class CTexture
{
protected:
	ID3D10Texture2D* _tex;
	ID3D10ShaderResourceView* _rsview;
	int _width,_height;
public:	
	int _row, _col;
	int _frame_width, _frame_height;
	int _totalSprites;
	CTexture()
	{
		_tex = NULL;
		_rsview = NULL;
		_width = -1;
		_height = -1;
		_row= -1, _col=-1;
		_totalSprites = -1;
	}

	CTexture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview, int col = 1, int row = 1,int totalSprites=1	)
	{
		this->_tex = tex;
		this->_rsview = rsview;

		D3D10_TEXTURE2D_DESC desc;
		this->_tex->GetDesc(&desc);

		this->_width = desc.Width;
		this->_height = desc.Height;
		this->_col = col;
		this->_row = row;
		this->_frame_width = desc.Width / col;
		this->_frame_height = desc.Height / row;
		this->_totalSprites = totalSprites;
	}

	ID3D10ShaderResourceView* getShaderResourceView() { return this->_rsview; }

	int getWidth() { return this->_width; }
	int getHeight() { return this->_height; }

	int getFrameWidth() { return this->_frame_width; }
	int getFrameHeight() { return this->_frame_height; }

	int getCol() { return this->_col; }
	int getRow() { return this->_row; }

	ID3D10Texture2D* getTexture() { return this->_tex; }

	~CTexture()
	{
		if (_rsview != NULL) this->_rsview->Release();
		if (_tex != NULL) this->_tex->Release();
	}
};

typedef CTexture* LPTEXTURE;
