#include "pch.h"
#include "CKHOpenAPI.h"
#include "resource.h"
#include "BrokerKW.h"
#include "BrokerKWDlg.h"



/////////////////////////////////////////////////////////////////////////////
// C_KH_OPEN_API

IMPLEMENT_DYNCREATE(C_KH_OPEN_API, CWnd)

// C_KH_OPEN_API 속성입니다.

// C_KH_OPEN_API 작업입니다.
BEGIN_EVENTSINK_MAP(C_KH_OPEN_API, CWnd)

	ON_EVENT(C_KH_OPEN_API, IDC_KHOPENAPICTRL, 1, C_KH_OPEN_API::OnReceiveTrData, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(C_KH_OPEN_API, IDC_KHOPENAPICTRL, 2, C_KH_OPEN_API::OnReceiveRealData, VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(C_KH_OPEN_API, IDC_KHOPENAPICTRL, 3, C_KH_OPEN_API::OnReceiveMsg, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(C_KH_OPEN_API, IDC_KHOPENAPICTRL, 4, C_KH_OPEN_API::OnReceiveChejanData, VTS_BSTR VTS_I4 VTS_BSTR)
	ON_EVENT(C_KH_OPEN_API, IDC_KHOPENAPICTRL, 5, C_KH_OPEN_API::OnEventConnect, VTS_I4)
	ON_EVENT(C_KH_OPEN_API, IDC_KHOPENAPICTRL, 7, C_KH_OPEN_API::OnReceiveRealCondition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(C_KH_OPEN_API, IDC_KHOPENAPICTRL, 8, C_KH_OPEN_API::OnReceiveTrCondition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4)
	ON_EVENT(C_KH_OPEN_API, IDC_KHOPENAPICTRL, 9, C_KH_OPEN_API::OnReceiveConditionVer, VTS_I4 VTS_BSTR)

END_EVENTSINK_MAP()


WORD C_KH_OPEN_API::request_realdata_stock(bool _bChe, bool _bHoga)
{
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		//std::vector<::CStringW>& vRequestCodes = _bAll ? this->vAllCodes : this->vPiDaqCodes;
		if (_bChe && _bHoga)
		{	// 체결 + 호가 합친거
			DBGPRINT(L"체결 + 호가 요청: %d", this->vFilteredCodes.size());
			return this->set_real_reg(this->vFilteredCodes
				, L"10;11;12;13;14;15;16;17;18;20;21;25;26;27;28;29;30;31;32;41;42;44;45;46;51;52;53;54;55;56;57;58;59;60;61;62;63;64;65;66;67;68;69;70;71;72;73;74;75;76;77;78;79;80;81;82;83;84;85;86;87;88;89;90;91;92;93;94;95;96;97;98;99;100;121;122;125;126;128;129;131;138;139;141;200;201;215;216;228;238;290;291;292;293;294;295;299;311;567;568;621;622;623;624;625;626;627;628;629;630;631;632;633;634;635;636;637;638;639;640;691;9068;9081;"
				L"6044;6100;6105;;6110"
			);
		}
		if (_bChe)
		{	// 체결 등록
			DBGPRINT(L"체결 요청: %d", this->vFilteredCodes.size());
			return this->set_real_reg(this->vFilteredCodes, L"20;10;11;12;27;28;15;13;14;16;17;18;25;26;29;30;31;32;228;311;290;691;567;568;141;9068;131;9081;");

		}
		if (_bHoga)
		{	// 호가 등록
			DBGPRINT(L"호가 요청: %d", this->vFilteredCodes.size());
			return this->set_real_reg(this->vFilteredCodes
				, L"21;41;61;81;51;71;91;42;62;82;52;72;92;43;63;83;53;73;93;44;64;84;54;74;94;45;65;85;55;75;95;46;66;86;56;76;96;47;67;87;57;77;97;48;68;88;58;78;98;49;69;89;59;79;99;50;70;90;60;80;100;121;122;125;126;23;24;128;129;138;139;200;201;238;291;292;293;294;295;621;631;622;632;623;633;624;634;625;635;626;636;627;637;628;638;629;639;630;640;299;215;216;"
				L"6044;6100;6105;;6110"
			);
		}
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
		g_pLog->WriteEx(L"[%s] 예기치 않은 예외 발생", __FUNCTIONW__);
	}
#endif
	return(0);
}

WORD C_KH_OPEN_API::request_realdata_option()
{
	WORD nRet = 0;
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		// GetActPriceList() 함수는 지수옵션 행사가에 100을 곱해서 소수점이 없는 값을 ';'로 구분해서 전달합니다.
		//	[지수옵션 행사가 사용예시]
		// ::CStringW strActPriceList(OpenAPI.GetActPriceList());
		// "19000;19250;19500;19750;20000;20250;20500;20750;21000;21250;21500;21750;..."

		// ";"로 구분하여 벡터에 저장합니다.
		std::vector<::CStringW> actPriceList;
		this->split_to_vec(actPriceList, this->GetActPriceList());
		// 벡터에 저장된 값을 출력합니다.
		//for (const ::CStringW& value : actPriceList)
		//{
		//	DBGPRINT(_T("%s"), value.GetString());
		//}
		// GetMonthList() 함수는 지수옵션 월물정보를 ';'로 구분해서 전달하는데 순서는 콜 11월물 ~ 콜 최근월물 풋 최근월물 ~ 풋 최근월물가 됩니다.
		// [지수옵션 월물조회 사용예시]
		// ::CStringW strMonthList(OpenAPI.GetMonthList());
		// "201812;201806;201712;201706;201703;201612;201611;201610;201609;201608;201607;..."

		// ";"로 구분하여 벡터에 저장합니다.
		std::vector<::CStringW> monthList;
		this->split_to_vec(monthList, this->GetMonthList());
		// 벡터에 저장된 값을 출력합니다.
		//for (const ::CStringW& value : monthList)
		//{
		//	DBGPRINT(_T("%s"), value.GetString());
		//}
		int insertPos = 3;	// 소수점을 삽입할 위치
		constexpr wchar_t insertStr[] = L".";
		::CStringW actPricePoint;
		for (const ::CStringW& actPrice : actPriceList)
		{	// 옵션 가격 리스트의 각 항목에 소수점을 추가하여 옵션 가격 포인트를 만듬
			actPricePoint = actPrice;
			actPricePoint.Insert(insertPos, insertStr);  // ✅ 완전히 동일한 기능

			for (const ::CStringW& month : monthList)
			{
				{	// 콜 옵션 코드 생성
					const ::CStringW& code = this->GetOptionCode(actPricePoint, 2, month);		// 콜
					if (std::find(this->vOptionCodes.begin(), this->vOptionCodes.end(), code) == this->vOptionCodes.end())	// 중복된 값이 없으면
					{
						this->vOptionCodes.push_back(code);										// 코스피200 지수 콜 옵션 코드를 리스트에 추가합니다.
						this->vOptionCodes.push_back(code.Mid(0, 2) + L"5" + code.Mid(3, 5));	// 미니코스피200 지수 콜 옵션 코드를 리스트에 추가합니다.
					}
				}
				{	// 풋 옵션 코드 생성
					const ::CStringW& code = this->GetOptionCode(actPricePoint, 3, month);				// 풋
					if (std::find(this->vOptionCodes.begin(), this->vOptionCodes.end(), code) == this->vOptionCodes.end())	// 중복된 값이 없으면
					{
						this->vOptionCodes.push_back(code);										// 코스피200 지수 풋 옵션 코드를 리스트에 추가합니다.
						this->vOptionCodes.push_back(code.Mid(0, 2) + L"5" + code.Mid(3, 5));	// 미니코스피200 지수 풋 옵션 코드를 리스트에 추가합니다.
					}
				}
			}
		}
		// 벡터에 저장된 값을 출력합니다.
		//::CStringW optionCodeListStr;
		//for (const ::CStringW& value : vOptionCodes)
		//{
		//	DBGPRINT(_T("%s"), value.GetString());
		//	//optionCodeListStr += value + _T(";");
		//}
		// 옵션 이론가 등록
		nRet = this->set_real_reg(this->vOptionCodes, L"195;182;186;190;191;193;192;194;181;246;247;248;187;188;189;");
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
		g_pLog->WriteEx(L"[%s] 예기치 않은 예외 발생", __FUNCTIONW__);
	}
#endif
	return nRet;
}

// GetStockMarketKind 의 리턴값은 문자형으로 아래와 같습니다.
// "0":코스피, "10":코스닥, "3":ELW, "8":ETF, "4"/"14":뮤추얼펀드, "6"/"16":리츠, "9"/"19":하이일드펀드, "30":제3시장, "60":ETN
// 종목 필터링 함수 (Python의 code_delete와 동일한 로직)
static bool is_kind_excluded(int marketKind) {
	// 1. 시장구분값이 아래에 해당하면 제외
	// 3, 4, 6, 8, 9, 14, 16, 19, 30, 60 (ETF, ETN, ELW 등)
	static const std::set<int> excludeKinds = { 3, 4, 6, 8, 9, 14, 16, 19, 30, 60 };
	if (excludeKinds.count(marketKind))
		return true;

	return false;
}

static bool is_word_excluded(LPCWSTR _pName)
{
	constexpr wchar_t szFirstWords[][10] = { L"HANARO ", L"KBSTAR ", L"TIGER ", L"ARIRANG ", L"SOL ", L"ACE ", L"KOSEF ", L"FOCUS ", L"KODEX ", L"WOORI " };
	constexpr wchar_t szExcludeWords[][10] = { L"액티브", L"(합성", L"ETN", L"우B", L"3우C", L"(전환)", L"G3우", L"1우", L"홀딩스", L"스팩" };
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		for (const auto& word : szFirstWords)
		{	// wcsncmp 를 사용해서 이름이 특정 단어로 시작하는지 확인
			const size_t wordLen = ::wcslen(word);
			if (::wcsncmp(_pName, word, wordLen) == 0)
			{	// 특정 단어로 시작하면 제외
				return true;
			}
		}
		for (const auto& word : szExcludeWords)
		{	// wcsstr 를 사용해서 이름에 특정 단어가 포함되어 있는지 확인
			if (::wcsstr(_pName, word) != nullptr)
			{	// 특정 단어가 포함되어 있으면 제외
				return true;
			}
		}
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
		g_pLog->WriteEx(L"[%s] 예기치 않은 예외 발생", __FUNCTIONW__);
	}
#endif
	return(false);
}
static bool is_word_excluded(std::wstring_view _pName)
{
	return is_word_excluded(_pName.data());
}

bool C_KH_OPEN_API::filtered_codes(LPCWSTR _pCode, LPCWSTR _pName, LPCWSTR _pState, LPCWSTR _pGamri)
{
	if (_pCode == nullptr || _pName == nullptr || _pState == nullptr || _pGamri == nullptr)
		return false;	// 코드, 이름, 상태, 감리구분이 없으면 제외
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		if (is_kind_excluded(this->GetStockMarketKind(_pCode)))	// 시장구분이 제외 대상이면
			return false;	// 제외
		if (is_word_excluded(_pName))	// 종목명에 특정 단어가 포함되어 있으면 제외
			return false;	// 제외
		if (::wcsstr(_pState, L"거래정지") || ::wcsstr(_pState, L"관리종목") || !::wcsstr(_pGamri, L"정상"))
			return false;	// 거래정지 또는 관리종목이거나, 감리구분이 정상 상태가 아니면 제외
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
		g_pLog->WriteEx(L"[%s] 예기치 않은 예외 발생", __FUNCTIONW__);
		return false;	// 예외 발생 시 제외
	}
#endif
	return true;	// 필터링된 종목으로 인정
}

