/*
================================================================================
					 �I�u�W�F�N�g�w�������Q�[���v���O���~���O
	     Copyright (c) 2011 Human Academy Sendai. All rights reserved.
================================================================================

 �y�Ώۂn�r�z
     Microsoft Windows 7�ȍ~

 �y�R���p�C���z
     Microsoft VisualC++ 2013

 �y�v���O�����z
	 DInput8.cpp
				DirectInput8�N���X

 �y�o�[�W�����z
	 * Version    2015.10.00      2015/08/28  03:10:03

================================================================================
*/

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "DInput8.hpp"
#include "../Common/ComLibrary.hpp"
#include <wbemidl.h>
#include <oleauto.h>
#include <errors.h>
#include <tchar.h>
#include <string>

//------------------------------------------------------------------------------
//	�X�^�e�B�b�N�����N���C�u����
//------------------------------------------------------------------------------
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Quartz.lib")
#pragma comment(lib, "wbemuuid.lib")
//------------------------------------------------------------------------------
//	�f�t�H���g�R���X�g���N�^
//------------------------------------------------------------------------------
CDInput8::CDInput8() : m_pDInput(NULL), m_pKeyboard(NULL), m_pMouse(NULL)
{
	CComLibrary::Initialize();		// COM���C�u����������
}

//------------------------------------------------------------------------------
//	�f�X�g���N�^
//------------------------------------------------------------------------------
CDInput8::~CDInput8()
{
	Release();
	CComLibrary::Uninitialize();	// COM���C�u�������
}

//------------------------------------------------------------------------------
//	������
//------------------------------------------------------------------------------
bool CDInput8::Initialize(const HWND hWnd)
{
	Release();

	// DirectInput8�I�u�W�F�N�g�̐����ƃC���^�t�F�[�X�̎擾
	if(::CoCreateInstance(CLSID_DirectInput8, NULL, CLSCTX_INPROC_SERVER,
						  IID_IDirectInput8, (LPVOID*)&m_pDInput)
	   != S_OK) {
		::OutputDebugString(TEXT("*** Error - DirectInput8�I�u�W�F�N�g�������s(CDInput8_Initialize)\n"));
		return false;
	}

	// DirectInput8�I�u�W�F�N�g������
	if(m_pDInput->Initialize((HINSTANCE)::GetWindowLong(hWnd, GWL_HINSTANCE),
							 DIRECTINPUT_VERSION)
	   != DI_OK) {
		::OutputDebugString(TEXT("*** Error - DirectInput8�I�u�W�F�N�g���������s(CDInput8_Initialize)\n"));
		Release();
		return false;
	}

	m_pKeyboard = new CNullInputDevice(256);					// �L�[�{�[�h��NULL�I�u�W�F�N�g��ݒ�
	m_pMouse    = new CNullInputDevice(sizeof(DIMOUSESTATE2));	// �}�E�X��NULL�I�u�W�F�N�g��ݒ�

	m_hWnd      = hWnd;

	return true;
}

