// KHOpenAPI.cpp  : Microsoft Visual C++로 만든 ActiveX 컨트롤 래퍼 클래스의 정의입니다.


#include "pch.h"
#include "CKHOpenAPI.h"
#include "resource.h"
#include "BrokerKW.h"
#include "BrokerKWDlg.h"



CLSID const& C_KH_OPEN_API::GetClsid()
{
	static CLSID const clsid = { 0xA1574A0D, 0x6BFA, 0x4BD7, { 0x90, 0x20, 0xDE, 0xD8, 0x87, 0x11, 0x81, 0x8D } };
	return clsid;
}

BOOL C_KH_OPEN_API::Create(LPCWSTR lpszClassName, LPCWSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* _pContext)
{
	lpszClassName;
	_pContext;
	return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
}

BOOL C_KH_OPEN_API::Create(LPCWSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CFile* pPersist, BOOL bStorage, BSTR bstrLicKey)
{
	return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID, pPersist, bStorage, bstrLicKey);
}

long C_KH_OPEN_API::CommConnect()
{
	this->nResult = 0;
	this->InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, NULL);
	return(this->nResult);
}
void C_KH_OPEN_API::CommTerminate()
{
	this->InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
long C_KH_OPEN_API::CommRqData(LPCWSTR sRQName, LPCWSTR sTrCode, long nPrevNext, LPCWSTR sScreenNo)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sRQName, sTrCode, nPrevNext, sScreenNo);
	return(this->nResult);
}
::CStringW& C_KH_OPEN_API::GetLoginInfo(LPCWSTR sTag)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTag);
	return(this->strResult);
}
long C_KH_OPEN_API::SendOrder(LPCWSTR sRQName, LPCWSTR sScreenNo, LPCWSTR sAccNo, long nOrderType, LPCWSTR sCode, long nQty, long nPrice, LPCWSTR sHogaGb, LPCWSTR sOrgOrderNo)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sRQName, sScreenNo, sAccNo, nOrderType, sCode, nQty, nPrice, sHogaGb, sOrgOrderNo);
	return(this->nResult);
}
// 이전 샘플에서 추출
long C_KH_OPEN_API::SendOrderFO(LPCWSTR sScreenNo, LPCWSTR sAccNo, LPCWSTR sPw, LPCWSTR sCode, long nOrderType, long nOrderCount, long nOrderPrice, LPCWSTR sOrderDTCD, long nCndtDTCD, LPCWSTR sOrgOrderNo)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sScreenNo, sAccNo, sPw, sCode, nOrderType, nOrderCount, nOrderPrice, sOrderDTCD, nCndtDTCD, sOrgOrderNo);
	return(this->nResult);
}
// 최근 샘플 함수
long C_KH_OPEN_API::SendOrderFO(LPCWSTR sRQName, LPCWSTR sScreenNo, LPCWSTR sAccNo, LPCWSTR sCode, long lOrdKind, LPCWSTR sSlbyTp, LPCWSTR sOrdTp, long lQty, LPCWSTR sPrice, LPCWSTR sOrgOrdNo)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sRQName, sScreenNo, sAccNo, sCode, lOrdKind, sSlbyTp, sOrdTp, lQty, sPrice, sOrgOrdNo);
	return(this->nResult);
}
void C_KH_OPEN_API::SetInputValue(LPCWSTR sID, LPCWSTR sValue)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR;
	this->InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sID, sValue);
}
long C_KH_OPEN_API::SetOutputFID(LPCWSTR sID)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sID);
	return(this->nResult);
}
::CStringW& C_KH_OPEN_API::CommGetData(LPCWSTR sJongmokCode, LPCWSTR sRealType, LPCWSTR sFieldName, long nIndex, LPCWSTR sInnerFieldName)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sJongmokCode, sRealType, sFieldName, nIndex, sInnerFieldName);
	return(this->strResult);
}
void C_KH_OPEN_API::DisconnectRealData(LPCWSTR sScnNo)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sScnNo);
}
long C_KH_OPEN_API::GetRepeatCnt(LPCWSTR sTrCode, LPCWSTR sRecordName)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sTrCode, sRecordName);
	return(this->nResult);
}
long C_KH_OPEN_API::CommKwRqData(LPCWSTR sArrCode, long bNext, long nCodeCount, long nTypeFlag, LPCWSTR sRQName, LPCWSTR sScreenNo)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sArrCode, bNext, nCodeCount, nTypeFlag, sRQName, sScreenNo);
	return(this->nResult);
}
::CStringW& C_KH_OPEN_API::GetAPIModulePath()
{
	this->strResult.Empty();
	this->InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, NULL);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetCodeListByMarket(LPCWSTR sMarket)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sMarket);
	return(this->strResult);
}
long C_KH_OPEN_API::GetConnectState()
{
	this->nResult = 0;
	this->InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, NULL);
	return(this->nResult);
}
LPCWSTR C_KH_OPEN_API::GetMasterCodeName(LPCWSTR sTrCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTrCode);
	return(this->strResult.GetString());
}
long C_KH_OPEN_API::GetMasterListedStockCnt(LPCWSTR sTrCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sTrCode);
	return(this->nResult);
}
LPCWSTR C_KH_OPEN_API::GetMasterConstruction(LPCWSTR sTrCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x12, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTrCode);
	return(this->strResult.GetString());
}