void C_KH_OPEN_API::set_login_packet(dk::_PIPE_PACKET& _pPacket)
{
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		_LOGIN_INFO_KW* pBuf = (_LOGIN_INFO_KW*)_pPacket.bytBuffer;
		{	// 서버 구분
			pBuf->bMockServer = static_cast<bool>(::_wtoi(this->GetServerGubun().GetString()));
			if (g_pLog) g_pLog->WriteEx(L"로그인 성공%s", pBuf->bMockServer ? L" (모의서버)" : L"");
			DBGPRINT(L"OnEventConnect() - 로그인 성공%s", pBuf->bMockServer ? L" (모의서버)" : L"");
		}
		// 계좌 비밀번호 입력창을 출력한다.
		//KOA_Functions("ShowAccountWindow"), "");
		//LONG nLoginState = GetConnectState();
		//if (nLoginState)
		{
			//HWND pWnd = ::FindWindow(NULL, "계좌비밀번호 입력 (버전: 4.33)");
			// "" Edit
			// "등록" Button
			// "전체계좌에 등록" Button
			// "AUTO (자동로그인. 공용PC에서 사용하지 마십시요.)" Button
			// "닫기" Button
			// "" ComboBox
			// "비밀번호" Static 에서 "전체계좌에 등록"을 누르면 "등록" 으로 변경된다. 그러면 닫기.
		}
		{	// 아이디
			pBuf->user_id = this->GetLoginInfo(L"USER_ID").GetString();
			if (g_pLog) g_pLog->WriteEx(L"아이디: %s", pBuf->user_id.c_str());
			DBGPRINT(L"OnEventConnect() - USER_ID: %s", pBuf->user_id.c_str());
			// tcp 로 변경될 경우 식별자를 아이디로 하기 위해 저장한다.
			this->szUserid = pBuf->user_id;	// 사용자 아이디를 저장한다.
		}
		{	// 이름
			pBuf->user_name = this->GetLoginInfo(L"USER_NAME").GetString();
			//if (g_pLog) g_pLog->WriteEx(L"이름: %s", pBuf->szName);
			//DBGPRINT(L"OnEventConnect() - USER_NAME: %s", pBuf->szName);
		}
		//DBGPRINT(L"OnEventConnect() - USER_ID: %s, USER_NAME: %s"), pBuf->szID, pBuf->szName);
		{	// 계좌
			pBuf->nAccnoCount = ::_wtoi(this->GetLoginInfo(L"ACCOUNT_CNT").GetString());
			//if (g_pLog) g_pLog->WriteEx(L"계좌개수: %d", pBuf->nAccnoCount);
			//DBGPRINT(L"OnEventConnect() - ACCOUNT_CNT: %d", pBuf->nAccnoCount);

			::CStringW strAccList = this->GetLoginInfo(L"ACCLIST");
			std::list<::CStringW> lstAccount;
			do
			{
				const int nIndex = strAccList.ReverseFind(L';');			// 계좌번호는 ; 로 구분된다. 뒤에서부터 찾는다.
				if (nIndex == -1) { break; }
				::CStringW strAccount = strAccList.Mid(nIndex + 1);
				if (!strAccount.IsEmpty())
				{
					//DBGPRINT(L"OnEventConnect(1) - 계좌번호: %s", strAccount.GetString());
					lstAccount.push_back(strAccount);			// 계좌번호를 추가한다.
				}
				strAccList.Delete(nIndex, strAccList.GetLength() - nIndex);
			} while (true);
			lstAccount.push_back(strAccList);						// 마지막 계좌번호를 추가한다.
			// 이제 lstAccount 를 역순으로 정렬한다
			lstAccount.reverse();
			// 그리고 다시 pBuf->szArrAccounts 에 복사한다.
			int 계좌카운트 = 0;
			for (auto it = lstAccount.begin(); it != lstAccount.end(); ++it)
			{
				//::wcscpy(pBuf->szArrAccounts[계좌카운트++], it->GetString());
				pBuf->szArrAccounts[계좌카운트++] = it->GetString();	// 계좌번호를 복사한다.
				//DBGPRINT(L"OnEventConnect(2) - 키움계좌: %s", pBuf->szArrAccounts[계좌카운트 - 1].c_str());
				if (g_pLog) g_pLog->WriteEx(L"키움계좌: %s", pBuf->szArrAccounts[계좌카운트 - 1].c_str());
				// 기본 계좌를 설정한다.
				if (!this->szDefaultAccno.length())
				{
					this->szDefaultAccno = pBuf->szArrAccounts[0];
					DBGPRINT(L"OnEventConnect(3) - 기본 계좌: %s", this->szDefaultAccno.c_str());
				}
			}
		}
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
		g_pLog->WriteEx(L"[%s] 예기치 않은 예외 발생", __FUNCTIONW__);
	}
