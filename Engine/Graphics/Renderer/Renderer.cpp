#include "Renderer.h"
#include "Graphics/ScreenBuffer/ScreenBuffer.h"
#include<iostream>
BEGIN(System)

#pragma region FRAME
Renderer::tagFrame::tagFrame(int iBufCnt)
{
	//배열 생성 및 초기화(RAII)
	charInfoArr = new CHAR_INFO[iBufCnt];//메모리 동적할당
	memset(charInfoArr, 0, sizeof(CHAR_INFO) * iBufCnt);


	pSortingOrderArr = new int[iBufCnt];//메모리 동적할당
	memset(pSortingOrderArr, 0, sizeof(int) * iBufCnt);
}

Renderer::tagFrame::~tagFrame()
{
	Safe_Delete_Arr(charInfoArr);
	Safe_Delete_Arr(pSortingOrderArr);
}

void Renderer::tagFrame::Clear(const Vector2& vScreenSize)
{
	//2차원 배열로 다루는 1차원 배열을 돌면서 모두 blank(' ')로 세팅
	const int iWidth = vScreenSize.m_iX;
	const int iHeight = vScreenSize.m_iY;

	for (int iRow = 0; iRow < iHeight; ++iRow) {
		for (int iCol = 0; iCol < iWidth; ++iCol) {
			//get arr index;
			//index = (current row idx * width) + current column idx
			int iIndex = (iRow * iWidth) + iCol;

			//set string and attributes
			CHAR_INFO& info = charInfoArr[iIndex];
			info.Char.AsciiChar = ' ';
			info.Attributes = 0;

			//init sort order
			pSortingOrderArr[iIndex] = -1;
		}
	}
}
#pragma endregion FRAME

#pragma region RENDERER
Renderer::Renderer(const Vector2& vScreenSize)
	:m_vScreenSize(vScreenSize)
{
	const int iBufCnt = vScreenSize.m_iX * vScreenSize.m_iY;

	m_pFrame = new FRAME(iBufCnt);

	//init frame.
	m_pFrame->Clear(vScreenSize);

	//RAII
	m_pScreenBuffers[0] = new ScreenBuffer(vScreenSize);
	m_pScreenBuffers[0]->Clear_Buffer();

	m_pScreenBuffers[1] = new ScreenBuffer(vScreenSize);
	m_pScreenBuffers[1]->Clear_Buffer();

	//set active buffer
	Present();
}


Renderer::~Renderer()
{
	Safe_Delete(m_pFrame);
	for (auto& buf : m_pScreenBuffers) {
		Safe_Delete(buf);
	}
}

void Renderer::Render()
{
	//clear screen.
	Clear();

	//all actors on the scene has finished "Submit"ting to the Renderer.
	//Now, iterate the renderQueue and add up the FRAMEs.

	for (const RENDERCOM& com : m_vecRenderQueue) {
		//if no text, skip
		if (!com.pText)
			continue;

		//세로기준 화면 벗어났는지 확인
		if (com.vPosition.m_iY < 0 || com.vPosition.m_iY >= m_vScreenSize.m_iY)
			continue;

		const int iLen = static_cast<int>(strlen(com.pText));
		if (iLen <= 0)
			continue;

		//가로기준 화면 벗어났는지 확인.
		//위치는 문자열의 맨 왼쪽 글자를 기준으로 한다
		const int iStartX = com.vPosition.m_iX;
		//문자열의 맨 마지막 문자의 인덱스
		const int iEndX = com.vPosition.m_iX + iLen - 1;
		if (iEndX < 0 || iStartX >= m_vScreenSize.m_iX)
			continue;

		//보여질 문자들을 추려낸다
		const int iVisibleStart = iStartX < 0 ? 0 : iStartX;//문자열의 시작 인덱스가 화면에서 벗어난 경우 0,
		//아닐 경우 기존값 유지
		
		//문자열의 끝 인덱스가 화면을 벗어난 경우 화면 너비만큼 값-1
		//아닌 경우 기존 값 그대로 사용
		const int iVisibleEnd = iEndX >= m_vScreenSize.m_iX ? m_vScreenSize.m_iX - 1 : iEndX;
		

		//문자열 설정 (화면에 그려질 부분만)
		for (int i = iVisibleStart; i <= iVisibleEnd; ++i) {
			//문자열 안의 문자 인덱스
			const int iSrcIdx = i - iStartX;

			//프레임(2차원 문자배열) 인덱스
			const int iFrameIdx = (com.vPosition.m_iY * m_vScreenSize.m_iX) + com.vPosition.m_iX;

			//그리기 우선순위 비교하기
			if (m_pFrame->pSortingOrderArr[iFrameIdx] > com.iSortingOrder)
				continue;

			//데이터 기록하기
			m_pFrame->charInfoArr[iFrameIdx].Char.AsciiChar = com.pText[iSrcIdx];
			m_pFrame->charInfoArr[iFrameIdx].Attributes = (WORD)com.eColor;

			//우선순위 갱신
			m_pFrame->pSortingOrderArr[iFrameIdx] = com.iSortingOrder;
		}
	}

	//draw the letters.
	GetCurBuffer()->Draw_Char(m_pFrame->charInfoArr);

	//swap buffer.
	Present();

	//empty renderqueue
	m_vecRenderQueue.clear();
}

void Renderer::Submit(const char* pText, const Vector2& vPos, Color eColor, int iSortOrder)
{
	//create a render data and push it into renderqueue.
	RENDERCOM renderCom = {};
	renderCom.pText = pText;
	renderCom.vPosition = vPos;
	renderCom.eColor = eColor;
	renderCom.iSortingOrder = iSortOrder;

	m_vecRenderQueue.emplace_back(renderCom);
}

void Renderer::Clear()
{
	//clearing screen.
	//1. erase frame(2d arr data.)
	m_pFrame->Clear(m_vScreenSize);

	//2. erase console buffer.
	GetCurBuffer()->Clear_Buffer();
}

void Renderer::Present()
{
	//swap buffer
	SetConsoleActiveScreenBuffer(GetCurBuffer()->Get_Buffer());

	//swap index
	m_iCurBufIdx = 1 - m_iCurBufIdx;
}

ScreenBuffer* Renderer::GetCurBuffer()
{
	if (m_iCurBufIdx >= MAX_NUM_BUFFER || m_iCurBufIdx < 0) {
		std::cerr << "BUFFER OUTOFINDEX\n";
		__debugbreak();
		return nullptr;
	}

	return m_pScreenBuffers[m_iCurBufIdx];
}


#pragma endregion RENDERER


//#pragma region RENDERCOMMAND
//Renderer::tagRenderCommand::tagRenderCommand(const char* _pText, const Vector2& _vPos, Color _eColor, int _iSortingOrder)
//	:vPosition(_vPos), eColor(_eColor), iSortingOrder(_iSortingOrder)
//{
//	//deep copy.
//	size_t szLen = strlen(_pText) + 1;
//	pText = new char[szLen];
//	strcpy_s(pText, sizeof(char) * szLen, _pText);
//}
//
//Renderer::tagRenderCommand::~tagRenderCommand()
//{
//
//}
//#pragma endregion RENDERCOMMAND


END