#pragma once
#define DIRECTXINPUT_VERSION 0x0800

#define DIK_LBUTTON (0) // �}�E�X�̉E�N���b�N
#define DIK_RBUTTON (1) // �}�E�X�̍��N���b�N
#define DIK_MBUTTON (2) // �}�E�X�̒��N���b�N�i�z�C�[���j

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
	// �R���g���[���[�ڑ��̃{�^���^�C�v
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
	
	// �L�[�{�[�h�ڑ��̃{�^���^�C�v
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
	
	// �}�E�X�ڑ��̃{�^���^�C�v
	enum class InputMouseType
{
	LEFT,
	RIGHT,
	CENTER,
};
	
	// ���݂̓��̓^�C�v
	enum class HIDType
{
	CONTROLLER,
	KEYBOARDMOSUE,
};
	
	// �X�e�B�b�N���́i�R���g���[���[�p�j
	enum class PadTrigger
{
	LTrigger,
	RTrigger,
};
	
	// �v���C���[�l���ݒ�
	enum class PlayerNumber
{
	SINGLE,
	DOUBLE,
	TRIPLE,
	MAX,
};

	/// <summary>
	/// ���͂̃N���X
	/// </summary>
	class Input
	{
	private:
		// �R���g���[���[�e�[�u��
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
		// �L�[�{�[�h�e�[�u��
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
		// �}�E�X�e�[�u��
		std::unordered_map<InputMouseType, DWORD> tableMouse =
		{
			{InputMouseType::CENTER,DIK_MBUTTON},
			{InputMouseType::LEFT,	DIK_LBUTTON},
			{InputMouseType::RIGHT,	DIK_RBUTTON},
		};

	private:
		/* �C���v�b�g�f�o�C�X */
		HRESULT result;
		// �C���v�b�g
		IDirectInput8* input;
		// �L�[�{�[�h�p�̕ϐ�
		IDirectInputDevice8* lpkeyboard = nullptr;
		// �}�E�X�p�̕ϐ�
		IDirectInputDevice8* lpMouse = nullptr;
		// �l�����̃R���g���[���[��p�ӂ��Ă���
		XINPUT_STATE controller[static_cast<int>(PlayerNumber::MAX)];
		XINPUT_STATE oldController[static_cast<int>(PlayerNumber::MAX)];

	public:
		HIDType inputType; // �C���v�b�g�̎�ނ�ۑ�����
	private:
		// �R���g���[���[�̏�Ԃ��i�[����ϐ�
		//XINPUT_STATE conState;
		// �L�[�{�[�h�}�E�X�̏�Ԃ��i�[����ϐ�
		DIMOUSESTATE keymouseState;
		DIMOUSESTATE oldkeymouseState;
		DIJOYSTATE joyStick;

		unsigned char mKeyBuffer[256] = {};
		unsigned char mOldKeyBuffer[256] = {};

		bool checkcontroller = false;
		bool checkkeyboard = false;

	public:
		// �֐��錾
		Input() = default;
		~Input() = default;

		// ���������s���֐�
		bool Initialize(HWND _hWnd, HINSTANCE _hInstance);
		// �����[�v�Ăяo���֐�
		void Update();
		// �L�[�{�[�h�{�^�����́i�g���K�[�j
		bool isKeyTrigger(InputControllerType _inputtype) const noexcept;
		// �L�[�{�[�h�{�^�����́i�g���K�[�j
		bool isKeyTrigger(InputKeyboardType _inputtype) const noexcept;
		// �L�[�{�[�h�{�^�����́i�g���K�[�j
		bool isKeyTrigger(InputMouseType _inputtype) const noexcept;
		// �L�[�{�[�h�{�^������(�v���X)
		bool isKeyPress(InputControllerType _inputtype) const noexcept;
		// �L�[�{�[�h�{�^������(�v���X)
		bool isKeyPress(InputKeyboardType _inputtype) const noexcept;
		// �L�[�{�[�h�{�^������(�v���X)
		bool isKeyPress(InputMouseType _inputtype) const noexcept;
		// �R���g���[���[�g���K�[�擾
		DirectX::XMFLOAT2 GetVertical(PadTrigger _triggertype);
		DirectX::XMFLOAT2 GetHorizontal(PadTrigger _triggertype);
		// �}�E�X�̈ʒu���擾����
		DirectX::XMFLOAT3 GetMousePos();
		// �}�E�X�̈ړ��ʂ��擾����
		POINT GetMouseVelocity();
		// �C���v�b�g�N���X�̃Q�b�^�[
		static Input* Get() { static Input instance; return &instance; }
		// ���݂̓��̓^�C�v���擾����
		HIDType GetType() { return inputType; }

	};
}