#endif
}

void C_KH_OPEN_API::OnEventConnect(long _nErrCode)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static dk::_PIPE_PACKET ipcConnectPacket{};
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		int nUseScreenCount = 0;
		if (!_nErrCode)
		{	// 로그인 성공
			DBGPRINT(L"[%s] 로그인 성공", __FUNCTIONW__);
			{
				// 전송한다.
				ipcConnectPacket.nDataIndex = _PKT_IDX_LOGIN_SUCCESS_;
				ipcConnectPacket.nDataSize = sizeof(_LOGIN_INFO_KW);
				ZeroMemory(ipcConnectPacket.bytBuffer, sizeof(_STOCK_INFO));	// 버퍼를 초기화
				this->set_login_packet(ipcConnectPacket);
				this->pPipe->Send(&ipcConnectPacket);
			}
			//WORD nUseScreenCount = 0;
			//struct _STOCK_INFO
			//	: public _CODE
			//	, public _STOCK_NAME
			//{
			//	bool bBlock{ false };			// 블록 여부, 내가 블록한 종목인지 여부
			//	bool nMarketKind{ false };		// [1]: 코스피, [2]: 코스닥
			//	bool bIsTopIncluded{ 0 };		// 코스피200 또는 코스닥150 지수에 포함되는지 여부

			//	BYTE 종목상태{ false };			// [0]: 정상, [1]: 거래정지, [2]: 거래중단
			//	bool 관리종목{ false };			// 관리종목
			//	BYTE 감리구분{ 0 };				// [0]: 정상, [1]: 투자주의, [20]: 투자경고, [3]: 투자위험, [4]: 투자주의환기종목
			//	bool 담보대출{ false };			// 담보대출
			//	bool 신용가능{ false };			// 신용가능
			//	WORD 증거금{ 0 };				// 증거금

			//	LONGLONG nListedStocks{ 0 };		// 상장주식수
			//	ULONGLONG nMarketCapTotal{ 0 };		// 시가총액
			//};
			std::unordered_map<std::wstring, _STOCK_INFO> umapStockInfo;	// 종목정보 벡터
			umapStockInfo.reserve(4000);				// 많아봐야 4000개 정도이므로 미리 예약해둔다.
			{	// 코스피 필터링
				std::vector<std::wstring> vKospiCodes;
				this->split_to_vec(vKospiCodes, this->GetCodeListByMarket(L"0"));	// 코스피 리스트
				DBGPRINT(L"코스피 개수: %d", vKospiCodes.size());

				for (const std::wstring& code : vKospiCodes)
				{	// 코스피 종목코드 필터링
					if (code.empty() || code.back() != L'0')
						continue;	// 종목코드가 비어있거나 마지막 글자가 '0'이 아니면 제외

					const int nMarketKind = this->GetStockMarketKind(code); // GetStockMarketKind는 int 리턴
					const std::wstring name = this->GetMasterCodeName(code); // 종목명
					const std::wstring state = this->GetMasterStockState(code);
					const std::wstring gamri = this->GetMasterConstruction(code);

					if (!this->filtered_codes(code.c_str(), name.c_str(), state.c_str(), gamri.c_str()))
						continue;	// 필터링된 종목이 아니면 제외
					
					this->vFilteredCodes.push_back(code);

					umapStockInfo.try_emplace(code);
					_STOCK_INFO& stockInfo = umapStockInfo[code];	// 마지막에 추가된 빈 구조체를 참조
					stockInfo.code = code;	// 종목코드
					stockInfo.name = name;
					stockInfo.nMarketKind = nMarketKind;	// 시장구분
					if (state.find(L"담보대출")) { stockInfo.담보대출 = true; }	// 담보대출 여부
					if (state.find(L"신용가능")) { stockInfo.신용가능 = true; }	// 신용가능 여부
					stockInfo.증거금 = (WORD)::_wtoi(state.c_str());
					stockInfo.nListedStocks = this->GetMasterListedStockCnt(code);	// 상장주식수
					stockInfo.nMarketCapTotal = this->GetMasterLastPrice(code) * stockInfo.nListedStocks;	// 시가총액 = 종가 * 상장주식수
				}
			}
			{	// 코스닥 필터링
				std::vector<std::wstring> vKosdaqCodes;
				this->split_to_vec(vKosdaqCodes, this->GetCodeListByMarket(L"10"));	// 코스닥 리스트
				DBGPRINT(L"코스닥 개수: %d", vKosdaqCodes.size());
				// 코스닥 종목코드 필터링
				for (const std::wstring& code : vKosdaqCodes)
				{
					if (code.empty() || code.back() != L'0')
						continue;	// 종목코드가 비어있거나 마지막 글자가 '0'이 아니면 제외

					const int nMarketKind = this->GetStockMarketKind(code); // GetStockMarketKind는 int 리턴
					const std::wstring name = this->GetMasterCodeName(code); // 종목명
					const std::wstring state = this->GetMasterStockState(code);
					const std::wstring gamri = this->GetMasterConstruction(code);

					if (!this->filtered_codes(code.c_str(), name.c_str(), state.c_str(), gamri.c_str()))
						continue;	// 필터링된 종목이 아니면 제외

					this->vFilteredCodes.push_back(code);

					umapStockInfo.try_emplace(code);
					_STOCK_INFO& stockInfo = umapStockInfo[code];	// 마지막에 추가된 빈 구조체를 참조
					stockInfo.code = code;	// 종목코드
					stockInfo.name = name;
					stockInfo.nMarketKind = nMarketKind;	// 시장구분
					if (state.find(L"담보대출")) { stockInfo.담보대출 = true; }	// 담보대출 여부
					if (state.find(L"신용가능")) { stockInfo.신용가능 = true; }	// 신용가능 여부
					stockInfo.증거금 = (WORD)::_wtoi(state.c_str());
					stockInfo.nListedStocks = this->GetMasterListedStockCnt(code);	// 상장주식수
					stockInfo.nMarketCapTotal = this->GetMasterLastPrice(code) * stockInfo.nListedStocks;	// 시가총액 = 종가 * 상장주식수
				}
			}
			DBGPRINT(L"필터링된 종목 개수1: %d / %d", this->vFilteredCodes.size(), umapStockInfo.size());
			{	// NXT 필터링
				std::vector<std::wstring> vNxtCodes;
				this->split_to_vec(vNxtCodes, this->GetCodeListByMarket(L"NXT"));
				DBGPRINT(L"NXT 종목 개수: %d", vNxtCodes.size());
				// nxt 코드의 문자열 뒤에 "_NX" 을 붙여서 vPiDaqCodes에 추가
				for (const std::wstring& code : vNxtCodes)
				{
					auto& stockInfo = umapStockInfo.find(code)->second;	// NXT 종목정보를 찾는다.
					stockInfo.bNXT = true;	// NXT 종목임을 표시
					// 종목코드에 "_NX"를 붙여서 vFilteredCodes에 추가
					const std::wstring nxt_code = code + L"_NX";	// NXT 종목코드
					this->vFilteredCodes.push_back(nxt_code);
				}
			}
			DBGPRINT(L"필터링된 종목 개수2: %d / %d", this->vFilteredCodes.size(), umapStockInfo.size());
			{
				// 종목 개수를 보낸다
				ipcConnectPacket.nDataIndex = _PKT_IDX_RESULT_STOCK_COUNT_KIWOOM_;
				ipcConnectPacket.nDataSize = sizeof(DWORD);
				ZeroMemory(ipcConnectPacket.bytBuffer, sizeof(_STOCK_INFO));	// 버퍼를 초기화

				const DWORD nCount = static_cast<DWORD>(umapStockInfo.size());	// 필터링된 종목 개수
				::memcpy(ipcConnectPacket.bytBuffer, &nCount, sizeof(DWORD));	// 필터링된 종목 개수를 복사한다.
				this->pPipe->Send(&ipcConnectPacket);
			}
			{
				// 필터링된 종목정보를 전송한다.
				ipcConnectPacket.nDataIndex = _PKT_IDX_STOCK_INFO_KIWOOM_;
				ipcConnectPacket.nDataSize = sizeof(_STOCK_INFO);
				// umapStockInfo 에서
				//const size_t nStockCount = umapStockInfo.size();	// 종목 개수
				//size_t nSendCount = 0;	// 전송한 종목 개수
				for (const auto& pair : umapStockInfo)
				{	// 종목코드를 순회하면서
					const std::wstring& code = pair.first;	// 종목코드
					
					_STOCK_INFO& stockInfo = umapStockInfo[code];	// 종목정보를 참조
					ZeroMemory(ipcConnectPacket.bytBuffer, sizeof(_STOCK_INFO));	// 버퍼를 초기화
					::memcpy(ipcConnectPacket.bytBuffer, &stockInfo, sizeof(_STOCK_INFO));	// 종목정보를 복사한다.
					this->pPipe->Send(&ipcConnectPacket);
					//DBGPRINT(L"전송 %d/%d: %s, %s", ++nSendCount, nStockCount, stockInfo.code.c_str(), stockInfo.name.c_str());
				}
				umapStockInfo.clear();	// 종목정보 맵을 비운다.
			}
			{	// 실시간 체결, 호가 데이터 요청
				if (this->bRequestChe || this->bRequestHoga)
				{	// 체결, 호가 한번에 요청
					nUseScreenCount = this->request_realdata_stock(this->bRequestChe, this->bRequestHoga);
					g_pLog->WriteEx(L"[%s] 주식 체결, 호가 요청: %d/%d, 사용한 화면 개수: %d", __FUNCTIONW__, this->vFilteredCodes.size(), this->vFilteredCodes.size(), nUseScreenCount);
					DBGPRINT(L"체결 호가 요청: %d/%d, 사용한 화면 개수: %d", this->vFilteredCodes.size(), this->vFilteredCodes.size(), nUseScreenCount);
				}
			}
			if (this->bRequestUpViAlram)
			{	// VI 알람 요청
				this->SetInputValue(L"시장구분", L"000");
				this->SetInputValue(L"장전구분", L"0");
				this->SetInputValue(L"종목코드", L"000");
				this->SetInputValue(L"발동구분", L"0");
				this->SetInputValue(L"제외종목", L"000000000");
				this->SetInputValue(L"거래량구분", L"0");
				this->SetInputValue(L"최소거래량", L"0");
				this->SetInputValue(L"최대거래량", L"0");
				this->SetInputValue(L"거래대금구분", L"0");
				this->SetInputValue(L"최소거래대금", L"0");
				this->SetInputValue(L"최대거래대금", L"0");
				this->SetInputValue(L"발동방향", L"0");

				const kw::C_KIWOOM_SCREEN* pScreen = this->get_screen_number();
				if (!this->CommRqData(L"VI발동/해제", _TR_OPT10054_, 0, pScreen->szScrNum))
				{
					g_pLog->WriteEx(L"[%s] VI발동/해제 요청 성공", __FUNCTIONW__);
					DBGPRINT(L"VI발동/해제 요청 성공");
				}
				else
				{
					g_pLog->WriteEx(L"[%s] VI발동/해제 요청 실패", __FUNCTIONW__);
					DBGPRINT(L"VI발동/해제 요청 실패");
				}
			}
			if (this->bRequestUpjongJisu)
			{	// 업종 지수 요청
				std::vector<std::wstring> vTemp;
				this->split_to_vec(vTemp, this->GetUpjongCode(), L",");

				for (const std::wstring& code : vTemp)
				{   // code 가 전부 숫자이며, 2자리 이상이면 vUpjongCodes 에 추가한다.
					if (code.length() > 2 && dk::is_num(code.c_str()))
					{
						this->vUpjongCodes.push_back(code);
					}
				}
				// 업종 지수 등록
				nUseScreenCount = this->set_real_reg(this->vUpjongCodes, L"20;10;11;12;15;13;14;16;17;18;25;26;252;251;253;255;256;257;");
				g_pLog->WriteEx(L"[%s] 업종 지수 요청: %d, 사용한 화면 개수: %d", __FUNCTIONW__, this->vUpjongCodes.size(), nUseScreenCount);
				DBGPRINT(L"업종 요청: %d, 사용한 화면 개수: %d", this->vUpjongCodes.size(), nUseScreenCount);
			}
			{	// ELW

				::CStringW& strStockCodeELW = this->GetCodeListByMarket(L"3");	// ELW 리스트
				std::vector<std::wstring> vTemp;
				this->split_to_vec(vTemp, strStockCodeELW);
				nUseScreenCount = this->set_real_reg(vTemp, L"20;666;1211;667;668;669;");
				DBGPRINT(L"ELW 요청: %d, 사용한 화면 개수: %d", vTemp.size(), nUseScreenCount);
			}
			{	// ETF
				::CStringW& strStockCodeETF = this->GetCodeListByMarket(L"8");	// ETF 리스트
				std::vector<std::wstring> vTemp;
				this->split_to_vec(vTemp, strStockCodeETF);
				nUseScreenCount = this->set_real_reg(vTemp, L"20;10;36;37;38;39;11;12;13;25;667;668;669;265;266;");
				DBGPRINT(L"ETF 요청: %d, 사용한 화면 개수: %d", vTemp.size(), nUseScreenCount);
			}
			{
				//::CStringW strCodes = GetCodeListByMarket(L""));    // 공백으로 하면 전체시장 코드리스트
				//::CStringW strExclude1 = this->GetCodeListByMarket(L"4");		// 뮤추얼펀드 리스트
				//this->split_to_vec(this->vOtherCodes, strExclude1);
				//::CStringW strExclude2 = this->GetCodeListByMarket(L"5");		// 신주인수권 리스트
				//this->split_to_vec(this->vOtherCodes, strExclude2);
				//::CStringW strExclude3 = this->GetCodeListByMarket(L"6");		// 리츠 리스트
				//this->split_to_vec(this->vOtherCodes, strExclude3);
				//::CStringW strExclude5 = this->GetCodeListByMarket(L"9");		// 하이일드펀드 리스트
				//this->split_to_vec(this->vOtherCodes, strExclude5);
				//::CStringW strExclude6 = this->GetCodeListByMarket(L"30");		// K-OTC 리스트
				//this->split_to_vec(this->vOtherCodes, strExclude6);
				//::CStringW strExclude7 = this->GetCodeListByMarket(L"50");		// 코넥스(KONEX) 리스트
				//this->split_to_vec(this->vOtherCodes, strExclude7);
				//DBGPRINT(L"기타 개수: %d", this->vOtherCodes.size());

				// 코스피, 코스닥, 기타를 vAllCodes에 합친다.
				//this->vAllCodes.reserve(this->vKospiCodes.size() + this->vKosdaqCodes.size() + this->vOtherCodes.size());
				//this->vAllCodes.insert(this->vAllCodes.end(), this->vKospiCodes.begin(), this->vKospiCodes.end());
				//this->vAllCodes.insert(this->vAllCodes.end(), this->vKosdaqCodes.begin(), this->vKosdaqCodes.end());
				//this->vAllCodes.insert(this->vAllCodes.end(), this->vOtherCodes.begin(), this->vOtherCodes.end());
				//DBGPRINT(L"전체 종목 개수: %d", this->vAllCodes.size());
				// 중복되는 코드 제거
				//std::sort(this->vAllCodes.begin(), this->vAllCodes.end());
				//this->vAllCodes.erase(std::unique(this->vAllCodes.begin(), this->vAllCodes.end()), this->vAllCodes.end());
				//DBGPRINT(L"중복 제거 후 전체 종목 개수: %d", this->vAllCodes.size());
			}
			if (this->bRequestFutureChe || this->bRequestFutureHoga)
			{
				::CStringW& strFuthreCodes = this->GetFutureList();
				this->split_to_vec(this->vFutureCodes, strFuthreCodes);
				// 선물 체결, 호가, 이론가 한번에 요청
				nUseScreenCount = set_real_reg(this->vFutureCodes, L"195;182;184;183;186;181;185;246;247;248;");
				g_pLog->WriteEx(L"[%s] 선물 체결, 호가, 이론가 요청: %d, 사용한 화면 개수: %d", __FUNCTIONW__, this->vFutureCodes.size(), nUseScreenCount);
				DBGPRINT(L"선물 요청: %d, 사용한 화면 개수: %d", this->vFutureCodes.size(), nUseScreenCount);
			}
			if (this->bRequestOptionChe || this->bRequestOptionHoga)
			{	// 옵션 체결, 호가, 이론가 한번에 요청
				nUseScreenCount = this->request_realdata_option();
				g_pLog->WriteEx(L"[%s] 옵션 체결, 호가, 이론가 요청: %d, 사용한 화면 개수: %d", __FUNCTIONW__, this->vOptionCodes.size(), nUseScreenCount);
				DBGPRINT(L"코스피200 + 미니코스피200 지수 옵션 요청: %d, 사용한 화면 개수: %d", this->vOptionCodes.size(), nUseScreenCount);
			}
			
			g_pLog->WriteEx(L"[%s] 사용한 화면 개수: %d, 남은 화면 개수: %d", __FUNCTIONW__, kw::_MAX_SCREEN_COUNT_ - this->nRemainScreenCount, this->nRemainScreenCount);
			DBGPRINT(L"사용한 화면 개수: %d, 남은 화면 개수: %d", kw::_MAX_SCREEN_COUNT_ - this->nRemainScreenCount, this->nRemainScreenCount);
			if (this->pPipe) { this->pPipe->Send(_PKT_IDX_KW_실시간_등록_완료_); }
		}
		else
		{	// 로그인 실패
			ipcConnectPacket.nDataIndex = _PKT_IDX_LOGIN_FAILED_;
			ipcConnectPacket.nDataSize = sizeof(DWORD);
			::memcpy(ipcConnectPacket.bytBuffer, &_nErrCode, sizeof(DWORD));	// 에러코드를 복사한다.
			this->pPipe->Send(&ipcConnectPacket);

			g_pLog->WriteEx(L"[%s] 로그인 실패: %d", __FUNCTIONW__, _nErrCode);
			DBGPRINT(L"OnEventConnect() - 로그인 실패: %d", _nErrCode);
		}
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		g_pLog->WriteEx(L"[%s] 예외발생", __FUNCTIONW__);
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
	}
