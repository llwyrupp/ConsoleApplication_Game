#pragma once
#include "EngineCommon/Engine_Includes.h"

BEGIN(System)
#define MAX_NUM_BUFFER 2
class ScreenBuffer;
class ENGINE_DLL Renderer
{
	typedef struct tagFrame {
		tagFrame(int iBufCnt);
		~tagFrame();

		void Clear(const Vector2& vScreenSize);

		//글자값, 글자색상을 멤버로 갖는 구조체
		CHAR_INFO* charInfoArr = nullptr;

		int* pSortingOrderArr = nullptr;
	}FRAME;

	typedef struct tagRenderCommand {
		/*tagRenderCommand(const char* _pText, const Vector2& _vPos, Color _eColor, int _iSortingOrder);
		~tagRenderCommand();*/

		//화면에 보여줄 문자값
		const char* pText = nullptr;

		//coordinates
		Vector2 vPosition;

		//color
		Color eColor = Color::eWhite;

		//render priority
		int iSortingOrder = 0;

	}RENDERCOM;

public:
	Renderer(const Vector2& vScreenSize);
	~Renderer();

	void Render();

	//렌더 batch에 한꺼번에 받아서 출력하기 위해 데이터를 적재한다.
	void Submit(const char* pText, const Vector2& vPos, Color eColor = Color::eWhite, int iSortOrder = 0);

public:
	static Renderer& Get_Instance();
private:
	//clear screen.
	void Clear();

	//use double buffering to swap the current(active) buffer
	void Present();


	//현재 사용할 버퍼 반환함수(getter)
	ScreenBuffer* GetCurBuffer();

private:
	//screen size.
	Vector2 m_vScreenSize;

	FRAME* m_pFrame = nullptr;

	//double buffer arr.
	ScreenBuffer* m_pScreenBuffers[MAX_NUM_BUFFER] = {};

	//the index of currently active buffer.
	int m_iCurBufIdx = 0;

	//render queue(internally implemented with std::vector.
	//put all rendering commands in this vector)
	vector<RENDERCOM> m_vecRenderQueue;

private:
	static Renderer* m_pInstance;
};

END