//------------------------------------------------------------------------------
//	���
//------------------------------------------------------------------------------
void CDInput8::Release()
{
	m_hWnd = NULL;

	ReleaseGamePad();

	delete m_pMouse;	m_pMouse    = NULL;		// �}�E�X���
	delete m_pKeyboard;	m_pKeyboard = NULL;		// �L�[�{�[�h���

	// DirectInput8�I�u�W�F�N�g���
	if(m_pDInput != NULL) {
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

//------------------------------------------------------------------------------
//	�f�o�C�X���
//------------------------------------------------------------------------------
void CDInput8::ReleaseDevice(IInputDevice* pDevice)
{
	// pDevice��NULL�܂���NULL�I�u�W�F�N�g�̏ꍇ�͉�����Ȃ�
	if(pDevice == NULL || pDevice->IsNull())
		return;

	// �f�o�C�X��������ANULL�I�u�W�F�N�g��ݒ�
	delete pDevice;
	pDevice = new CNullInputDevice();
}

//------------------------------------------------------------------------------
//	�L�[�{�[�h�f�o�C�X����
//------------------------------------------------------------------------------
bool CDInput8::CreateKeyboard()
{
	if(m_pDInput == NULL) {
		::OutputDebugString(TEXT("*** Error - DirectInput��������(CDInput8_CreateKeyboard)\n"));
		return false;
	}

	// �L�[�{�[�h�I�u�W�F�N�g�������ς݂̏ꍇ�́A���̂܂ܕԂ�
	if(m_pKeyboard->IsNull() == false)
		return true;

	// �f�o�C�X����
	IDirectInputDevice8*   pDIDevice = NULL;
	if(m_pDInput->CreateDevice(GUID_SysKeyboard, &pDIDevice, NULL) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �f�o�C�X�������s(CDInput8_CreateKeyboard)\n"));
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�ݒ�
	if(pDIDevice->SetDataFormat(&c_dfDIKeyboard) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �f�[�^�t�H�[�}�b�g�ݒ莸�s(CDInput8_CreateKeyboard)\n"));
		pDIDevice->Release();
		return false;
	}

	// �������x���ݒ�
	if(pDIDevice->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �������x���ݒ莸�s(CDInput8_CreateKeyboard)\n"));
		pDIDevice->Release();
		return false;
	}

	// �o�b�t�@�T�C�Y�ݒ�
	DIPROPDWORD   dipd;
	::ZeroMemory(&dipd, sizeof(dipd));
	dipd.diph.dwSize       = sizeof(dipd);
	dipd.diph.dwHeaderSize = sizeof(dipd.diph);
	dipd.diph.dwObj        = 0;
	dipd.diph.dwHow        = DIPH_DEVICE;
	dipd.dwData            = DIDEV_BUFSIZE;
	if(pDIDevice->SetProperty(DIPROP_BUFFERSIZE, &dipd.diph) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �o�b�t�@�T�C�Y�ݒ莸�s(CDInput8_CreateKeyboard)\n"));
		pDIDevice->Release();
		return false;
	}

	// �A�N�Z�X���擾
	pDIDevice->Acquire();

	// �L�[�{�[�h�I�u�W�F�N�g����
	delete m_pKeyboard;
	m_pKeyboard = new CKeyboard(pDIDevice);
	pDIDevice->Release();

	return true;
}

//------------------------------------------------------------------------------
//	�}�E�X�f�o�C�X����
//------------------------------------------------------------------------------
bool CDInput8::CreateMouse()
{
	if(m_pDInput == NULL) {
		::OutputDebugString(TEXT("*** Error - DirectInput��������(CDInput8_CreateMouse)\n"));
		return false;
	}

	// �}�E�X�I�u�W�F�N�g�������ς݂̏ꍇ�́A���̂܂ܕԂ�
	if(m_pMouse->IsNull() == false)
		return true;

	// �f�o�C�X����
	IDirectInputDevice8*   pDIDevice = NULL;
	if(m_pDInput->CreateDevice(GUID_SysMouse, &pDIDevice, NULL) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �f�o�C�X�������s(CDInput8_CreateMouse)\n"));
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�ݒ�
	if(pDIDevice->SetDataFormat(&c_dfDIMouse2) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �f�[�^�t�H�[�}�b�g�ݒ莸�s(CDInput8_CreateMouse)\n"));
		pDIDevice->Release();
		return false;
	}

	// �������x���ݒ�
	if(pDIDevice->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �������x���ݒ莸�s(CDInput8_CreateMouse)\n"));
		pDIDevice->Release();
		return false;
	}

	// �o�b�t�@�T�C�Y�ݒ�
	DIPROPDWORD   dipd;
	::ZeroMemory(&dipd, sizeof(dipd));
	dipd.diph.dwSize       = sizeof(dipd);
	dipd.diph.dwHeaderSize = sizeof(dipd.diph);
	dipd.diph.dwObj        = 0;
	dipd.diph.dwHow        = DIPH_DEVICE;
	dipd.dwData            = DIDEV_BUFSIZE;
	if(pDIDevice->SetProperty(DIPROP_BUFFERSIZE, &dipd.diph) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �o�b�t�@�T�C�Y�ݒ莸�s(CDInput8_CreateMouse)\n"));
		pDIDevice->Release();
		return false;
	}

	// �A�N�Z�X���擾
	pDIDevice->Acquire();

	// �}�E�X�I�u�W�F�N�g����
	delete m_pMouse;
	m_pMouse = new CMouse(pDIDevice);
	pDIDevice->Release();

	return true;
}

//------------------------------------------------------------------------------
//	�Q�[���p�b�h�f�o�C�X���
//------------------------------------------------------------------------------
void CDInput8::ReleaseGamePad()
{
	for(unsigned int i = 0; i < m_GamePad.size(); i++)
		delete m_GamePad[i];
	m_GamePad.clear();
}

//------------------------------------------------------------------------------
//	�Q�[���p�b�h�f�o�C�X����
//------------------------------------------------------------------------------
DWORD CDInput8::CreateGamePad(const DWORD inCount)
{
	if(m_pDInput == NULL) {
		::OutputDebugString(TEXT("*** Error - DirectInput��������(CDInput8_CreateGamePad)\n"));
		return 0;
	}

	ReleaseGamePad();

	if(inCount == 0)
		return 0;

	m_GamePad.resize(inCount, NULL);

	// �Q�[���p�b�h�f�o�C�X����
	m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
						   (LPDIENUMDEVICESCALLBACK)EnumGamePadProc, this, DIEDFL_ATTACHEDONLY);

	// �����ł����Q�[���p�b�h�𐔂���
	unsigned int   i, Create = 0;
	for(i = 0; i < m_GamePad.size(); i++) {
		if(m_GamePad[i] == NULL)
			break;
		Create++;
	}

	// ����Ȃ�������NullGamePad��ݒ�
	for(i = Create; i < inCount; i++)
		m_GamePad[i] = new CNullGamePad(sizeof(DIJOYSTATE));

	return Create;
}

//------------------------------------------------------------------------------
//	�Q�[���p�b�h�񋓃R�[���o�b�N
//------------------------------------------------------------------------------
BOOL CALLBACK CDInput8::EnumGamePadProc(LPDIDEVICEINSTANCE pDevInst, LPVOID pRef)
{
	return ((CDInput8*)pRef)->InitGamePad(pDevInst, pRef);
}

//------------------------------------------------------------------------------
//	�Q�[���p�b�h������
//------------------------------------------------------------------------------
BOOL CDInput8::InitGamePad(const LPDIDEVICEINSTANCE pDevInst, LPVOID pRef)
{
#ifdef _DEBUG
	if(m_pDInput == NULL) {
		::OutputDebugString(TEXT("*** Error - DirectInput��������(CDInput8_InitGamePad)\n"));
		return DIENUM_STOP;
	}
#endif

	if (IsXInputDevice(&pDevInst->guidInstance)) {
		for (unsigned int i = 0; i < m_GamePad.size(); i++) {
			if (m_GamePad[i] == NULL) {
				m_GamePad[i] = new CNullGamePad();
				break;
			}
		}
		return DIENUM_CONTINUE;
	}


	// �Q�[���p�b�h�I�u�W�F�N�g�쐬
	IDirectInputDevice8*   pDIDevice;
	if(m_pDInput->CreateDevice(pDevInst->guidInstance, &pDIDevice, NULL) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �Q�[���p�b�h�I�u�W�F�N�g�쐬���s(CDInput8_InitGamePad)\n"));
		return DIENUM_CONTINUE;
	}

	// �f�[�^�t�H�[�}�b�g�ݒ�
	if(pDIDevice->SetDataFormat(&c_dfDIJoystick) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �f�[�^�t�H�[�}�b�g�ݒ莸�s(CDInput8_InitGamePad)\n"));
		pDIDevice->Release();
		return DIENUM_CONTINUE;
	}

	// �������x���ݒ�
	if(pDIDevice->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE) != DI_OK) {
		::OutputDebugString(TEXT("*** Error - �������x���ݒ莸�s(CDInput8_InitGamePad)\n"));
		pDIDevice->Release();
		return DIENUM_CONTINUE;
	}

	// �o�b�t�@�T�C�Y�ݒ�
	DIPROPDWORD   dipd;
	::ZeroMemory(&dipd, sizeof(dipd));
	dipd.diph.dwSize       = sizeof(dipd);
	dipd.diph.dwHeaderSize = sizeof(dipd.diph);
	dipd.diph.dwObj        = 0;
	dipd.diph.dwHow        = DIPH_DEVICE;
	dipd.dwData            = DIDEV_BUFSIZE;
	if(FAILED(pDIDevice->SetProperty(DIPROP_BUFFERSIZE, &dipd.diph))) {
		::OutputDebugString(TEXT("*** Error - �o�b�t�@�T�C�Y�ݒ莸�s(CDInput8_InitGamePad)\n"));
		pDIDevice->Release();
		return DIENUM_CONTINUE;
	}

	// ���͈͐ݒ�
	DIENUMAXESARGS   Args = {this, pDIDevice};
	if(FAILED(pDIDevice->EnumObjects((LPDIENUMDEVICEOBJECTSCALLBACK)CDInput8::EnumGamePadAxesProc,
									 &Args, DIDFT_AXIS))) {
		pDIDevice->Release();
		return DIENUM_CONTINUE;
	}

	// �A�N�Z�X���擾
	pDIDevice->Acquire();

	// �Q�[���p�b�h�z��֒ǉ�
	for(unsigned int i = 0; i < m_GamePad.size(); i++) {
		if(m_GamePad[i] == NULL) {
			m_GamePad[i] = new CGamePad(pDIDevice);
			break;
		}
	}
	pDIDevice->Release();

	// �񋓏I������
	if(m_GamePad[m_GamePad.size() - 1] != NULL)
		return DIENUM_STOP;

	return DIENUM_CONTINUE;
}

//------------------------------------------------------------------------------
//	�Q�[���p�b�h���񋓃R�[���o�b�N
//------------------------------------------------------------------------------
BOOL CALLBACK CDInput8::EnumGamePadAxesProc(LPDIDEVICEOBJECTINSTANCE pDevObjInst, LPVOID pRef)
{
	return ((DIENUMAXESARGS*)pRef)->pDInput->SetAxesProp(pDevObjInst, pRef);
}

//------------------------------------------------------------------------------
//	���v���p�e�B�ݒ�
//------------------------------------------------------------------------------
BOOL CDInput8::SetAxesProp(const LPDIDEVICEOBJECTINSTANCE pDevObjInst, LPVOID pRef)
{
	IDirectInputDevice8*   pDIDevice = ((DIENUMAXESARGS*)pRef)->pDIDevice;

#ifdef _DEBUG
	if(pDIDevice == NULL) {
		::OutputDebugString(TEXT("*** Error - �Q�[���p�b�h��������(CDInput8_SetAxesProp)\n"));
		return DIENUM_STOP;
	}
#endif

	// ���͈͐ݒ�(��Ύ��̂�)
	if((pDevObjInst->dwType & DIDFT_ABSAXIS) != 0) {
		DIPROPRANGE   dipr;
		dipr.diph.dwSize       = sizeof(dipr);
		dipr.diph.dwHeaderSize = sizeof(dipr.diph);
		dipr.diph.dwHow        = DIPH_BYID;
		dipr.diph.dwObj        = pDevObjInst->dwType;
		dipr.lMin              = DIDEV_AXIS_MIN;
		dipr.lMax              = DIDEV_AXIS_MAX;
		if(FAILED(pDIDevice->SetProperty(DIPROP_RANGE, &dipr.diph)))
			::OutputDebugString(TEXT("*** Error - ���͈͐ݒ莸�s(CDInput8_SetAxesProp)\n"));
	}

	// �f�b�h�]�[���ݒ�
	DIPROPDWORD   dipdw;
	dipdw.diph.dwSize       = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwHow        = DIPH_BYID;
	dipdw.diph.dwObj        = pDevObjInst->dwType;
	dipdw.dwData            = DIDEV_AXIS_DEADZONE;
	if(FAILED(pDIDevice->SetProperty(DIPROP_DEADZONE, &dipdw.diph)))
		::OutputDebugString(TEXT("*** Error - �f�b�h�]�[���ݒ莸�s(CDInput8_SetAxesProp)\n"));

	return DIENUM_CONTINUE;
}

BOOL CDInput8::IsXInputDevice(GUID* pGuidProductFromDirectInput)
{
	IWbemLocator* pIWbemLocator				= NULL;
	IEnumWbemClassObject* pEnumDevices		= NULL;
	IWbemClassObject* pDevices[20]			= { 0 };
	IWbemServices* pIWbemServices			= NULL;
	BSTR                    bstrNamespace	= NULL;
	BSTR                    bstrDeviceID	= NULL;
	BSTR                    bstrClassName	= NULL;
	DWORD                   uReturned		= 0;
	bool                    bIsXinputDevice = false;
	UINT                    iDevice = 0;
	VARIANT                 var;
	HRESULT                 hr;
	
	auto l_cleanup = [&]() {
		VariantClear(&var);
		if (bstrNamespace)
			SysFreeString(bstrNamespace);
		if (bstrDeviceID)
			SysFreeString(bstrDeviceID);
		if (bstrClassName)
			SysFreeString(bstrClassName);
		for (iDevice = 0; iDevice < 20; iDevice++)
			SAFE_RELEASE(pDevices[iDevice]);
		SAFE_RELEASE(pEnumDevices);
		SAFE_RELEASE(pIWbemLocator);
		SAFE_RELEASE(pIWbemServices);
	};

	// So we can call VariantClear() later, even if we never had a successful IWbemClassObject::Get().
	VariantInit(&var);

	// Create WMI
	hr = CoCreateInstance(CLSID_WbemLocator,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator,
		(LPVOID*)&pIWbemLocator);

	if (FAILED(hr) || pIWbemLocator == NULL)
		l_cleanup();

	HrToStrByAMGet(hr);
	static int a;
	a++;
	std::wstring b = std::to_wstring(a);
	OutputDebugString(b.c_str());

	bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2"); if (bstrNamespace == NULL) l_cleanup();
	bstrClassName = SysAllocString(L"Win32_PnPEntity");   if (bstrClassName == NULL) l_cleanup();
	bstrDeviceID  = SysAllocString(L"DeviceID");          if (bstrDeviceID == NULL)  l_cleanup();

	HrToStrByAMGet(hr);
	a++;
	b = std::to_wstring(a);
	OutputDebugString(b.c_str());

	// Connect to WMI ����������������
	//hr = pIWbemLocator->ConnectServer(bstrNamespace, NULL, NULL, 0L,
	//	0L, NULL, NULL, &pIWbemServices);

	hr = pIWbemLocator->ConnectServer(BSTR(L"root\\CIMV2"), NULL, NULL, 0L,
		0L, NULL, NULL, &pIWbemServices);
	HrToStrByAMGet(hr);
	a++;
	b = std::to_wstring(a);
	OutputDebugString(b.c_str());

	if (FAILED(hr) || pIWbemServices == NULL)
		l_cleanup();

	// Switch security level to IMPERSONATE. 
	hr =CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	HrToStrByAMGet(hr);
	a++;
	b = std::to_wstring(a);
	OutputDebugString(b.c_str());

	hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, NULL, &pEnumDevices);

	if (FAILED(hr) || pEnumDevices == NULL)
	{
		HrToStrByAMGet(hr);
		a++;
		std::wstring b = std::to_wstring(a);
		OutputDebugString(b.c_str());
		l_cleanup();
	}

	// Loop over all devices
	for (;; )
	{
		// Get 20 at a time
		hr = pEnumDevices->Next(10000, 20, pDevices, &uReturned);
		if (FAILED(hr))
			l_cleanup();
		if (uReturned == 0)
			break;

		for (iDevice = 0; iDevice < uReturned; iDevice++)
		{
			// For each device, get its device ID
			hr = pDevices[iDevice]->Get(bstrDeviceID, 0L, &var, NULL, NULL);
			if (SUCCEEDED(hr) && var.vt == VT_BSTR && var.bstrVal != NULL)
			{
				// Check if the device ID contains "IG_".  If it does, then it's an XInput device
					// This information can not be found from DirectInput 
				if (wcsstr(var.bstrVal, L"IG_"))
				{
					// If it does, then get the VID/PID from var.bstrVal
					DWORD dwPid = 0, dwVid = 0;
					WCHAR* strVid = wcsstr(var.bstrVal, L"VID_");
					if (strVid && swscanf(strVid, L"VID_%4X", &dwVid) != 1)
						dwVid = 0;
					WCHAR* strPid = wcsstr(var.bstrVal, L"PID_");
					if (strPid && swscanf(strPid, L"PID_%4X", &dwPid) != 1)
						dwPid = 0;

					// Compare the VID/PID to the DInput device
					DWORD dwVidPid = MAKELONG(dwVid, dwPid);
					if (dwVidPid == pGuidProductFromDirectInput->Data1)
					{
						bIsXinputDevice = true;
						l_cleanup();
					}
				}
			}
			VariantClear(&var);
			SAFE_RELEASE(pDevices[iDevice]);
		}
	}

//LCleanup:
//	VariantClear(&var);
//	if (bstrNamespace)
//		SysFreeString(bstrNamespace);
//	if (bstrDeviceID)
//		SysFreeString(bstrDeviceID);
//	if (bstrClassName)
//		SysFreeString(bstrClassName);
//	for (iDevice = 0; iDevice < 20; iDevice++)
//		SAFE_RELEASE(pDevices[iDevice]);
//	SAFE_RELEASE(pEnumDevices);
//	SAFE_RELEASE(pIWbemLocator);
//	SAFE_RELEASE(pIWbemServices);

	return bIsXinputDevice;
}

BOOL CDInput8::EnumJoysticksCallback(DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	if (IsXInputDevice(&pdidInstance->guidProduct))
		return DIENUM_CONTINUE;

	// Device is verified not XInput, so add it to the list of DInput devices

	return DIENUM_CONTINUE;
}

//------------------------------------------------------------------------------
//	�f�o�C�X�A�N�Z�X���擾
//------------------------------------------------------------------------------
void CDInput8::Acquire()
{
	if(m_pDInput == NULL) {
		::OutputDebugString(TEXT("*** Error - DirectInput��������(CDInput8_Acquire)\n"));
		return;
	}

	m_pKeyboard->Acquire();
	m_pMouse   ->Acquire();

	for(unsigned int i = 0; i < m_GamePad.size(); i++)
		m_GamePad[i]->Acquire();
}

//------------------------------------------------------------------------------
//	�f�o�C�X�A�N�Z�X�����
//------------------------------------------------------------------------------
void CDInput8::Unacquire()
{
	if(m_pDInput == NULL) {
//		::OutputDebugString(TEXT("*** Error - DirectInput��������(CDInput8_Unacquire)\n"));
		return;
	}

	m_pKeyboard->Unacquire();
	m_pMouse   ->Unacquire();

	for(unsigned int i = 0; i < m_GamePad.size(); i++)
		m_GamePad[i]->Unacquire();
}

void CDInput8::HrToStrByAMGet(HRESULT hr) {
	TCHAR szErr[MAX_ERROR_TEXT_LEN];
	TCHAR szMsg[MAX_ERROR_TEXT_LEN + MAX_PATH + 256];
	// MAX_ERROR_TEXT_LEN �� errors.h �Œ�`�ς�
	AMGetErrorText(hr, szErr, MAX_ERROR_TEXT_LEN);
	_snwprintf_s(szMsg, _countof(szMsg), _TRUNCATE,
		_T("HRESULT=%08X (%s) %s")
		, hr
		, (FAILED(hr)) ? TEXT("FAILED") : TEXT("SUCCEEDED")
		, szErr);
	OutputDebugString(szMsg);
}