#endif
}

void C_KH_OPEN_API::OnReceiveMsg(LPCWSTR sScrNo, LPCWSTR sRQName, LPCWSTR sTrCode, LPCWSTR sMsg)
{
	sScrNo;
	sRQName;
	sTrCode;
	sMsg;
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		DBGPRINT(L"OnReceiveMsg() - %s / %s / %s / %s"
			, sScrNo
			, sRQName
			, sTrCode
			, sMsg
		);
		//release_screen(pCurrentOrder->szScrNo);
		if (!::wcscmp(sTrCode, L"KOA_NORMAL_BUY_KQ_ORD")
			|| !::wcscmp(sTrCode, L"KOA_NORMAL_SELL_KQ_ORD")
			|| !::wcscmp(sTrCode, L"KOA_NORMAL_KQ_MODIFY")
			)
		{
			if (!::wcsncmp(sMsg, L"[RC", 3))
			{	// 주문이 실패하면 화면번호 해제
				this->release_screen(sScrNo);
			}
		}
		else if (!::wcscmp(sTrCode, L"KOA_NORMAL_KQ_CANCEL"))
		{
			if (::wcsstr(sMsg, L"[100000]"))
			{	// 취소는 성공하면 화면번호 해제.
				this->release_screen(sScrNo);
			}
		}
		// OnReceiveMsg() - 0001 / test_order / KOA_NORMAL_BUY_KQ_ORD / [RC4025] 모의투자 매수증거금이 부족합니다.
		// // OnReceiveMsg() - 0002 / test_order / KOA_NORMAL_BUY_KQ_ORD / [RC4027] 모의투자 상 / 하한가 오류입니다.
		// // OnReceiveMsg() - 0001 / test_order / KOA_NORMAL_BUY_KQ_ORD / [100000] 모의투자 매수주문완료
		// OnReceiveMsg() - 0004 / test_order / KOA_NORMAL_SELL_KQ_ORD / [100000] 모의투자 매도주문완료
		// OnReceiveMsg() - 0005 / test_order / KOA_NORMAL_KQ_MODIFY / [100000] 모의투자 매수주문완료 ( 매수 주문후 가격 정정시 )
		// OnReceiveMsg() - 0005 / test_order / KOA_NORMAL_KQ_MODIFY / [100000] 모의투자 매도주문완료 ( 매도 주문후 가격 정정시 )

		// OnReceiveMsg() - 0001 / test_order / KOA_NORMAL_KQ_CANCEL / [RC4033] 모의투자 정정/취소할 수량이 없습니다. ( 매수 주문 후 매도 취소 시 발생 )
		// OnReceiveMsg() - 0003 / test_order / KOA_NORMAL_KQ_CANCEL / [RC4061] 모의투자 주문번호를 확인하세요.
		// OnReceiveMsg() - 0004 / test_order / KOA_NORMAL_KQ_CANCEL / [100000] 모의투자 취소주문완료

		// 
		//dk::_PIPE_PACKET packet =
		//{	// 메모리 할당과 복사를 한번만 하기 위해 여기에서 _PIPE_PACKET 를 할당한다.
		//	_PKT_IDX_KIWOOM_RESULT_CANCEL_ORDER_
		//	, sizeof(_RESULT_CANCEL_ORDER_KW)
		//	, { 0 }
		//};
		//_RESULT_CANCEL_ORDER_KW* pResult = (_RESULT_CANCEL_ORDER_KW*)packet.bytBuffer;
		//::wcscpy(pResult->szScrNo, sScrNo);
		//if ((::strstr(sTrCode, "KQ_ORD") || ::strstr(sTrCode, "KQ_MODIFY")) && ::strstr(sMsg, "100000"))
		//{
		//	DBGPRINT(L"화면 등록 요청: %s"), sScrNo);
		//	pResult->bRegi = true;
		//}
		//else
		//{
		//	DBGPRINT(L"화면 해제 요청: %s"), sScrNo);
		//	pResult->bRegi = false;
		//}
		//if (pPipe) { pPipe->Send(&packet); }
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
	}