::CStringW& C_KH_OPEN_API::GetMasterListedStockDate(LPCWSTR sTrCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTrCode);
	return(this->strResult);
}
long C_KH_OPEN_API::GetMasterLastPrice(LPCWSTR sTrCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x14, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTrCode);
	this->nResult = ::_wtoi(this->strResult.GetString());
	return(this->nResult);
}
LPCWSTR C_KH_OPEN_API::GetMasterStockState(LPCWSTR sTrCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTrCode);
	return(this->strResult.GetString());
}

long C_KH_OPEN_API::GetDataCount(LPCWSTR strRecordName)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, strRecordName);
	return(this->nResult);
}

::CStringW& C_KH_OPEN_API::GetOutputValue(LPCWSTR strRecordName, long nRepeatIdx, long nItemIdx)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4;
	this->strResult.Empty();
	this->InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strRecordName, nRepeatIdx, nItemIdx);
	return(this->strResult);
}

::CStringW& C_KH_OPEN_API::GetCommData(LPCWSTR strTrCode, LPCWSTR strRecordName, long nIndex, LPCWSTR strItemName)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x18, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strTrCode, strRecordName, nIndex, strItemName);
	return(this->strResult);
}

::CStringW& C_KH_OPEN_API::GetCommRealData(LPCWSTR sTrCode, long nFid)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_I4;
	this->strResult.Empty();
	this->InvokeHelper(0x19, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTrCode, nFid);
	return(this->strResult);
}

