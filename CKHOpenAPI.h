/*
 * MIT License
 * Copyright (c) 2025 dwerasd
 *
 * 사용된 라이브러리:
 * - ConcurrentQueue (Cameron Desrochers)
 *   라이센스 선택: Boost Software License 1.0
 *   원본 파일: readerwriterqueue.h
 *   원본 파일: blockingconcurrentqueue.h
*/
#pragma once


#include <unordered_map>

#include <DarkCore/DMemory.h>
#include <DarkCore/DLocale.h>
#include <DarkCore/DTimer.h>
#include <DarkCore/DThread.h>
#include <DarkCore/DUtil.h>
#include <DarkCore/DPipe.h>

#include <DOpenSources/csv.h>
#include <DOpenSources/readerwriterqueue.h>
#include <DOpenSources/blockingconcurrentqueue.h>

#include <Defines/ConfigDef.h>
#include <Defines/NetworkDef.h>
#include <Defines/StockDef.h>

#include <DataHelper/StructKW.h>

#include "KHOpenAPIDef.h"

#include "CKHOpenAPIHelper.h"


#define _USE_EXCEPTION_KW_

enum
{
	_REALDATA_주식체결_ = 0
	, _REALDATA_주식호가잔량_
	, _REALDATA_종목프로그램매매_
	, _REALDATA_주식당일거래원_
	, _REALDATA_선물시세_
	, _REALDATA_선물호가잔량_
	, _REALDATA_옵션시세_
	, _REALDATA_옵션호가잔량_
	, _REALDATA_업종지수_
	, _REALDATA_업종등락_
	, _REALDATA_VI발동해제_
	, _REALDATA_선물이론가_
	, _REALDATA_옵션이론가_
	, _REALDATA_ETF_NAV_
	, _REALDATA_ELW지표_
	, _REALDATA_ELW이론가_
	, _REALDATA_장시작시간_
	, _MAX_REALDATA_TYPES_
};