#endif
}

void C_KH_OPEN_API::OnReceiveTrData(LPCWSTR _sScrNum, LPCWSTR sRQName, LPCWSTR sTrCode, LPCWSTR sRecordName, LPCWSTR sPrevNext, long nDataLength, LPCWSTR sErrorCode, LPCWSTR sMessage, LPCWSTR sSplmMsg)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	_sScrNum;
	sRQName;
	sRecordName;
	sPrevNext;
	nDataLength;
	sErrorCode;
	sMessage;
	sSplmMsg;
	static dk::_PIPE_PACKET ipcTrPacket{};
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		ZeroMemory(&ipcTrPacket, sizeof(dk::_PIPE_PACKET));
		DBGPRINT(L"OnReceiveTrData() - %s / %s / %s / %s / %s / %d / %s / %s / %s"
			, sTrCode
			, _sScrNum		// "0001"
			, sRQName		// "test_order"
			, sRecordName	// ""
			, sPrevNext		// ""
			, nDataLength	// 0
			, sErrorCode	// ""
			, sMessage		// ""
			, sSplmMsg		// ""
		);
		//long nRecvCount = GetRepeatCnt(sTrCode, sRQName);
		if (!::wcscmp(_TR_OPW00001_, sTrCode))
		{	// 예수금상세현황요청
			ipcTrPacket.nDataIndex = _PKT_IDX_RESULT_OPW00001_;
			ipcTrPacket.nDataSize = sizeof(_RESULT_TR_OPW00001);
			_RESULT_TR_OPW00001* pBuf = (_RESULT_TR_OPW00001*)ipcTrPacket.bytBuffer;
			::wcscpy(pBuf->예수금, this->GetCommData(sTrCode, L"예수금상세현황", 0, L"예수금").GetString());	// 화면번호
			::wcscpy(pBuf->출금가능금액, this->GetCommData(sTrCode, L"예수금상세현황", 0, L"출금가능금액").GetString());	// 출금가능금액
			::wcscpy(pBuf->주문가능금액, this->GetCommData(sTrCode, L"예수금상세현황", 0, L"주문가능금액").GetString());	// 주문가능금액
		}
		if (0 < ipcTrPacket.nDataSize)
		{
			//DBGPRINT(L"[%s] 보낸다: %d", _sRealKey, ipcTrPacket.nDataSize);
			this->pPipe->Send(&ipcTrPacket);
		}
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
	}