::CStringW& C_KH_OPEN_API::GetChejanData(long nFid)
{
	constexpr BYTE parms[] = VTS_I4;
	this->strResult.Empty();
	this->InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, nFid);
	return(this->strResult);
}
// 이 아래는 새로 추가된 함수들이다.
::CStringW& C_KH_OPEN_API::GetThemeGroupList(long nType)
{
	constexpr BYTE parms[] = VTS_I4;
	this->strResult.Empty();
	this->InvokeHelper(0x1b, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, nType);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetThemeGroupCode(LPCWSTR strThemeCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strThemeCode);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetFutureList()
{
	this->strResult.Empty();
	this->InvokeHelper(0x1d, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, NULL);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetFutureCodeByIndex(long nIndex)
{
	constexpr BYTE parms[] = VTS_I4;
	this->strResult.Empty();
	this->InvokeHelper(0x1e, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, nIndex);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetActPriceList()
{
	this->strResult.Empty();
	this->InvokeHelper(0x1f, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, NULL);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetMonthList()
{
	this->strResult.Empty();
	this->InvokeHelper(0x20, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, NULL);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetOptionCode(LPCWSTR strActPrice, long nCp, LPCWSTR strMonth)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x21, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strActPrice, nCp, strMonth);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetOptionCodeByMonth(LPCWSTR sTrCode, long nCp, LPCWSTR strMonth)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x22, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTrCode, nCp, strMonth);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetOptionCodeByActPrice(LPCWSTR sTrCode, long nCp, long nTick)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4;
	this->strResult.Empty();
	this->InvokeHelper(0x23, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sTrCode, nCp, nTick);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSFutureList(LPCWSTR strBaseAssetCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x24, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strBaseAssetCode);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSFutureCodeByIndex(LPCWSTR strBaseAssetCode, long nIndex)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_I4;
	this->strResult.Empty();
	this->InvokeHelper(0x25, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strBaseAssetCode, nIndex);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSActPriceList(LPCWSTR strBaseAssetGb)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x26, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strBaseAssetGb);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSMonthList(LPCWSTR strBaseAssetGb)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x27, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strBaseAssetGb);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSOptionCode(LPCWSTR strBaseAssetGb, LPCWSTR strActPrice, long nCp, LPCWSTR strMonth)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strBaseAssetGb, strActPrice, nCp, strMonth);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSOptionCodeByMonth(LPCWSTR strBaseAssetGb, LPCWSTR sTrCode, long nCp, LPCWSTR strMonth)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x29, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strBaseAssetGb, sTrCode, nCp, strMonth);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSOptionCodeByActPrice(LPCWSTR strBaseAssetGb, LPCWSTR sTrCode, long nCp, long nTick)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4;
	this->strResult.Empty();
	this->InvokeHelper(0x2a, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strBaseAssetGb, sTrCode, nCp, nTick);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSFOBasisAssetList()
{
	this->strResult.Empty();
	this->InvokeHelper(0x2b, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, NULL);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetOptionATM()
{
	this->strResult.Empty();
	this->InvokeHelper(0x2c, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, NULL);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetSOptionATM(LPCWSTR strBaseAssetGb)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x2d, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, strBaseAssetGb);
	return(this->strResult);
}
::CStringW& C_KH_OPEN_API::GetBranchCodeName()
{
	this->strResult.Empty();
	this->InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, NULL);
	return(this->strResult);
}
long C_KH_OPEN_API::CommInvestRqData(LPCWSTR sMarketGb, LPCWSTR sRQName, LPCWSTR sScreenNo)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x2f, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sMarketGb, sRQName, sScreenNo);
	return(this->nResult);
}
long C_KH_OPEN_API::SendOrderCredit(LPCWSTR sRQName, LPCWSTR sScreenNo, LPCWSTR sAccNo, long nOrderType, LPCWSTR sCode, long nQty, long nPrice, LPCWSTR sHogaGb, LPCWSTR sCreditGb, LPCWSTR sLoanDate, LPCWSTR sOrgOrderNo)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sRQName, sScreenNo, sAccNo, nOrderType, sCode, nQty, nPrice, sHogaGb, sCreditGb, sLoanDate, sOrgOrderNo);
	return(this->nResult);
}
::CStringW& C_KH_OPEN_API::KOA_Functions(LPCWSTR sFunctionName, LPCWSTR sParam)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR;
	this->strResult.Empty();
	this->InvokeHelper(0x31, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, parms, sFunctionName, sParam);
	return(this->strResult);
}
long C_KH_OPEN_API::SetInfoData(LPCWSTR sInfoData)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, sInfoData);
	return(this->nResult);
}
long C_KH_OPEN_API::SetRealReg(LPCWSTR strScreenNo, LPCWSTR strCodeList, LPCWSTR strFidList, LPCWSTR strOptType)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, strScreenNo, strCodeList, strFidList, strOptType);
	return(this->nResult);
}
long C_KH_OPEN_API::GetConditionLoad()
{
	this->nResult = 0;
	this->InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, NULL);
	return(this->nResult);
}
::CStringW& C_KH_OPEN_API::GetConditionNameList()
{
	this->strResult.Empty();
	this->InvokeHelper(0x35, DISPATCH_METHOD, VT_BSTR, (void*)&this->strResult, NULL);
	return(this->strResult);
}
BOOL C_KH_OPEN_API::SendCondition(LPCWSTR strScrNo, LPCWSTR strConditionName, int nIndex, int nSearch)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I2 VTS_I2;
	this->bResult = FALSE;
	this->InvokeHelper(0x36, DISPATCH_METHOD, VT_BOOL, (void*)&this->bResult, parms, strScrNo, strConditionName, nIndex, nSearch);
	return(this->bResult);
}
void C_KH_OPEN_API::SendConditionStop(LPCWSTR strScrNo, LPCWSTR strConditionName, int nIndex)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I2;
	this->InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strScrNo, strConditionName, nIndex);
}
COleVariant C_KH_OPEN_API::GetCommDataEx(LPCWSTR strTrCode, LPCWSTR strRecordName)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR;
	this->oleResult.Clear();
	this->InvokeHelper(0x38, DISPATCH_METHOD, VT_VARIANT, (void*)&this->oleResult, parms, strTrCode, strRecordName);
	return(this->oleResult);
}
void C_KH_OPEN_API::SetRealRemove(LPCWSTR strScrNo, LPCWSTR strDelCode)
{
	constexpr BYTE parms[] = VTS_BSTR VTS_BSTR;
	this->InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strScrNo, strDelCode);
}
long C_KH_OPEN_API::GetMarketType(LPCWSTR strCode)
{
	constexpr BYTE parms[] = VTS_BSTR;
	this->nResult = 0;
	this->InvokeHelper(0x3a, DISPATCH_METHOD, VT_I4, (void*)&this->nResult, parms, strCode);
	return(this->nResult);
}