class C_KH_OPEN_API
	: public CWnd
	, dk::C_PIPE_RECEIVER
	, public dk::C_THREAD
{
private:
	bool bRequestChe{ true };
	bool bRequestHoga{ true };
	bool bRequestFutureChe{ true };
	bool bRequestFutureHoga{ true };
	bool bRequestOptionChe{ true };
	bool bRequestOptionHoga{ true };
	bool bRequestUpjongJisu{ true };
	bool bRequestUpViAlram{ true };

	BOOL bResult{ FALSE };
	long nResult{ 0 };
	CStringW strResult;
	COleVariant oleResult;

	long nRealDataSequence{ 0 };
	ULONG nDateToday{ 0 };
	wchar_t szDateToday[32] = { 0 };

	dk::_DLOCAL_TIME lt;

	//std::vector<WORD> vRealRegListA;
	std::vector<long> vRealFidListB;	// 주식체결
	//std::vector<WORD> vRealRegListC;
	std::vector<long> vRealFidListD;	// 주식호가 잔량

	dk::C_PIPE_CONNECTOR* pPipe{ nullptr };
	dk::_PIPE_PACKET currentPacket;

	DWORD ThreadFunc(LPVOID _pParam);

	WORD nRemainScreenCount{ kw::_MAX_SCREEN_COUNT_ };
	std::vector<kw::C_KIWOOM_SCREEN> vKiwoomScreens;

	kw::C_KIWOOM_SCREEN* get_screen_number(bool _bSetRealReg = false);
	kw::C_KIWOOM_SCREEN* get_screen(LPCWSTR _pScreenNo);
	void release_screen(LPCWSTR _pScreenNo);

	std::vector<std::wstring> vFilteredCodes;
	std::vector<std::wstring> vUpjongCodes;

	//void split_to_vec(std::vector<std::wstring>& _v, LPWSTR _str, wchar_t _c = L';');
	void split_to_vec(std::vector<std::wstring>& _v, ::CStringW _str, LPCWSTR _c = L";");
	void split_to_vec(std::vector<::CStringW>& _v, ::CStringW _str, LPCWSTR _c = L";");
	//void split_to_vec(std::vector<std::wstring>& _v, std::wstring& _str, wchar_t _c = L';');

	WORD set_real_reg(std::vector<std::wstring>& _v, const std::wstring& _strFields, const std::wstring& _strOptType = L"0");

	std::vector<::CStringW> vOptionCodes;
	std::vector<::CStringW> vFutureCodes;

	std::vector<::CStringW> vEtfCodes;
	std::vector<::CStringW> vElwCodes;

	
	WORD set_real_reg(std::vector<::CStringW>& _v, ::CStringW _strFields, ::CStringW _strOptType = L"0");

	WORD request_realdata_stock(bool _bChe = true, bool _bHoga = false);
	WORD request_realdata_option();

	bool m_bFieldChecked[_MAX_REALDATA_TYPES_] = { false, };	// 실시간 데이터 필드 확인 완료 여부
	bool m_bMatchedFields[_MAX_REALDATA_TYPES_] = { false, };	// 실시간 데이터 필드 순서 일치 여부

	// 주식체결
	bool ValidateField(_RAW_실시간_주식체결* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_주식호가잔량* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_종목프로그램매매* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_주식당일거래원* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_VI발동해제* pBuf, LPCWSTR _pRealData); 
	bool ValidateField(_RAW_실시간_업종지수* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_업종등락* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_선물시세* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_선물호가잔량* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_옵션시세* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_옵션호가잔량* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_선물이론가* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_옵션이론가* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_ETF_NAV* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_ELW_지표* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_ELW_이론가* pBuf, LPCWSTR _pRealData);
	bool ValidateField(_RAW_실시간_장시작시간* pBuf, LPCWSTR _pRealData);

	inline void FillHeader(_실시간_패킷_헤더* pBuf)
	{
		pBuf->nSequence = this->nRealDataSequence++;

		this->lt.refresh();
		pBuf->nTimeStamp = dk::get_ms(&this->lt);
		pBuf->nTickCount = ::GetTickCount64();
	}
	void FillRealData(_RAW_실시간_주식체결* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_주식호가잔량* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_종목프로그램매매* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_주식당일거래원* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_VI발동해제* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_업종지수* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_업종등락* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_선물시세* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_선물호가잔량* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_옵션시세* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_옵션호가잔량* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_선물이론가* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_옵션이론가* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_ETF_NAV* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_ELW_지표* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_ELW_이론가* pBuf, LPCWSTR _sRealKey);
	void FillRealData(_RAW_실시간_장시작시간* pBuf, LPCWSTR _sRealKey);

	void SplitRealData(_RAW_실시간_주식체결* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_주식호가잔량* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_종목프로그램매매* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_주식당일거래원* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_VI발동해제* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_업종지수* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_업종등락* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_선물시세* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_선물호가잔량* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_옵션시세* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_옵션호가잔량* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_선물이론가* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_옵션이론가* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_ETF_NAV* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_ELW_지표* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_ELW_이론가* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void SplitRealData(_RAW_실시간_장시작시간* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
		
	void CombineRealData(_RAW_실시간_주식체결* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_주식호가잔량* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_종목프로그램매매* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_주식당일거래원* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_VI발동해제* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_업종지수* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_업종등락* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_선물시세* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_선물호가잔량* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_옵션시세* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_옵션호가잔량* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_선물이론가* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_옵션이론가* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_ETF_NAV* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_ELW_지표* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_ELW_이론가* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);
	void CombineRealData(_RAW_실시간_장시작시간* pBuf, LPCWSTR _sRealKey, LPCWSTR _sRealData);

	dk::WCHART<32> szUserid{};
	dk::WCHART<20> szDefaultAccno{};
	void set_login_packet(dk::_PIPE_PACKET& _pPacket);

	bool filtered_codes(LPCWSTR _pCode, LPCWSTR _pName, LPCWSTR _pState, LPCWSTR _pGamri);
	inline bool filtered_codes(std::wstring_view _pCode, std::wstring_view _pName, std::wstring_view _pState, std::wstring_view _pGamri)
	{
		return this->filtered_codes(_pCode.data(), _pName.data(), _pState.data(), _pGamri.data());
	}

protected:
	DECLARE_DYNCREATE(C_KH_OPEN_API)

public:
	void init();
	void Destroy();

	moodycamel::BlockingConcurrentQueue<dk::_PIPE_PACKET*> bqPackets;
	void PushPacket(dk::_PIPE_PACKET* _pPacket);

	CLSID const& GetClsid();
	virtual BOOL Create(LPCWSTR lpszClassName, LPCWSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* _pContext = nullptr);

	BOOL Create(LPCWSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE, BSTR bstrLicKey = nullptr);

public:
	long CommConnect();
	void CommTerminate();
	
	long CommRqData(LPCWSTR sRQName, LPCWSTR sTrCode, long nPrevNext, LPCWSTR sScreenNo);
	::CStringW& GetLoginInfo(LPCWSTR sTag);
	long SendOrder(LPCWSTR sRQName, LPCWSTR sScreenNo, LPCWSTR sAccNo, long nOrderType, LPCWSTR sCode, long nQty, long nPrice, LPCWSTR sHogaGb, LPCWSTR sOrgOrderNo);
	// 이전 샘플에서 추출
	long SendOrderFO(LPCWSTR sScreenNo, LPCWSTR sAccNo, LPCWSTR sPw, LPCWSTR sCode, long nOrderType, long nOrderCount, long nOrderPrice, LPCWSTR sOrderDTCD, long nCndtDTCD, LPCWSTR sOrgOrderNo);
	// 최근 샘플 함수
	long SendOrderFO(LPCWSTR sRQName, LPCWSTR sScreenNo, LPCWSTR sAccNo, LPCWSTR sCode, long lOrdKind, LPCWSTR sSlbyTp, LPCWSTR sOrdTp, long lQty, LPCWSTR sPrice, LPCWSTR sOrgOrdNo);
	void SetInputValue(LPCWSTR sID, LPCWSTR sValue);
	long SetOutputFID(LPCWSTR sID);
	::CStringW& CommGetData(LPCWSTR sJongmokCode, LPCWSTR sRealType, LPCWSTR sFieldName, long nIndex, LPCWSTR sInnerFieldName);
	void DisconnectRealData(LPCWSTR sScnNo);
	long GetRepeatCnt(LPCWSTR sTrCode, LPCWSTR sRecordName);
	long CommKwRqData(LPCWSTR sArrCode, long bNext, long nCodeCount, long nTypeFlag, LPCWSTR sRQName, LPCWSTR sScreenNo);
	::CStringW& GetAPIModulePath();
	::CStringW& GetCodeListByMarket(LPCWSTR sMarket);
	long GetConnectState();
	LPCWSTR GetMasterCodeName(LPCWSTR sTrCode);
	inline LPCWSTR GetMasterCodeName(std::wstring_view sTrCode) { return this->GetMasterCodeName(sTrCode.data()); }
	long GetMasterListedStockCnt(LPCWSTR sTrCode);
	inline long GetMasterListedStockCnt(std::wstring_view sTrCode) { return this->GetMasterListedStockCnt(sTrCode.data()); }
	LPCWSTR GetMasterConstruction(LPCWSTR sTrCode);
	inline LPCWSTR GetMasterConstruction(std::wstring_view sTrCode) { return this->GetMasterConstruction(sTrCode.data()); }
	::CStringW& GetMasterListedStockDate(LPCWSTR sTrCode);
	long GetMasterLastPrice(LPCWSTR sTrCode);
	inline long GetMasterLastPrice(std::wstring_view sTrCode) { return this->GetMasterLastPrice(sTrCode.data()); }
	LPCWSTR GetMasterStockState(LPCWSTR sTrCode);
	inline LPCWSTR GetMasterStockState(std::wstring_view sTrCode) { return this->GetMasterStockState(sTrCode.data()); }
	long GetDataCount(LPCWSTR strRecordName);
	::CStringW& GetOutputValue(LPCWSTR strRecordName, long nRepeatIdx, long nItemIdx);
	::CStringW& GetCommData(LPCWSTR strTrCode, LPCWSTR strRecordName, long nIndex, LPCWSTR strItemName);
	::CStringW& GetCommRealData(LPCWSTR sTrCode, long nFid);
	::CStringW& GetChejanData(long nFid);
	// 이 아래는 새로 추가된 함수들이다.
	::CStringW& GetThemeGroupList(long nType);
	::CStringW& GetThemeGroupCode(LPCWSTR strThemeCode);
	::CStringW& GetFutureList();
	::CStringW& GetFutureCodeByIndex(long nIndex);
	::CStringW& GetActPriceList();
	::CStringW& GetMonthList();
	::CStringW& GetOptionCode(LPCWSTR strActPrice, long nCp, LPCWSTR strMonth);
	::CStringW& GetOptionCodeByMonth(LPCWSTR sTrCode, long nCp, LPCWSTR strMonth);
	::CStringW& GetOptionCodeByActPrice(LPCWSTR sTrCode, long nCp, long nTick);
	::CStringW& GetSFutureList(LPCWSTR strBaseAssetCode);
	::CStringW& GetSFutureCodeByIndex(LPCWSTR strBaseAssetCode, long nIndex);
	::CStringW& GetSActPriceList(LPCWSTR strBaseAssetGb);
	::CStringW& GetSMonthList(LPCWSTR strBaseAssetGb);
	::CStringW& GetSOptionCode(LPCWSTR strBaseAssetGb, LPCWSTR strActPrice, long nCp, LPCWSTR strMonth);
	::CStringW& GetSOptionCodeByMonth(LPCWSTR strBaseAssetGb, LPCWSTR sTrCode, long nCp, LPCWSTR strMonth);
	::CStringW& GetSOptionCodeByActPrice(LPCWSTR strBaseAssetGb, LPCWSTR sTrCode, long nCp, long nTick);
	::CStringW& GetSFOBasisAssetList();
	::CStringW& GetOptionATM();
	::CStringW& GetSOptionATM(LPCWSTR strBaseAssetGb);
	::CStringW& GetBranchCodeName();
	long CommInvestRqData(LPCWSTR sMarketGb, LPCWSTR sRQName, LPCWSTR sScreenNo);
	long SendOrderCredit(LPCWSTR sRQName, LPCWSTR sScreenNo, LPCWSTR sAccNo, long nOrderType, LPCWSTR sCode, long nQty, long nPrice, LPCWSTR sHogaGb, LPCWSTR sCreditGb, LPCWSTR sLoanDate, LPCWSTR sOrgOrderNo);
	::CStringW& KOA_Functions(LPCWSTR sFunctionName, LPCWSTR sParam);
	inline ::CStringW& KOA_Functions(std::wstring_view sFunctionName, std::wstring_view sParam)
	{
		return this->KOA_Functions(sFunctionName.data(), sParam.data());
	}
	inline ::CStringW& GetServerGubun()
	{
		return this->KOA_Functions(L"GetServerGubun", L"");
	}
	inline int GetStockMarketKind(LPCWSTR sCode)
	{
		return ::_wtoi(this->KOA_Functions(L"GetStockMarketKind", sCode).GetString());
	}
	inline int GetStockMarketKind(std::wstring_view sCode)
	{
		return ::_wtoi(this->KOA_Functions(L"GetStockMarketKind", sCode.data()).GetString());
	}
	inline ::CStringW& GetUpjongCode()
	{
		return this->KOA_Functions(L"GetUpjongCode", L"");
	}
	long SetInfoData(LPCWSTR sInfoData);
	long SetRealReg(LPCWSTR strScreenNo, LPCWSTR strCodeList, LPCWSTR strFidList, LPCWSTR strOptType);
	long GetConditionLoad();
	::CStringW& GetConditionNameList();
	BOOL SendCondition(LPCWSTR strScrNo, LPCWSTR strConditionName, int nIndex, int nSearch);
	void SendConditionStop(LPCWSTR strScrNo, LPCWSTR strConditionName, int nIndex);
	COleVariant GetCommDataEx(LPCWSTR strTrCode, LPCWSTR strRecordName);
	void SetRealRemove(LPCWSTR strScrNo, LPCWSTR strDelCode);
	long GetMarketType(LPCWSTR strCode);

	DECLARE_EVENTSINK_MAP()
	void OnEventConnect(long _nErrCode);
	void OnReceiveMsg(LPCWSTR sScrNo, LPCWSTR sRQName, LPCWSTR sTrCode, LPCWSTR sMsg);
	void OnReceiveTrData(LPCWSTR _화면번호, LPCWSTR sRQName, LPCWSTR sTrCode, LPCWSTR sRecordName, LPCWSTR sPrevNext, long nDataLength, LPCWSTR sErrorCode, LPCWSTR sMessage, LPCWSTR sSplmMsg);
	void OnReceiveRealData(LPCWSTR sRealKey, LPCWSTR sRealType, LPCWSTR sRealData);
	void OnReceiveChejanData(LPCWSTR sGubun, long nItemCnt, LPCWSTR sFIdList);
	void OnReceiveConditionVer(long lRet, LPCWSTR sMsg);
	void OnReceiveTrCondition(LPCWSTR _화면번호, LPCWSTR strCodeList, LPCWSTR strConditionName, long nIndex, long nNext);
	void OnReceiveRealCondition(LPCWSTR sTrCode, LPCWSTR strType, LPCWSTR strConditionName, LPCWSTR strConditionIndex);
};