#endif
}

void C_KH_OPEN_API::OnReceiveRealData(LPCWSTR _sRealKey, LPCWSTR _sRealType, LPCWSTR _sRealData)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	_sRealData;
	constexpr size_t nStartPos = 1;
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		static bool bFirstLog = false;
		if (!bFirstLog)
		{
			bFirstLog = true;
			g_pLog->WriteEx(L"[%s] 실시간 데이터 첫 데이터 수신 성공", __FUNCTIONW__);
		}
		//DBGPRINT(L"OnReceiveRealData() - %d %s/%s/%s"), nRealDataSequence, _sRealKey, _sRealType, _sRealData);
		//if (!::wcscmp(_sRealType, L"주식체결")))
		ZeroMemory(&this->currentPacket, sizeof(dk::_PIPE_PACKET));
		//const ULONGLONG nRealType = *(ULONGLONG*)&_sRealType[1];
		switch (*(ULONGLONG*)&_sRealType[nStartPos]) // 64비트에서 65.4%, 32비트 환경에서 wcscmp 보다 51.3% 빠르다.
		{
		case N주식체결:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_주식체결_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_주식체결);
			//this->CombineRealData((_RAW_실시간_주식체결*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_주식체결*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N주식호가잔량:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_주식호가잔량_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_주식호가잔량);
			//this->CombineRealData((_RAW_실시간_주식호가잔량*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_주식호가잔량*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		//case N주식우선호가:
		//	this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_주식우선호가_;
		//	this->currentPacket.nDataSize = sizeof(_RAW_실시간_주식우선호가);
		//	this->CombineRealData((_RAW_실시간_주식우선호가*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
		//	break;
		//case N주식예상체결:
		//	this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_주식예상체결_;
		//	this->currentPacket.nDataSize = sizeof(_RAW_실시간_주식예상체결);
		//	this->CombineRealData((_RAW_실시간_주식예상체결*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
		//	break;
		case N종목프로그램매매:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_종목프로그램매매_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_종목프로그램매매);
			//this->CombineRealData((_RAW_실시간_종목프로그램매매*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_종목프로그램매매*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N주식당일거래원:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_주식당일거래원_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_주식당일거래원);
			//this->CombineRealData((_RAW_실시간_주식당일거래원*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_주식당일거래원*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case NVI발동해제:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_VI발동해제_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_VI발동해제);
			//this->CombineRealData((_RAW_실시간_VI발동해제*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_VI발동해제*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N업종지수:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_업종지수_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_업종지수);
			//this->CombineRealData((_RAW_실시간_업종지수*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_업종지수*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N업종등락:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_업종등락_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_업종등락);
			//this->CombineRealData((_RAW_실시간_업종등락*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_업종등락*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N선물시세:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_선물시세_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_선물시세);
			//this->CombineRealData((_RAW_실시간_선물시세*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_선물시세*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N선물호가잔량:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_선물호가잔량_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_선물호가잔량);
			//this->CombineRealData((_RAW_실시간_선물호가잔량*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_선물호가잔량*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N선물이론가:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_선물이론가_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_선물이론가);
			//this->CombineRealData((_RAW_실시간_선물이론가*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_선물이론가*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N옵션시세:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_옵션시세_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_옵션시세);
			//this->CombineRealData((_RAW_실시간_옵션시세*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_옵션시세*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N옵션호가잔량:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_옵션호가잔량_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_옵션호가잔량);
			//this->CombineRealData((_RAW_실시간_옵션호가잔량*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_옵션호가잔량*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N옵션이론가:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_옵션이론가_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_옵션이론가);
			//this->CombineRealData((_RAW_실시간_옵션이론가*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_옵션이론가*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case NETF_NAV:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_ETF_NAV_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_ETF_NAV);
			//this->CombineRealData((_RAW_실시간_ETF_NAV*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_ETF_NAV*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case NELW_지표:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_ELW_지표_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_ELW_지표);
			//this->CombineRealData((_RAW_실시간_ELW_지표*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_ELW_지표*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case NELW_이론가:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_ELW_이론가_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_ELW_이론가);
			//this->CombineRealData((_RAW_실시간_ELW_이론가*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_ELW_이론가*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		case N장시작시간:
			this->currentPacket.nDataIndex = _PKT_IDX_RAW_키움_장시작시간_;
			this->currentPacket.nDataSize = sizeof(_RAW_실시간_장시작시간);
			//this->CombineRealData((_RAW_실시간_장시작시간*)this->currentPacket.bytBuffer, _sRealKey, _sRealData);
			this->FillRealData((_RAW_실시간_장시작시간*)this->currentPacket.bytBuffer, _sRealKey);
			break;
		//default:
		//	DBGPRINT(L"❗️[실시간] %s 알 수 없는 실시간 타입: %s / %llx / %s"
		//		, _sRealKey
		//		, _sRealType
		//		, *(ULONG_PTR*)&_sRealType[1]
		//		, _sRealData
		//	);
		//	break;
		}
		if (0 < this->currentPacket.nDataSize)
		{
			//DBGPRINT(L"[%s] 보낸다: %d", _sRealKey, this->currentPacket.nDataSize);
			this->pPipe->Send(&currentPacket);
		}
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
	}
#endif
}

