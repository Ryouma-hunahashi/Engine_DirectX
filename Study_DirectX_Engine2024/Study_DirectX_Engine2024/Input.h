#pragma once
#define DIRECTXINPUT_VERSION 0x0800

#define DIK_LBUTTON (0) // マウスの右クリック
#define DIK_RBUTTON (1) // マウスの左クリック
#define DIK_MBUTTON (2) // マウスの中クリック（ホイール）

#pragma region Includes
#include <map>
#include <iostream>
#include <DirectXMath.h>
#include <dinput.h>
#include <Xinput.h>
#include <unordered_map>
#pragma endregion

#pragma region Librarys
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dxguid.lib")
#pragma endregion

namespace Applib
{
	// コントローラー接続のボタンタイプ
	enum class InputControllerType
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	A,
	B,
	Y,
	X,
	SELECT,
	START,
	RB1,
	RB2,
	RB3,
	LB1,
	LB2,
	LB3
};
	
	// キーボード接続のボタンタイプ
	enum class InputKeyboardType
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LSHIFT,
	RSHIFT,
	CNTL,
	SPACE,
	ENTER,
	BACKSPACE,
	ESCAPE,
	ALT,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
	NUM_0,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
};
	
	// マウス接続のボタンタイプ
	enum class InputMouseType
{
	LEFT,
	RIGHT,
	CENTER,
};
	
	// 現在の入力タイプ
	enum class HIDType
{
	CONTROLLER,
	KEYBOARDMOSUE,
};
	
	// スティック入力（コントローラー用）
	enum class PadTrigger
{
	LTrigger,
	RTrigger,
};
	
	// プレイヤー人数設定
	enum class PlayerNumber
{
	SINGLE,
	DOUBLE,
	TRIPLE,
	MAX,
};

	/// <summary>
	/// 入力のクラス
	/// </summary>
	class Input
	{
	private:
		// コントローラーテーブル
		std::unordered_map<InputControllerType, DWORD> tableController =
		{
			{InputControllerType::UP	    , XINPUT_GAMEPAD_DPAD_UP			},
			{InputControllerType::DOWN	    , XINPUT_GAMEPAD_DPAD_DOWN			},
			{InputControllerType::LEFT	    , XINPUT_GAMEPAD_DPAD_LEFT			},
			{InputControllerType::RIGHT	    , XINPUT_GAMEPAD_DPAD_RIGHT			},
			{InputControllerType::A		    , XINPUT_GAMEPAD_A					},
			{InputControllerType::B		    , XINPUT_GAMEPAD_B					},
			{InputControllerType::Y		    , XINPUT_GAMEPAD_Y					},
			{InputControllerType::X		    , XINPUT_GAMEPAD_X					},
			{InputControllerType::SELECT	, XINPUT_GAMEPAD_BACK				},
			{InputControllerType::RB1	    , XINPUT_GAMEPAD_RIGHT_SHOULDER		},
			{InputControllerType::RB2	    , 0								    },
			{InputControllerType::RB3	    , XINPUT_GAMEPAD_RIGHT_THUMB		},
			{InputControllerType::LB1	    , XINPUT_GAMEPAD_LEFT_SHOULDER		},
			{InputControllerType::LB2	    , 0								    },
			{InputControllerType::LB3 	    , XINPUT_GAMEPAD_LEFT_THUMB			},

		};
		// キーボードテーブル
		std::unordered_map<InputKeyboardType, DWORD> tableKeyboard =
		{
			{InputKeyboardType::A,			DIK_A			},
			{InputKeyboardType::B,			DIK_B			},
			{InputKeyboardType::C,			DIK_C			},
			{InputKeyboardType::D,			DIK_D			},
			{InputKeyboardType::E,			DIK_E			},
			{InputKeyboardType::F,			DIK_F			},
			{InputKeyboardType::G,			DIK_G			},
			{InputKeyboardType::H,			DIK_H			},
			{InputKeyboardType::I,			DIK_I			},
			{InputKeyboardType::J,			DIK_J			},
			{InputKeyboardType::K,			DIK_K			},
			{InputKeyboardType::L,			DIK_L			},
			{InputKeyboardType::M,			DIK_M			},
			{InputKeyboardType::N,			DIK_N			},
			{InputKeyboardType::O,			DIK_O			},
			{InputKeyboardType::P,			DIK_P			},
			{InputKeyboardType::Q,			DIK_Q			},
			{InputKeyboardType::R,			DIK_R			},
			{InputKeyboardType::S,			DIK_S			},
			{InputKeyboardType::T,			DIK_T			},
			{InputKeyboardType::U,			DIK_U			},
			{InputKeyboardType::V,			DIK_V			},
			{InputKeyboardType::W,			DIK_W			},
			{InputKeyboardType::X,			DIK_X			},
			{InputKeyboardType::Y,			DIK_Y			},
			{InputKeyboardType::Z,			DIK_Z			},
			{InputKeyboardType::UP,			DIK_UP			},
			{InputKeyboardType::DOWN,		DIK_DOWN		},
			{InputKeyboardType::LEFT,		DIK_LEFT		},
			{InputKeyboardType::RIGHT,		DIK_RIGHT		},
			{InputKeyboardType::LSHIFT,		DIK_LSHIFT		},
			{InputKeyboardType::RSHIFT,		DIK_RSHIFT		},
			{InputKeyboardType::CNTL,		DIK_LCONTROL	},
			{InputKeyboardType::SPACE,		DIK_SPACE		},
			{InputKeyboardType::ENTER,		DIK_RETURN		},
			{InputKeyboardType::BACKSPACE,	DIK_BACKSPACE	},
			{InputKeyboardType::ESCAPE,		DIK_ESCAPE		},
			{InputKeyboardType::ALT,		DIK_LALT		},
			{InputKeyboardType::NUM_1,		DIK_1			},
			{InputKeyboardType::NUM_2,		DIK_2			},
			{InputKeyboardType::NUM_3,		DIK_3			},
			{InputKeyboardType::NUM_4,		DIK_4			},
			{InputKeyboardType::NUM_5,		DIK_5			},
			{InputKeyboardType::NUM_6,		DIK_6			},
			{InputKeyboardType::NUM_7,		DIK_7			},
			{InputKeyboardType::NUM_8,		DIK_8			},
			{InputKeyboardType::NUM_9,		DIK_9			},
			{InputKeyboardType::NUM_0,		DIK_0			},
			{InputKeyboardType::F1,			DIK_F1			},
			{InputKeyboardType::F2,			DIK_F2			},
			{InputKeyboardType::F3,			DIK_F3			},
			{InputKeyboardType::F4,			DIK_F4			},
			{InputKeyboardType::F5,			DIK_F5			},
			{InputKeyboardType::F6,			DIK_F6			},
			{InputKeyboardType::F7,			DIK_F7			},
			{InputKeyboardType::F8,			DIK_F8			},
			{InputKeyboardType::F9,			DIK_F9			},
			{InputKeyboardType::F10,		DIK_F10			},
			{InputKeyboardType::F11,		DIK_F11			},
			{InputKeyboardType::F12,		DIK_F12			},
		};
		// マウステーブル
		std::unordered_map<InputMouseType, DWORD> tableMouse =
		{
			{InputMouseType::CENTER,DIK_MBUTTON},
			{InputMouseType::LEFT,	DIK_LBUTTON},
			{InputMouseType::RIGHT,	DIK_RBUTTON},
		};

	private:
		/* インプットデバイス */
		HRESULT result;
		// インプット
		IDirectInput8* input;
		// キーボード用の変数
		IDirectInputDevice8* lpkeyboard = nullptr;
		// マウス用の変数
		IDirectInputDevice8* lpMouse = nullptr;
		// 人数分のコントローラーを用意しておく
		XINPUT_STATE controller[static_cast<int>(PlayerNumber::MAX)];
		XINPUT_STATE oldController[static_cast<int>(PlayerNumber::MAX)];

	public:
		HIDType inputType; // インプットの種類を保存する
	private:
		// コントローラーの状態を格納する変数
		//XINPUT_STATE conState;
		// キーボードマウスの状態を格納する変数
		DIMOUSESTATE keymouseState;
		DIMOUSESTATE oldkeymouseState;
		DIJOYSTATE joyStick;

		unsigned char mKeyBuffer[256] = {};
		unsigned char mOldKeyBuffer[256] = {};

		bool checkcontroller = false;
		bool checkkeyboard = false;

	public:
		// 関数宣言
		Input() = default;
		~Input() = default;

		// 初期化を行う関数
		bool Initialize(HWND _hWnd, HINSTANCE _hInstance);
		// 毎ループ呼び出す関数
		void Update();
		// キーボードボタン入力（トリガー）
		bool isKeyTrigger(InputControllerType _inputtype) const noexcept;
		// キーボードボタン入力（トリガー）
		bool isKeyTrigger(InputKeyboardType _inputtype) const noexcept;
		// キーボードボタン入力（トリガー）
		bool isKeyTrigger(InputMouseType _inputtype) const noexcept;
		// キーボードボタン入力(プレス)
		bool isKeyPress(InputControllerType _inputtype) const noexcept;
		// キーボードボタン入力(プレス)
		bool isKeyPress(InputKeyboardType _inputtype) const noexcept;
		// キーボードボタン入力(プレス)
		bool isKeyPress(InputMouseType _inputtype) const noexcept;
		// コントローラートリガー取得
		DirectX::XMFLOAT2 GetVertical(PadTrigger _triggertype);
		DirectX::XMFLOAT2 GetHorizontal(PadTrigger _triggertype);
		// マウスの位置を取得する
		DirectX::XMFLOAT3 GetMousePos();
		// マウスの移動量を取得する
		POINT GetMouseVelocity();
		// インプットクラスのゲッター
		static Input* Get() { static Input instance; return &instance; }
		// 現在の入力タイプを取得する
		HIDType GetType() { return inputType; }

	};
}