void C_KH_OPEN_API::OnReceiveChejanData(	// 체결 잔고 실시간 처리
	LPCWSTR _sGubun							// 체결구분. 접수와 체결시 '0'값, 국내주식 잔고변경은 '1'값, 파생잔고변경은 '4'
	, long _nItemCnt
	, LPCWSTR _sFIdList
)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//0: 체결 데이터
	//1 : 잔고 데이터
	//3 : 특이신호
	//4 : 조회
	//5 : 실시간 데이터
	//6 : 관심종목 체결 데이터
	//7 : 주문체결 데이터
	//8 : 장시작시간 데이터
	//9 : 예상체결 데이터
	//10 : 장운영정보 데이터
	//11 : 시간외단일가 체결 데이터
	//12 : 시간외종가 체결 데이터
	//13 : 체결강도 데이터
	//14 : 파생잔고 데이터
	//15 : 정정 / 취소 데이터
	//16 : 미체결 데이터
	//17 : 단일가 호가집계 데이터
	//18 : RTD 데이터
	static dk::_PIPE_PACKET ipcChejanPacket{};
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		DBGPRINT(L"OnReceiveChejanData() - %s / %d / %s"
			, _sGubun
			, _nItemCnt
			, _sFIdList
		);
		ZeroMemory(&ipcChejanPacket, sizeof(dk::_PIPE_PACKET));
		if (!wcscmp(_sGubun, L"0"))
		{
			_실시간_키움_주문체결통보 pResultOrder;
			// CJ_TRADE(체결)에 대한 체결 데이터 가져오기
			::wcscpy(pResultOrder.szCode, this->GetChejanData(_주문체결_종목코드_).TrimLeft(L'A').GetString());	// 종목코드
			//DBGPRINT(L"종목코드 : %s"), pResultOrder.szCode);
			//::wcscpy(pResultOrder.szAccno, this->GetChejanData(_주문체결_계좌번호_).GetString());	// 계좌번호
			//DBGPRINT(L"계좌번호 : %s"), pResultOrder.szAccno);
			::wcscpy(pResultOrder.szPrice, this->GetChejanData(_주문체결_주문가격_).GetString());	// 주문가격
			//DBGPRINT(L"주문가격 : %s"), pResultOrder.szPrice);
			::wcscpy(pResultOrder.szOrdVolume, this->GetChejanData(_주문체결_주문수량_).GetString()); // 주문수량
			//DBGPRINT(L"주문수량 : %s"), pResultOrder.szOrdVolume);
			// 미체결수량
			//sData = this->GetChejanData(_주문체결_미체결수량_);
			//pResultOrder.nUnsettledVolume = ::_wtoi(sData.GetString());
			::wcscpy(pResultOrder.szUnsettledVolume, this->GetChejanData(_주문체결_미체결수량_).GetString()); // 미체결수량
			//DBGPRINT(L"미체결수량 : %d"), pResultOrder.nUnsettledVolume);	// 미체결 수량이 0 이면 모두 체결된 것임
			// 주문상태, +매수, -매도, -매도정정, +매수정정, 매수취소, 매도취소
			::wcscpy(pResultOrder.szOrdType, this->GetChejanData(_주문체결_주문구분_).GetString()); // 주문구분

			// 주문상태: 접수, 확인, 체결, 거부, 접수거부, 확인거부
			::wcscpy(pResultOrder.szOrdStatus, this->GetChejanData(_주문체결_주문상태_).GetString()); // 주문상태
			//DBGPRINT(L"주문상태 : %s", pResultOrder.szOrdStatus);

			// CJ_ORD(주문)에 대한 체결 데이터 가져오기
			::wcscpy(pResultOrder.szOrdNo, this->GetChejanData(_주문체결_주문번호_).GetString()); // 주문번호
			//DBGPRINT(L"주문번호 : %s"), sData.GetString());

			// 원주문번호
			::wcscpy(pResultOrder.szOrgOrdNo, this->GetChejanData(_주문체결_원주문번호_).GetString()); // 원주문번호
			//DBGPRINT(L"원주문번호 : %s"), sData.GetString());

			::wcscpy(pResultOrder.szScrNo, this->GetChejanData(_주문체결_화면번호_).GetString()); // 화면번호
			//DBGPRINT(L"화면번호 : %s"), sData.GetString());

			::wcscpy(pResultOrder.szCheTime, this->GetChejanData(_주문체결_주문체결시간_).GetString()); // 주문체결시간
			////DBGPRINT(L"주문체결시간 : %s"), sData.GetString());

			::wcscpy(pResultOrder.szTransVolume, this->GetChejanData(_주문체결_체결량_).GetString()); // 체결량
			////DBGPRINT(L"체결수량 : %d"), pResultOrder.nTransVolume);

			::wcscpy(pResultOrder.szTransPrice, this->GetChejanData(_주문체결_체결가_).GetString()); // 체결가
			//DBGPRINT(L"_주문체결_체결가 : %d"), pResultOrder.dbTransPrice);
			//// 단위체결수량
			::wcscpy(pResultOrder.szUnitTransVolume, this->GetChejanData(_주문체결_단위체결량_).GetString()); // 단위체결수량
			//DBGPRINT(L"단위체결수량 : %d"), pResultOrder.nUnitTransVolume);

			//// 단위체결가
			::wcscpy(pResultOrder.szUnitTransPrice, this->GetChejanData(_주문체결_단위체결가_).GetString()); // 단위체결가
			//DBGPRINT(L"단위체결가 : %d"), pResultOrder.dbUnitTransPrice);

			// 한줄로 출력해본다
			DBGPRINT(L"[체잔] %s 화면: %s, 코드: %s, 주문량: %s, 체결량: %s, 체결가: %s, 미체결수량: %s, 주문구분: %s, 주문번호: %s, 원주문번호: %s, 주문체결시간: %s"
				, pResultOrder.szOrdStatus
				, pResultOrder.szScrNo
				, pResultOrder.szCode
				, pResultOrder.szOrdVolume
				, pResultOrder.szTransVolume
				, pResultOrder.szTransPrice
				, pResultOrder.szUnsettledVolume
				, pResultOrder.szOrdType
				, pResultOrder.szOrdNo
				, pResultOrder.szOrgOrdNo
				, pResultOrder.szCheTime
			);

			//theApp.recv_chejan(&pResultOrder);

			// _주문체결_매도수구분
			//::wcscpy(pResultOrder.szBuySellType, this->GetChejanData(_주문체결_매도수구분_).GetString()); // 매도수구분
			//DBGPRINT(L"매도수구분 : %s"), sData.GetString());	// 매도(매도정정, 매도취도 포함)인 경우 1, 매수(매수정정, 매수취소 포함)인 경우 2 

			//sData = this->GetChejanData(949);
			//DBGPRINT(L"949 : %s"), sData.GetString());

			//sData = this->GetChejanData(10010);
			//DBGPRINT(L"10010 : %s"), sData.GetString());

			//sData = this->GetChejanData(969);
			//DBGPRINT(L"969 : %s"), sData.GetString());

			//sData = this->GetChejanData(819);
			//DBGPRINT(L"819 : %s"), sData.GetString());
			//DBGPRINT(L"OnReceiveChejanData() - %d / %s / %s"), _nItemCnt, _sGubun, _sFIdList);
		}
		else if (!wcscmp(_sGubun, L"1"))
		{
			_실시간_키움_잔고통보 pResultOrder;
			::wcscpy(pResultOrder.szCode, this->GetChejanData(_잔고_종목코드_).TrimLeft(L'A').GetString()); // 종목코드
			//DBGPRINT(L"종목코드 : %s"), pResultOrder.szCode);

			::wcscpy(pResultOrder.szVolume, this->GetChejanData(_잔고_보유수량_).GetString()); // 보유수량
			//DBGPRINT(L"보유수량 : %s")
			
			::wcscpy(pResultOrder.szOrderableVolume, this->GetChejanData(_잔고_주문가능수량_).GetString()); // 주문가능수량
			//DBGPRINT(L"_잔고_주문가능수량_ : %s", pResultOrder.szOrderableVolume);

			//sData = this->GetChejanData(_잔고_계좌번호);
			::wcscpy(pResultOrder.szAccno, this->GetChejanData(_잔고_계좌번호_).GetString()); // 계좌번호
			//DBGPRINT(L"계좌번호 : %s", pResultOrder.szAccno);

			::wcscpy(pResultOrder.szBuyPrice, this->GetChejanData(_잔고_매입단가_).GetString()); // 매입단가
			//DBGPRINT(L"매입단가 : %s", pResultOrder.szBuyPrice);

			::wcscpy(pResultOrder.szTotalBuyPrice, this->GetChejanData(_잔고_총매입가_).GetString()); // 총매입가
			//DBGPRINT(L"총매입가 : %s", pResultOrder.szTotalBuyPrice);

			::wcscpy(pResultOrder.szDeposit, this->GetChejanData(_잔고_예수금_).GetString()); // 예수금
			//DBGPRINT(L"예수금 : %s", pResultOrder.szDeposit);

			::wcscpy(pResultOrder.szProfitRate, this->GetChejanData(_잔고_손익율_).GetString()); // 손익율
			//DBGPRINT(L"손익율 : %s", pResultOrder.szProfitRate);

			//DBGPRINT(L"OnReceiveChejanData() - %d / %s / %s"), _nItemCnt, _sGubun, _sFIdList);
		}
		else
		{
			// _주문체결_계좌번호;
			// _주문체결_주문번호;
			// _주문체결_관리자사번;
			// _주문체결_종목코드;
			// _주문체결_주문업무분류;
			// _주문체결_주문상태;
			// _주문체결_종목명;
			// _주문체결_주문수량;
			// _주문체결_주문가격;
			// _주문체결_미체결수량;
			// _주문체결_체결누계금액;
			// _주문체결_원주문번호;
			// _주문체결_주문구분;		// (+매수, -매도, -매도정정, +매수정정, 매수취소, 매도취소)
			// _주문체결_매매구분;		// (보통, 시장가등)
			// _주문체결_매도수구분;
			// _주문체결_주문체결시간;
			// _주문체결_체결번호;
			// _주문체결_체결가;
			// _주문체결_체결량;
			// _주문체결_현재가;
			// _주문체결_최우선매도호가;
			// _주문체결_최우선매수호가;
			// _주문체결_단위체결가;
			// _주문체결_단위체결량;
			// _주문체결_당일매매수수료;
			// _주문체결_당일매매세금;
			// _주문체결_거부사유;
			// _주문체결_화면번호;
			// _주문체결_터미널번호;
			// _주문체결_신용구분;
			// _주문체결_대출일;
			DBGPRINT(L"OnReceiveChejanData() - %d / %s / %s", _nItemCnt, _sGubun, _sFIdList);
		}

		if (0 < ipcChejanPacket.nDataSize)
		{
			//DBGPRINT(L"[체잔] 보낸다: %d", ipcChejanPacket.nDataSize);
			this->pPipe->Send(&ipcChejanPacket);
		}

		//::CStringW strFidList	= _sFIdList;
		//	//m_listCtrl.AddString("체결정보");
		//do
		//{
		//	int nIndex = strFidList.ReverseFind(';');
		//	if (nIndex == -1) { break; }
		//	::CStringW strFid = strFidList.Mid(nIndex + 1);
		//	if (!strFid.IsEmpty())
		//	{
		//		::CStringW strData = CommGetData(_sGubun, "-1", strFid, 0, "");

		//		::CStringW strText;
		//		strText.Format("[%s] : %s", strFid.GetString(), strData.GetString());
		//		//m_listCtrl.AddString(strText);
		//	}
		//	strFidList.Delete(nIndex, strFidList.GetLength() - nIndex);
		//} while (true);
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
	}
#endif
}

// 키움 사용자 조건검색식 요청해서 받은거다.
void C_KH_OPEN_API::OnReceiveConditionVer(long _lRet, LPCWSTR _sMsg)	// 조건식을 문자열로 받음.
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//DBGPRINT(L"C_KH_OPEN_API::OnReceiveConditionVer");
	static dk::_PIPE_PACKET ipcConditionPacket{};
#if defined(_USE_EXCEPTION_KW_)
	try
	{	// 받은 그대로 
#endif
		
		//{
		//	_PKT_PIPE_KIWOOM_SUCCESS_CONDITIONS_
		//	, 0
		//	, { 0 }
		//};
		ZeroMemory(&ipcConditionPacket, sizeof(dk::_PIPE_PACKET));
		if (1 != _lRet)
		{	// 사용자 조건검색식 리스트를 얻어오지 못한 경우
			wchar_t szBuffer[(1 << 10)] = { 0 };
			::swprintf(szBuffer, L"ErrorCode: %d / Message: %s", _lRet, _sMsg);

			ipcConditionPacket.nDataIndex = _PKT_PIPE_KIWOOM_FAIL_CONDITIONS_;
			ipcConditionPacket.nDataSize = (WORD)::wcslen(szBuffer);
			// 오류 메시지를 버퍼에 복사하고
			::memcpy(ipcConditionPacket.bytBuffer, (LPVOID)szBuffer, ipcConditionPacket.nDataSize);	// 에러 메시지를 큐에 넣는다.
		}
		else
		{	// 조건식 리스트를 잘 얻어온 경우
			const ::CStringW& strConds = this->GetConditionNameList();

			WORD nCount = 0;
			for (int i = 0; i < strConds.GetLength(); ++i)
			{
				if (L'^' == strConds.GetAt(i))
				{
					++nCount;
				}
			}
			DBGPRINT(L"조건식의 개수: %d", nCount);

			ipcConditionPacket.nDataIndex = _PKT_PIPE_KIWOOM_SUCCESS_CONDITIONS_;
			ipcConditionPacket.nDataSize = (WORD)strConds.GetLength();
			// 조건식의 개수를 먼저 넣고, 그 다음에 조건식 문자열을 넣는다.
			*(LPWORD)ipcConditionPacket.bytBuffer = (WORD)nCount;	
			::memcpy(ipcConditionPacket.bytBuffer + sizeof(WORD), (LPVOID)strConds.GetString(), ipcConditionPacket.nDataSize);
		}
		if (0 < ipcConditionPacket.nDataSize)
		{
			DBGPRINT(L"[조건식] 보낸다: %d", ipcConditionPacket.nDataSize);
			this->pPipe->Send(&ipcConditionPacket);
		}
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
	}
#endif
}

// SendCondition 조건검색의 결과 첫 콜백인듯.
void C_KH_OPEN_API::OnReceiveTrCondition(
	LPCWSTR _화면번호			// 화면번호
	, LPCWSTR strCodeList		// 종목리스트(“;”로 구분), 조회된 종목리스트(ex:039490;005930;036570;…;)
	, LPCWSTR strConditionName	// 조회된 조건명
	, long nIndex				// 조회된 조건명 인덱스
	, long nNext				// 연속조회(2:연속조회, 0:연속조회없음), nNext 가 2로 들어오면 종목이 더 있는것
)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static dk::_PIPE_PACKET ipcTrConditionPacket{};

	DBGPRINT(L"OnReceiveTrCondition() - %s / %s / %s / %d", _화면번호, strCodeList, strConditionName, nIndex);
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		ZeroMemory(&ipcTrConditionPacket, sizeof(dk::_PIPE_PACKET));

		ipcTrConditionPacket.nDataIndex = _PKT_PIPE_KIWOOM_RECEIVED_CONDITIONS_;	// 조건검색 데이터 받음
		ipcTrConditionPacket.nDataSize = sizeof(_RECIVE_TR_CONDITION_DATA);

		_RECIVE_TR_CONDITION_DATA* pBuf = (_RECIVE_TR_CONDITION_DATA*)&ipcTrConditionPacket.bytBuffer[0];

		pBuf->nConditionIndex = nIndex;
		pBuf->nCountNextData = nNext;

		::wcscpy(pBuf->szScreenNumber, _화면번호);
		::wcscpy(pBuf->szConditionName, strConditionName);
		::wcscpy(pBuf->szCodeList, strCodeList);
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
	}
#endif
}

void C_KH_OPEN_API::OnReceiveRealCondition(
	LPCWSTR sTrCode
	, LPCWSTR strType
	, LPCWSTR strConditionName
	, LPCWSTR strConditionIndex
)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static dk::_PIPE_PACKET ipcRealCondition{};
	//DBGPRINT(L"OnReceiveRealCondition() - %s / %s / %s / %s", sTrCode, strType, strConditionName, strConditionIndex);
#if defined(_USE_EXCEPTION_KW_)
	try
	{
#endif
		ipcRealCondition.nDataIndex = _NET_MSG_KIWOOM_RECIVE_REALTIME_CONDITION_;	// 실시간 조건검색 데이터 받음
		ipcRealCondition.nDataSize = sizeof(_RECIVE_REALTIME_CONDITION_DATA);

		_RECIVE_REALTIME_CONDITION_DATA* pBuf = (_RECIVE_REALTIME_CONDITION_DATA*)&ipcRealCondition.bytBuffer[0];

		//DBGPRINT(L"OnReceiveRealCondition() %s / %s / %s / %s"), sTrCode, strType, strConditionName, strConditionIndex);

		pBuf->bInput = ('I' == strType[0]);		// 편입 "I", 이탈 "D", 0x49, 0x44
		pBuf->nConditionIndex = ::_wtoi(strConditionIndex);
		::wcscpy(pBuf->szStockCode, sTrCode);
		::wcscpy(pBuf->szConditionName, strConditionName);
#if defined(_USE_EXCEPTION_KW_)
	}
	catch (...)
	{	// 큐에 넣지 못했는데 메모리가 터졌다면 
		DBGPRINT(L"%s - Unexpected exception line: %i", __FUNCTIONW__, __LINE__);
	}
#endif
}
