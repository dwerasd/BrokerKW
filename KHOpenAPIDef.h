#pragma once


#include <mutex>
#include <atomic>
#include <unordered_map>

#include <DarkCore/DSingleton.h>
#include <DarkCore/DPrint.h>

#include <Defines/StockDef.h>
#include <Defines/NetworkDef.h>

#include <DataHelper/StructKW.h>


inline constexpr int _OP_ERR_NONE_ = 0; // 정상처리
inline constexpr int _OP_ERR_FAIL_ = -10; // 실패
inline constexpr int _OP_ERR_LOGIN_ = -100; // 사용자정보교환실패
inline constexpr int _OP_ERR_CONNECT_ = -101; // 서버접속실패
inline constexpr int _OP_ERR_VERSION_ = -102; // 버전처리실패
inline constexpr int _OP_ERR_FIREWALL_ = -103; // 개인방화벽실패
inline constexpr int _OP_ERR_MEMORY_ = -104; // 메모리보호실패
inline constexpr int _OP_ERR_INPUT_ = -105; // 함수입력값오류
inline constexpr int _OP_ERR_SOCKET_CLOSED_ = -106; // 통신연결종료

inline constexpr int _OP_ERR_SISE_OVERFLOW_ = -200; // "시세조회 과부하"
inline constexpr int _OP_ERR_RQ_STRUCT_FAIL_ = -201; // "REQUEST_INPUT_st Failed"
inline constexpr int _OP_ERR_RQ_STRING_FAIL_ = -202; // "요청 전문 작성 실패"
inline constexpr int _OP_ERR_NO_DATA_ = -203; // "데이터가 존재하지 않습니다."
inline constexpr int _OP_ERR_OVER_MAX_DATA_ = -204; // "한번에 조회 가능한 종목개수는 최대 100종목 입니다."
inline constexpr int _OP_ERR_DATA_RCV_FAIL_ = -205; // 데이터수신실패
inline constexpr int _OP_ERR_OVER_MAX_FID_ = -206; // 조회가능한FID수초과
inline constexpr int _OP_ERR_REAL_CANCEL_ = -207; // 실시간해제오류

inline constexpr int _OP_ERR_ORD_WRONG_INPUT_ = -300; // "입력값 오류"
inline constexpr int _OP_ERR_ORD_WRONG_ACCNO_ = -301; // "계좌비밀번호를 입력하십시오."
inline constexpr int _OP_ERR_OTHER_ACC_USE_ = -302; // "타인계좌는 사용할 수 없습니다."
inline constexpr int _OP_ERR_MIS_2BILL_EXC_ = -303; // "주문가격이 20억원을 초과합니다."
inline constexpr int _OP_ERR_MIS_5BILL_EXC_ = -304; // "주문가격이 50억원을 초과합니다."
inline constexpr int _OP_ERR_MIS_1PER_EXC_ = -305; // "주문수량이 총발행주수의 1%를 초과합니다."
inline constexpr int _OP_ERR_MIS_3PER_EXC_ = -306; // "주문수량은 총발행주수의 3%를 초과할 수 없습니다."
inline constexpr int _OP_ERR_SEND_FAIL_ = -307; // "주문전송실패"
inline constexpr int _OP_ERR_ORD_OVERFLOW_ = -308; // "주문전송 과부하"
inline constexpr int _OP_ERR_MIS_300CNT_EXC_ = -309; // 주문수량300계약초과
inline constexpr int _OP_ERR_MIS_500CNT_EXC_ = -310; // 주문수량500계약초과
inline constexpr int _OP_ERR_ORD_WRONG_ACCTINFO_ = -340; // 계좌정보없음
inline constexpr int _OP_ERR_ORD_SYMCODE_EMPTY_ = -500; // 종목코드없음

inline constexpr int _UM_SCRENN_CLOSE_ = 1000;

inline constexpr wchar_t _TR_OPT10001_[] = L"OPT10001";
inline constexpr wchar_t _TR_OPT10003_[] = L"OPT10003";
inline constexpr wchar_t _TR_OPT10004_[] = L"OPT10004";
inline constexpr wchar_t _TR_OPT10015_[] = L"OPT10015";
inline constexpr wchar_t _TR_OPT10027_[] = L"OPT10027";
inline constexpr wchar_t _TR_OPT10054_[] = L"OPT10054";
inline constexpr wchar_t _TR_OPT10080_[] = L"OPT10080";
inline constexpr wchar_t _TR_OPT10081_[] = L"OPT10081";
inline constexpr wchar_t _TR_OPT10085_[] = L"OPT10085";
inline constexpr wchar_t _TR_OPT10086_[] = L"OPT10086";

inline constexpr wchar_t _TR_OPW00001_[] = L"OPW00001";
inline constexpr wchar_t _TR_OPW00013_[] = L"OPW00013";
inline constexpr wchar_t _TR_OPW00018_[] = L"OPW00018";


namespace kw
{
	inline constexpr WORD _MAX_SCREEN_COUNT_ = 200;

	class C_KIWOOM_SCREEN
	{
	private:
		volatile long nLock{ 0 };							// 사용중인지 여부	

	public:
		C_KIWOOM_SCREEN() {}
		virtual ~C_KIWOOM_SCREEN() {}

		int nUseCount{ 0 };						// SetRealReg 는 한 화면당 100개가 최고.
		wchar_t szScrNum[(1 << 3)] = { 0 };

		void lock() { ::InterlockedExchange(&nLock, 1); }
		void unlock() { ::InterlockedExchange(&nLock, 0); }
		//bool is_locked() { return (0 != ::InterlockedCompareExchange(&nLock, 0, 0)); }
		bool is_locked() { return (0 != ::InterlockedOr(&nLock, 0)); }
	};
	// 스크린 구조체 정의
	struct _KIWOOM_SCREEN
	{
		std::atomic<int> nLock{ 0 };  // 사용 중인지 여부
		std::atomic<int> nUsedCount{ 0 };  // SetRealReg는 한 화면당 100개가 최고
		wchar_t szScrNum[8] = { 0 };

		void lock() { nLock.store(1, std::memory_order_release); }
		void unlock() { nLock.store(0, std::memory_order_release); }
		bool is_locked() const { return nLock.load(std::memory_order_acquire) != 0; }
	};

	typedef std::unordered_map<std::wstring, std::unique_ptr<_KIWOOM_SCREEN>> UMAP_KIWOOM_SCREENS;
	// 스크린 관리자 클래스 정의
	class C_SCREEN_MANAGER
		: public dk::C_SINGLETON<C_SCREEN_MANAGER>
	{
	private:
		std::atomic<WORD> nRemainScreenCount{ _MAX_SCREEN_COUNT_ };  // 화면 번호를 관리하는데 사용할 수 있는 화면 번호의 개수
		UMAP_KIWOOM_SCREENS umapKiwoomScreens;
		std::mutex mtx;

	public:
		C_SCREEN_MANAGER()
		{
			for (WORD i = 1; i < _MAX_SCREEN_COUNT_; ++i)
			{
				auto pScreen = std::make_unique<_KIWOOM_SCREEN>();
				::swprintf_s(pScreen->szScrNum, L"%04d", i);
				this->umapKiwoomScreens[pScreen->szScrNum] = std::move(pScreen);
			}
		}

		~C_SCREEN_MANAGER()
		{
			std::lock_guard<std::mutex> lock(mtx);
			this->umapKiwoomScreens.clear();
		}

		_KIWOOM_SCREEN* get_scr(bool _bSetRealReg = false)
		{
			if (!this->nRemainScreenCount) { return nullptr; }

			std::lock_guard<std::mutex> lock(mtx);
			for (auto& [key, pScreen] : this->umapKiwoomScreens)
			{
				if (!_bSetRealReg)
				{
					if (!pScreen->is_locked())
					{
						pScreen->lock();
						--this->nRemainScreenCount;
						return pScreen.get();
					}
				}
				else {
					if (100 > pScreen->nUsedCount.load(std::memory_order_acquire))
					{
						pScreen->nUsedCount.fetch_add(1, std::memory_order_relaxed);
						--this->nRemainScreenCount;
						return pScreen.get();
					}
					else {
						pScreen->lock();
					}
				}
			}
			return nullptr;
		}

		LPCWSTR get_scr_num(bool _bSetRealReg)
		{
			if (!this->nRemainScreenCount) { return nullptr; }

			auto pScreen = this->get_scr(_bSetRealReg);
			if (pScreen) { return pScreen->szScrNum; }
			return nullptr;
		}
		_KIWOOM_SCREEN* get_scr(LPCWSTR _pScreenNo)
		{
			if (!this->nRemainScreenCount) { return nullptr; }

			std::lock_guard<std::mutex> lock(mtx);
			auto it = this->umapKiwoomScreens.find(_pScreenNo);
			if (it != this->umapKiwoomScreens.end()) { return it->second.get(); }
			return nullptr;
		}
		void set_used_count(LPCWSTR _pScreenNo, WORD _nCount)
		{
			std::lock_guard<std::mutex> lock(mtx);
			auto it = this->umapKiwoomScreens.find(_pScreenNo);
			if (it != this->umapKiwoomScreens.end())
			{
				it->second->nUsedCount.store(_nCount, std::memory_order_relaxed);
				//this->nRemainScreenCount -= _nCount;
				this->nRemainScreenCount.fetch_sub(_nCount, std::memory_order_relaxed);
			}
		}
		void release(LPCWSTR _pScreenNo)
		{
			std::lock_guard<std::mutex> lock(mtx);
			auto it = this->umapKiwoomScreens.find(_pScreenNo);
			if (it != this->umapKiwoomScreens.end())
			{
				it->second->nUsedCount.store(0, std::memory_order_relaxed);
				it->second->unlock();
				++this->nRemainScreenCount;
			}
		}
		void release(_KIWOOM_SCREEN* _pScreen)
		{
			std::lock_guard<std::mutex> lock(mtx);
			_pScreen->nUsedCount.store(0, std::memory_order_relaxed);
			_pScreen->unlock();
			++this->nRemainScreenCount;
		}
	};

	//class C_KIWOOM_MANAGER
	//{
	//private:
	//	WORD nRemainScreenCount{ _MAX_SCREEN_COUNT_ };        // 화면번호를 관리하는데 사용할 수 있는 화면번호의 개수
	//	UMAP_KIWOOM_SCREENS umapKiwoomScreens;

	//public:
	//	C_KIWOOM_MANAGER()
	//	{
	//		for (WORD i = 1; i < _MAX_SCREEN_COUNT_; ++i)
	//		{   // 0000 은 사용하지 않는다.
	//			auto pScreen = std::make_unique<_KIWOOM_SCREEN>();	// std::make_unique 로 생성한 객체는 std::move 로 이동시켜야 한다.
	//			::swprintf_s(pScreen->szScrNum, L"%04d", i);
	//			this->umapKiwoomScreens[pScreen->szScrNum] = std::move(pScreen);
	//		}
	//	}
	//	~C_KIWOOM_MANAGER()
	//	{
	//		this->umapKiwoomScreens.clear();
	//	}

	//	_KIWOOM_SCREEN* get_screen(bool _bSetRealReg)
	//	{
	//		for (auto& [key, pScreen] : umapKiwoomScreens)
	//		{
	//			if (!_bSetRealReg)
	//			{   // 미체결 내역이 남아있는 화면은 사용할 수 없다.
	//				// 체결이 끝나면 release_screen 함수를 호출하여 화면을 해제한다.
	//				if (!pScreen->is_locked())
	//				{   // 락을 걸고 내보낸다.
	//					pScreen->lock();
	//					--nRemainScreenCount;        // 화면 사용 카운트를 감소시킨다.
	//					return pScreen.get();
	//				}
	//			}
	//			else
	//			{   // _bSetRealReg 가 true 라면 SetRealReg 함수용 화면번호이다.
	//				if (100 > pScreen->nUsedCount)
	//				{   // 실시간 요청은 화면당 100개까지 가능하다.
	//					--nRemainScreenCount;        // 화면 사용 카운트를 감소시킨다.
	//					return pScreen.get();
	//				}
	//				else
	//				{   // 만약 100개를 넘어가면 사용할 수 없게 락을 건다.
	//					pScreen->lock();
	//				}
	//			}
	//		}
	//		return nullptr;
	//	}
	//	LPCWSTR get_screen_number(bool _bSetRealReg)
	//	{
	//		auto pScreen = get_screen(_bSetRealReg);
	//		if (pScreen)
	//		{
	//			return pScreen->szScrNum;
	//		}
	//		return nullptr;
	//	}
	//	_KIWOOM_SCREEN* get_screen(LPCWSTR _pScreenNo)
	//	{
	//		auto it = umapKiwoomScreens.find(_pScreenNo);
	//		if (it != umapKiwoomScreens.end())
	//		{
	//			return it->second.get();
	//		}
	//		return nullptr;
	//	}

	//	void release_screen(LPCWSTR _pScreenNo)
	//	{
	//		auto it = umapKiwoomScreens.find(_pScreenNo);
	//		if (it != umapKiwoomScreens.end())
	//		{
	//			it->second->nUsedCount = 0;
	//			it->second->unlock();
	//			++nRemainScreenCount;        // 화면 사용 카운트를 증가시킨다.
	//		}
	//	}
	//};


	// 주문 관리자 클래스 정의
	struct _CONDITION_KIWOOM
	{
		int nConditionIndex{ 0 };
		std::wstring strConditionName;
	};

	inline constexpr double _KIWOOM_REAL_FEE_ = 0.00015;
	inline constexpr double _KIWOOM_MOCK_FRE_ = 0.0035;
	inline constexpr double _KIWOOM_TAX_ = 0.002;
	__inline double get_real_profit_kw(double& _실매도가, double& _수익금, double& _수익률, double _dbBuyBalance, double _dbSellBalance)
	{
		// 총 매수금액, 총 매도금액, 잔고, 총 수익금, 총 수익률
		// 매수 금액: %0.0f, 매도 금액: %0.0f, 수수료: %0.0f, 잔고: %0.0f, 수익: %0.0f (%0.2f%%)
		double gbfee = _dbBuyBalance * _KIWOOM_REAL_FEE_;
		double gsfee = _dbSellBalance * _KIWOOM_REAL_FEE_;
		double gtexs = _dbSellBalance * _KIWOOM_TAX_;
		double bfee = gbfee - ::fmod(gbfee, 10);
		double sfee = gsfee - ::fmod(gsfee, 10);
		double texs = gtexs - ::fmod(gtexs, 1);
		_실매도가 = ::fabs((double)(_dbSellBalance - texs - bfee - sfee));			// 키움 매도가
		_수익금 = (double)::round(_실매도가 - _dbBuyBalance);						// 키움 손익
		_수익률 = _수익금 / _dbBuyBalance * 100.0;									// 키움 수익률
		return (texs - bfee - sfee);												// 키움 수수료
	}
	__inline double get_mock_profit_kw(double& _실매도가, double& _수익금, double& _수익률, double _dbBuyBalance, double _dbSellBalance)
	{
		// 총 매수금액, 총 매도금액, 잔고, 총 수익금, 총 수익률
	// 매수 금액: %0.0f, 매도 금액: %0.0f, 수수료: %0.0f, 잔고: %0.0f, 수익: %0.0f (%0.2f%%)
		double gbfee = _dbBuyBalance * _KIWOOM_MOCK_FRE_;
		double gsfee = _dbSellBalance * _KIWOOM_MOCK_FRE_;
		double gtexs = _dbSellBalance * _KIWOOM_TAX_;
		double bfee = gbfee - ::fmod(gbfee, 10);
		double sfee = gsfee - ::fmod(gsfee, 10);
		double texs = gtexs - ::fmod(gtexs, 1);
		_실매도가 = ::fabs((double)(_dbSellBalance - texs - bfee - sfee));			// 키움 매도가
		_수익금 = (double)::round(_실매도가 - _dbBuyBalance);							// 키움 손익
		_수익률 = _수익금 / _dbBuyBalance * 100.0;									// 키움 수익률
		return (texs - bfee - sfee);												// 키움 수수료
	}

	//static double dbHoga[] = { 1000.0, 5000.0, 10000.0, 50000.0, 100000.0, 500000.0, 1000000.0 };
	//static double dbNewHoga[] = { 2000.0, 5000.0, 20000.0, 50000.0, 200000.0, 500000.0, 1000000.0 };
	//static double dbUnit[] = { 1.0, 5.0, 10.0, 50.0, 100.0, 500.0, 1000.0 };
	inline constexpr double dbHoga[] = { 1000.0, 5000.0, 10000.0, 50000.0, 100000.0, 500000.0, 1000000.0 };		// 호가 단위
	inline constexpr double dbNewHoga[] = { 2000.0, 5000.0, 20000.0, 50000.0, 200000.0, 500000.0, 1000000.0 };	// 새로운 호가 단위
	inline constexpr double dbUnit[] = { 1.0, 5.0, 10.0, 50.0, 100.0, 500.0, 1000.0 };
	inline double get_hoga_price(double _dbPrice, bool _bNew = true, int _nGap = 0)
	{
		const double* pHoga = _bNew ? dbNewHoga : dbHoga;
		int i = 0;
		while (_dbPrice >= pHoga[i] && 6 > i++);
		// 만약 호가 단위가 1 이라면 그대로 반환한다.
		double dbPrice = _dbPrice;
		if (0 < i) { dbPrice = ::round(_dbPrice / dbUnit[i]) * dbUnit[i]; }
		if (0 < _nGap)
		{
			// 만약 최저가가 1999 라면 2000이 1틱, 2005이 2틱, 2010가 3틱, 2015이 4틱 이어야 한다.
			// 우선 최저가가 1999 라면, 2000 이 1틱이니 이것부터 적용한다.
			//DBGPRINT(L"dbPrice1: %0.0f, dbHoga[%d]: %0.0f, (dbUnit[i] * _nGap): %0.0f, _nGap: %d", dbPrice, i, dbHoga[i], (dbUnit[i] * _nGap), _nGap);
			if (6 > i && (dbPrice + (dbUnit[i] * _nGap)) >= dbHoga[i])
			{
				double dbTemp = dbPrice;
				while (true)
				{
					if (!_nGap) { break; }
					dbTemp += dbUnit[i];
					--_nGap;		// 라운드피겨까지 틱을 소모하고
					if (dbTemp >= dbHoga[i]) { break; }
				}
				dbPrice = dbTemp;	// 라운드피겨 호가를 반영한다.
			}
			//DBGPRINT(L"dbPrice2: %0.0f, dbUnit[%d]: %0.0f, _nGap: %d", dbPrice, i, dbUnit[i], _nGap);
			// 이제 2000 위 틱을 적용한다.
			if (6 > i && dbPrice <= dbHoga[i + 1]) { dbPrice += (dbUnit[i + 1] * _nGap); }
			else dbPrice += (dbUnit[i] * _nGap);
		}
		else if (0 > _nGap)
		{   // 만약 최고가가 2005 라면, 2000이 -1틱, 1999가 -2틱, 1998이 -3틱, 1997이 -4틱 이어야 한다.
			// 우선 최고가가 2005 라면, 2000 이 1틱이니 이것부터 적용한다.
			if (0 < i && dbPrice - (dbUnit[i] * -_nGap) < dbHoga[i - 1])
			{
				double dbTemp = dbPrice;
				while (true)
				{
					if (!_nGap) { break; }
					dbTemp -= dbUnit[i];
					++_nGap;
					if (dbTemp <= dbHoga[i]) { break; }
				}
				dbPrice = dbTemp;
			}
			// 이제 2000 아래 틱을 적용한다.
			if (0 < i && dbPrice >= dbHoga[i - 1])  // 만약 dbPrice가 dbHoga[i-1]과 같다면, dbUnit[i-1]을 사용한다. (즉, 2000이면 1999로 내린다.)
			{
				dbPrice -= (dbUnit[i - 1] * -_nGap);
				//DBGPRINT(L"dbPrice: %0.0f, dbUnit[%d]: %0.0f, _nGap: %d", dbPrice, i - 1, dbUnit[i - 1], _nGap);
			}
			else dbPrice -= (dbUnit[i] * -_nGap);
		}
		return dbPrice;
	}
	static int trailing_stop_hoga = -4;
	inline bool trailing_stop(double currentPrice, double& highestPrice)
	{
		bool bResult = false;
		do
		{
			if (currentPrice > highestPrice)
			{	// 최고가를 갱신합니다.
				highestPrice = currentPrice;
				break; // 최고가 갱신 시 종료
			}
			// 고가에서 4호가 아래로 내려오면 매도 신호 발생
			double sellPriceThreshold = get_hoga_price(highestPrice, true, trailing_stop_hoga);
			if (currentPrice <= sellPriceThreshold) { bResult = true; }
		} while (false);
		return(bResult);
	}
	static int trailing_start_hoga = 4;
	inline bool trailing_start(double currentPrice, double& lowestPrice)
	{
		bool bResult = false;
		do
		{
			// 최저가를 갱신합니다.
			if (currentPrice < lowestPrice) { lowestPrice = currentPrice; break; }
			// 저가에서 4호가 위로 올라오면 매수 신호 발생
			double buyPriceThreshold = get_hoga_price(lowestPrice, true, trailing_start_hoga);
			DBGPRINT(L"currentPrice: %0.0f, lowestPrice: %0.0f, buyPriceThreshold: %0.0f", currentPrice, lowestPrice, buyPriceThreshold);
			if (currentPrice >= buyPriceThreshold) { bResult = true; }
		} while (false);
		return(bResult);
	}
}


//#define DT_NONE					0				// 기본문자 형식
//#define DT_DATE					1				// 일자 형식
//#define DT_TIME					2				// 시간 형식
//#define DT_NUMBER				3				// 콤파 숫자 형식
//#define DT_ZERO_NUMBER			4				// 콤파 숫자(0표시) 형식
//#define DT_SIGN					5				// 대비기호 형식

#if defined(_MFC_VER)
typedef struct
{
	::CStringW	strKey;				// 조회 키
	::CStringW	strRealKey;			// 리얼 키
	int			nRow;				// 그리드 행
	int			nCol;				// 그리드 열
	int			nDataType;			// 데이타 타입(0:기본문자, 1:일자, 2:시간, 3:콤파 숫자, 4:콤파 숫자(0표시), 5:대비기호)
	BOOL		bTextColor;			// 문자열 색 변경(상승, 하락색)
	UINT		nAlign;				// 문자열 정렬(DT_LEFT, DT_CENTER, DT_RIGHT)
	::CStringW	strBeforeData;		// 문자열 앞 문자 넣기
	::CStringW	strAfterData;		// 문자열 뒤 문자 넣기
} stGRID;
#endif



inline constexpr int _MAX_LIMIT_REQUEST_COUNT_PER_SECOND_ = 4;

// 일반 주문 SendOrder 와 신용 주문 SendOrderCredit 함수는 거래구분을 사용한다.
inline constexpr wchar_t _거래구분_지정가_[] = L"00";
inline constexpr wchar_t _거래구분_시장가_[] = L"03";
inline constexpr wchar_t _거래구분_조건부지정가_[] = L"05";
inline constexpr wchar_t _거래구분_최유리지정가_[] = L"06";
inline constexpr wchar_t _거래구분_최우선지정가_[] = L"07";
inline constexpr wchar_t _거래구분_지정가_IOC_[] = L"10";
inline constexpr wchar_t _거래구분_시장가_IOC_[] = L"13";
inline constexpr wchar_t _거래구분_최유리_IOC_[] = L"16";
inline constexpr wchar_t _거래구분_지정가_FOK_[] = L"20";
inline constexpr wchar_t _거래구분_시장가_FOK_[] = L"23";
inline constexpr wchar_t _거래구분_최유리_FOK_[] = L"26";
inline constexpr wchar_t _거래구분_장전시간외종가_[] = L"61";
inline constexpr wchar_t _거래구분_시간외단일가매매_[] = L"62";
inline constexpr wchar_t _거래구분_장후시간외종가_[] = L"81";

// 코스피지수200 선물옵션은 SendOrderFO 함수와 아래 거래구분을 사용한다.
inline constexpr wchar_t _거래구분_선물_지정가_[] = L"1";
inline constexpr wchar_t _거래구분_선물_조건부지정가_[] = L"2";
inline constexpr wchar_t _거래구분_선물_시장가_[] = L"3";
inline constexpr wchar_t _거래구분_선물_최유리지정가_[] = L"4";
inline constexpr wchar_t _거래구분_선물_지정가_IOC_[] = L"5";
inline constexpr wchar_t _거래구분_선물_지정가_FOK_[] = L"6";
inline constexpr wchar_t _거래구분_선물_시장가_IOC_[] = L"7";
inline constexpr wchar_t _거래구분_선물_시장가_FOK_[] = L"8";
inline constexpr wchar_t _거래구분_선물_최유리지정가_IOC_[] = L"9";
inline constexpr wchar_t _거래구분_선물_최유리지정가_FOK_[] = L"A";
inline constexpr wchar_t _거래구분_선물_장종료후시간외지정가_[] = L"1";

inline constexpr int _주식체결_체결시간_ = 20;
inline constexpr int _주식체결_현재가_ = 10;
inline constexpr int _주식체결_전일대비_ = 11;
inline constexpr int _주식체결_등락율_ = 12;
inline constexpr int _주식체결_최우선매도호가_ = 27;
inline constexpr int _주식체결_최우선매수호가_ = 28;
inline constexpr int _주식체결_거래량_ = 15;
inline constexpr int _주식체결_누적거래량_ = 13;
inline constexpr int _주식체결_누적거래대금_ = 14;
inline constexpr int _주식체결_시가_ = 16;
inline constexpr int _주식체결_고가_ = 17;
inline constexpr int _주식체결_저가_ = 18;
inline constexpr int _주식체결_전일대비기호_ = 25;
inline constexpr int _주식체결_전일거래량대비_계약주_ = 26;
inline constexpr int _주식체결_거래대금증감_ = 29;
inline constexpr int _주식체결_전일거래량대비_비율_ = 30;
inline constexpr int _주식체결_거래회전율_ = 31;
inline constexpr int _주식체결_거래비용_ = 32;
inline constexpr int _주식체결_체결강도_ = 228;
inline constexpr int _주식체결_시가총액_억_ = 311;
inline constexpr int _주식체결_장구분_ = 290;
inline constexpr int _주식체결_KO접근도_ = 691;
inline constexpr int _주식체결_상한가발생시간_ = 567;
inline constexpr int _주식체결_하한가발생시간_ = 568;
inline constexpr int _주식체결_전일동시간거래량비율_ = 851;	// (jj : 주식체결 전일거래량대비 비율)
inline constexpr int _주식체결_매도체결량_ = 1030;
inline constexpr int _주식체결_매수체결량_ = 1031;
inline constexpr int _주식체결_매수비율_ = 1032;
inline constexpr int _주식체결_거래소구분_ = 9081;

inline constexpr int _장시작시간_장운영구분_ = 215;
inline constexpr int _장시작시간_체결시간_ = 20;
inline constexpr int _장시작시간_장시작예상잔여시간_ = 214;

inline constexpr int _주문체결_계좌번호_ = 9201;
inline constexpr int _주문체결_주문번호_ = 9203;
inline constexpr int _주문체결_관리자사번_ = 9205;
inline constexpr int _주문체결_종목코드_ = 9001;
inline constexpr int _주문체결_주문업무분류_ = 912;	// (jj : 주식주문)
inline constexpr int _주문체결_주문상태_ = 913;		// (접수, 확인, 체결) (10 : 원주문, 11 : 정정주문, 12 : 취소주문, 20 : 주문확정, 21 : 정정확인, 22 : 취소확인, 90, 92 : 주문거부)
inline constexpr int _주문체결_종목명_ = 302;
inline constexpr int _주문체결_주문수량_ = 900;
inline constexpr int _주문체결_주문가격_ = 901;
inline constexpr int _주문체결_미체결수량_ = 902;
inline constexpr int _주문체결_체결누계금액_ = 903;
inline constexpr int _주문체결_원주문번호_ = 904;
inline constexpr int _주문체결_주문구분_ = 905;		// (+매수, -매도, -매도정정, +매수정정, 매수취소, 매도취소)
inline constexpr int _주문체결_매매구분_ = 906;		// (보통, 시장가등)
inline constexpr int _주문체결_매도수구분_ = 907;		// 매도(매도정정, 매도취소 포함)인 경우 1, 매수(매수정정, 매수취소 포함)인 경우 2
inline constexpr int _주문체결_주문체결시간_ = 908;	// (HHMMSS)
inline constexpr int _주문체결_체결번호_ = 909;
inline constexpr int _주문체결_체결가_ = 910;
inline constexpr int _주문체결_체결량_ = 911;
inline constexpr int _주문체결_현재가_ = 10;
inline constexpr int _주문체결_최우선매도호가_ = 27;
inline constexpr int _주문체결_최우선매수호가_ = 28;
inline constexpr int _주문체결_단위체결가_ = 914;
inline constexpr int _주문체결_단위체결량_ = 915;
inline constexpr int _주문체결_당일매매수수료_ = 938;
inline constexpr int _주문체결_당일매매세금_ = 939;
inline constexpr int _주문체결_거부사유_ = 919;
inline constexpr int _주문체결_화면번호_ = 920;
inline constexpr int _주문체결_터미널번호_ = 921;
inline constexpr int _주문체결_신용구분_ = 922;
inline constexpr int _주문체결_대출일_ = 923;

inline constexpr int _매도수구분_매도_ = 1;
inline constexpr int _매도수구분_매수_ = 2;

inline constexpr int _잔고_계좌번호_ = 9201;
inline constexpr int _잔고_종목코드_ = 9001;
inline constexpr int _잔고_종목명_ = 302;
inline constexpr int _잔고_현재가_ = 10;
inline constexpr int _잔고_보유수량_ = 930;
inline constexpr int _잔고_매입단가_ = 931;
inline constexpr int _잔고_총매입가_ = 932;
inline constexpr int _잔고_주문가능수량_ = 933;
inline constexpr int _잔고_당일순매수량_ = 945;
inline constexpr int _잔고_매도매수구분_ = 946;
inline constexpr int _잔고_당일총매도손익_ = 950;
inline constexpr int _잔고_예수금_ = 951;
inline constexpr int _잔고_최우선매도호가_ = 27;
inline constexpr int _잔고_최우선매수호가_ = 28;
inline constexpr int _잔고_기준가_ = 307;
inline constexpr int _잔고_손익율_ = 8019;

static wchar_t szOrdType[][32] =
{
	L"주문오류"
	, L"신규매수"
	, L"신규매도"
	, L"매수취소"
	, L"매도취소"
	, L"매수정정"
	, L"매도정정"
};

inline LPCWSTR get_ord_type(int _nType)
{
	if (0 < _nType && _nType < _countof(szOrdType))	// _countof(szOrdType) = 7
	{
		return szOrdType[_nType];
	}
	return szOrdType[0];
}

inline int get_ord_type(LPCWSTR _pType)
{
	for (int i = 1; i < _countof(szOrdType); ++i)
	{
		if (!::wcscmp(_pType, szOrdType[i]))
		{
			return i;
		}
	}
	return 0;
}

inline LPCWSTR get_tr_type(int _nType)
{
	switch (_nType)
	{
	case 0: return L"지정가";
	case 3: return L"시장가";
	case 5: return L"조건부지정가";
	case 6: return L"최유리지정가";
	case 7: return L"최우선지정가";
	case 10: return L"지정가IOC";
	case 13: return L"시장가IOC";
	case 16: return L"최유리IOC";
	case 20: return L"지정가FOK";
	case 23: return L"시장가FOK";
	case 26: return L"최유리FOK";
	case 61: return L"장전시간외종가";
	case 62: return L"시간외단일가매매";
	case 81: return L"장후시간외종가";
	}
	return L"오류";
}

inline LPCWSTR get_tr_type(LPCWSTR _sType)
{
	if (!::wcscmp(_sType, L"지정가")) { return _거래구분_지정가_; }
	else if (!::wcscmp(_sType, L"시장가")) { return _거래구분_시장가_; }
	else if (!::wcscmp(_sType, L"조건부지정가")) { return _거래구분_조건부지정가_; }
	else if (!::wcscmp(_sType, L"최유리지정가")) { return _거래구분_최유리지정가_; }
	else if (!::wcscmp(_sType, L"최우선지정가")) { return _거래구분_최우선지정가_; }
	else if (!::wcscmp(_sType, L"지정가IOC")) { return _거래구분_지정가_IOC_; }
	else if (!::wcscmp(_sType, L"시장가IOC")) { return _거래구분_시장가_IOC_; }
	else if (!::wcscmp(_sType, L"최유리IOC")) { return _거래구분_최유리_IOC_; }
	else if (!::wcscmp(_sType, L"지정가FOK")) { return _거래구분_지정가_FOK_; }
	else if (!::wcscmp(_sType, L"시장가FOK")) { return _거래구분_시장가_FOK_; }
	else if (!::wcscmp(_sType, L"최유리FOK")) { return _거래구분_최유리_FOK_; }
	else if (!::wcscmp(_sType, L"장전시간외종가")) { return _거래구분_장전시간외종가_; }
	else if (!::wcscmp(_sType, L"시간외단일가매매")) { return _거래구분_시간외단일가매매_; }
	else if (!::wcscmp(_sType, L"장후시간외종가")) { return _거래구분_장후시간외종가_; }
	return(0);
}


static wchar_t szResultType[][32] =
{
	L"결과오류"
	, L"매수"
	, L"매도"
	, L"매수정정"
	, L"매도정정"
	, L"매수취소"
	, L"매도취소"
};

inline LPCWSTR get_result_type(int _nType)
{
	if (0 < _nType && _nType < _countof(szResultType))
	{
		return szResultType[_nType];
	}
	return szResultType[0];
}

inline bool check_type(int _nOrdType, int _nResultType)
{
	if (1 == _nOrdType && 1 == _nResultType)	// 신규매수, 매수
	{
		return true;
	}
	else if (2 == _nOrdType && 2 == _nResultType)	// 신규매도, 매도
	{
		return true;
	}
	else if (3 == _nOrdType && 5 == _nResultType)	// 매수취소, 매수정정
	{
		return true;
	}
	else if (4 == _nOrdType && 6 == _nResultType)	// 매도취소, 매도정정
	{
		return true;
	}
	else if (5 == _nOrdType && 3 == _nResultType)	// 매수정정, 매수취소
	{
		return true;
	}
	else if (6 == _nOrdType && 4 == _nResultType)	// 매도정정, 매도취소
	{
		return true;
	}
	return false;
}

struct _ORDER_KW
{
	ULONGLONG nTime{ 0 };				// 주문시간

	int nType{ 0 };					// 주문유형 1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정
	int nOrdVolume{ 0 };				// 주문수량
	int nPrice{ 0 };					// 주문가격
	wchar_t szTrType[3] = { 0 };		// 00: 지정가, 03: 시장가, 05: 조건부지정가, 06: 최유리지정가, 07: 최우선지정가, 10: 지정가IOC, 13: 시장가IOC, 16: 최유리IOC, 20: 지정가FOK, 23: 시장가FOK, 26: 최유리FOK, 61: 장전시간외종가, 62: 시간외단일가매매, 81: 장후시간외종가
	wchar_t szScrNo[5] = { 0 };		// 화면번호
	wchar_t szCode[7] = { 0 };			// 종목코드
	wchar_t szAccno[20] = { 0 };	// 계좌번호
	wchar_t szOrdNo[20] = { 0 };		// 주문번호
	wchar_t szOrgOrdNo[20] = { 0 };		// 원주문번호
	wchar_t szRQName[32] = { 0 };		// 주문명

	int nStep{ 0 };					// 0: 주문전, 1: 주문후, 2: 접수, 확인됨, 체결완료시 오더를 삭제한다.
	int nUnsettledVolume{ 0 };			// 미체결수량
	int nVolume{ 0 };					// 체결수량
};

enum _STRUCT_TYPE_
{
	_STRUCT_TYPE_NONE_ = 0
	, _실시간_장시작시간_
	, _실시간_주식체결_
	, _실시간_주식호가잔량_
	, _실시간_선물시세_
	, _실시간_선물호가잔량_
	, _실시간_선물이론가_
	, _실시간_옵션시세_
	, _실시간_옵션호가잔량_
	, _실시간_옵션이론가_
	, _실시간_업종지수_
	, _실시간_업종등락_
	, _실시간_ETF_NAV_
	, _실시간_ELW_지표_
	, _실시간_ELW_이론가_
	, _실시간_VI발동해제_
	, _실시간_종목프로그램매매_
	, _실시간_주식당일거래원_
};

inline constexpr wchar_t 장시작시간[] = L"장시작시간";
inline constexpr wchar_t 주식체결[] = L"주식체결";
inline constexpr wchar_t 주식우선호가[] = L"주식우선호가";
inline constexpr wchar_t 주식호가잔량[] = L"주식호가잔량";
inline constexpr wchar_t 선물시세[] = L"선물시세";
inline constexpr wchar_t 선물호가잔량[] = L"선물호가잔량";
inline constexpr wchar_t 선물이론가[] = L"선물이론가";
inline constexpr wchar_t 옵션시세[] = L"옵션시세";
inline constexpr wchar_t 옵션호가잔량[] = L"옵션호가잔량";
inline constexpr wchar_t 옵션이론가[] = L"옵션이론가";
inline constexpr wchar_t 업종지수[] = L"업종지수";
inline constexpr wchar_t 업종등락[] = L"업종등락";
inline constexpr wchar_t ETF_NAV[] = L"ETF NAV";
inline constexpr wchar_t ELW_지표[] = L"ELW 지표";
inline constexpr wchar_t ELW_이론가[] = L"ELW 이론가";
inline constexpr wchar_t VI발동해제[] = L"VI발동/해제";
inline constexpr wchar_t 종목프로그램매매[] = L"종목프로그램매매";
inline constexpr wchar_t 주식당일거래원[] = L"주식당일거래원";

inline constexpr ULONGLONG N주식체결 = 0x0000ACB0CCB4C2DD;
inline constexpr ULONGLONG N주식호가잔량 = 0xC794AC00D638C2DD;
//inline constexpr ULONGLONG N주식우선호가 = 0xD638C120C6B0C2DD;
//inline constexpr ULONGLONG N주식예상체결 = 0xCCB4C0C1C608C2DD;
inline constexpr ULONGLONG N종목프로그램매매 = 0xADF8B85CD504BAA9;
inline constexpr ULONGLONG N주식당일거래원 = 0xAC70C77CB2F9C2DD;
inline constexpr ULONGLONG NVI발동해제 = 0x002FB3D9BC1C0049;
inline constexpr ULONGLONG N선물시세 = 0x0000C138C2DCBB3C;
inline constexpr ULONGLONG N선물호가잔량 = 0xC794AC00D638BB3C;
inline constexpr ULONGLONG N선물이론가 = 0xAC00B860C774BB3C;
inline constexpr ULONGLONG N옵션시세 = 0x0000C138C2DCC158;
inline constexpr ULONGLONG N옵션호가잔량 = 0xC794AC00D638C158;
inline constexpr ULONGLONG N옵션이론가 = 0xAC00B860C774C158;
inline constexpr ULONGLONG N업종지수 = 0x0000C218C9C0C885;
inline constexpr ULONGLONG N업종등락 = 0x0000B77DB4F1C885;
inline constexpr ULONGLONG NETF_NAV = 0x004E002000460054;
inline constexpr ULONGLONG NELW_지표 = 0xC9C000200057004C;
inline constexpr ULONGLONG NELW_이론가 = 0xC77400200057004C;
inline constexpr ULONGLONG N장시작시간 = 0xAC04C2DCC791C2DC;

inline constexpr wchar_t 매수W[] = L"매수";
inline constexpr wchar_t 매도W[] = L"매도";
inline constexpr wchar_t 매수정정W[] = L"매수정정";
inline constexpr wchar_t 매도정정W[] = L"매도정정";
inline constexpr wchar_t 매수취소W[] = L"매수취소";
inline constexpr wchar_t 매도취소W[] = L"매도취소";
inline constexpr wchar_t 접수W[] = L"접수";
inline constexpr wchar_t 확인W[] = L"확인";
inline constexpr wchar_t 체결W[] = L"체결";
inline constexpr wchar_t 거부W[] = L"거부";
inline constexpr wchar_t 접수거부W[] = L"접수거부";
inline constexpr wchar_t 확인거부W[] = L"확인거부";

inline constexpr ULONGLONG N매수 = 0x00000000c218b9e4;
inline constexpr ULONGLONG N매도 = 0x00000000b3c4b9e4;
inline constexpr ULONGLONG N매수정정 = 0xc815c815c218b9e4;
inline constexpr ULONGLONG N매도정정 = 0xc815c815b3c4b9e4;
inline constexpr ULONGLONG N매수취소 = 0xc18ccde8c218b9e4;
inline constexpr ULONGLONG N매도취소 = 0xc18ccde8b3c4b9e4;
inline constexpr ULONGLONG N접수 = 0x00000000c218c811;
inline constexpr ULONGLONG N확인 = 0x00000000c778d655;
inline constexpr ULONGLONG N체결 = 0x00000000acb0ccb4;
inline constexpr ULONGLONG N거부 = 0x00000000bd80ac70;
inline constexpr ULONGLONG N접수거부 = 0xbd80ac70c218c811;
inline constexpr ULONGLONG N확인거부 = 0xbd80ac70c778d655;

inline constexpr wchar_t 장시작[] = L"장시작";
inline constexpr wchar_t 주식체[] = L"주식체";
inline constexpr wchar_t 주식우[] = L"주식우";
inline constexpr wchar_t 주식호[] = L"주식호";
inline constexpr wchar_t 선물시[] = L"선물시";
inline constexpr wchar_t 선물호[] = L"선물호";
inline constexpr wchar_t 선물이[] = L"선물이";
inline constexpr wchar_t 옵션시[] = L"옵션시";
inline constexpr wchar_t 옵션호[] = L"옵션호";
inline constexpr wchar_t 옵션이[] = L"옵션이";
inline constexpr wchar_t 업종지[] = L"업종지";
inline constexpr wchar_t 업종등[] = L"업종등";
inline constexpr wchar_t ETF[] = L"ETF N";
inline constexpr wchar_t ELW지[] = L"ELW 지";
inline constexpr wchar_t ELW이[] = L"ELW 이";
inline constexpr wchar_t VI발[] = L"VI발";
inline constexpr wchar_t 종목프[] = L"종목프";
inline constexpr wchar_t 주식당[] = L"주식당";


inline constexpr wchar_t _KOA_NORMAL_BUY_KP_ORD_[] = L"KOA_NORMAL_BUY_KP_ORD";		// 코스피 종목 매수 주문
inline constexpr wchar_t _KOA_NORMAL_SELL_KP_ORD_[] = L"KOA_NORMAL_SELL_KP_ORD";		// 코스피 종목 매도 주문
inline constexpr wchar_t _KOA_NORMAL_KP_CANCEL_[] = L"KOA_NORMAL_KP_CANCEL";			// 코스피 종목 주문 취소 주문
inline constexpr wchar_t _KOA_NORMAL_KP_MODIFY_[] = L"KOA_NORMAL_KP_MODIFY";			// 코스피 종목 주문 변경 주문
inline constexpr wchar_t _KOA_NORMAL_BUY_KQ_ORD_[] = L"KOA_NORMAL_BUY_KQ_ORD";		// 코스닥 종목 매수 주문
inline constexpr wchar_t _KOA_NORMAL_SELL_KQ_ORD_[] = L"KOA_NORMAL_SELL_KQ_ORD";		// 코스닥 종목 매도 주문
inline constexpr wchar_t _KOA_NORMAL_KQ_CANCEL_[] = L"KOA_NORMAL_KQ_CANCEL";			// 코스닥 종목 주문 취소 주문
inline constexpr wchar_t _KOA_NORMAL_KQ_MODIFY_[] = L"KOA_NORMAL_KQ_MODIFY";			// 코스닥 종목 주문 변경 주문


#pragma pack(push, 1)
struct _CONV_실시간_주식체결
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };		// 091259
	BYTE 거래유형{ 0 };					// 1: 매수, 2: 매도, 3: 단일가매매
	int 현재가{ 0 };					// 18105
	int 전일대비{ 0 };					// -200  
	double 등락율{ 0 };					// -1.09
	int 최우선매도호가{ 0 };			// 18105
	int 최우선매수호가{ 0 };			// 18100
	int 거래량{ 0 };					// 1
	ULONG 누적거래량{ 0 };				// 1
	LONGLONG 누적거래대금{ 0 };			// 0
	int 시가{ 0 };						// 18105
	int 고가{ 0 };						// 18105
	int 저가{ 0 };						// 18105
	int 전일대비기호{ 0 };				// 5
	int 전일거래량대비_계약주{ 0 };	// -12610
	LONGLONG 거래대금증감{ 0 };			// -232859830
	double 전일거래량대비_비율{ 0 };		// -0.01
	double 거래회전율{ 0 };				// 0.00
	ULONG 거래비용{ 0 };				// 6
	double 체결강도{ 0 };				// 0.00
	LONGLONG 시가총액{ 0 };				// 91
	int 장구분{ 0 };					// 2
	double KO접근도{ 0 };				// 0
	wchar_t 상한가발생시간[7] = { 0 };	// 000000
	wchar_t 하한가발생시간[7] = { 0 };	// 000000
	LONGLONG 매수체결량{ 0 };			// 0
	LONGLONG 매도체결량{ 0 };			// 0
	double 매수비율{ 0 };				// 0.0
};

struct _CONV_실시간_주식호가잔량
	: public _실시간_패킷_헤더
{
	wchar_t 호가시간[7] = { 0 };		// 091259
	ULONG 누적거래량{ 0 };			// 1
	int 매도호가[10] = { 0 };
	ULONG 매도호가수량[10] = { 0 };
	int 매도호가직전대비[10] = { 0 };
	ULONG LP매도호가수량[10] = { 0 };

	int 매수호가[10] = { 0 };
	ULONG 매수호가수량[10] = { 0 };
	int 매수호가직전대비[10] = { 0 };
	ULONG LP매수호가수량[10] = { 0 };

	ULONG 매도호가총잔량{ 0 };
	ULONG 매수호가총잔량{ 0 };
	int 매도호가총잔량직전대비{ 0 };
	int 매수호가총잔량직전대비{ 0 };
	int 순매수잔량{ 0 };
	double 매수비율{ 0 };
	int 순매도잔량{ 0 };
	double 매도비율{ 0 };
	int 장운영구분{ 0 };
	wchar_t 투자자별ticker[40] = { 0 };	// 이게 뭔지 모름
};

// 호가 단계별 정보
struct 호가단계정보
{
	int 매도호가;              // [41~50]
	int 매도호가수량;          // [61~70]  
	int 매도호가직전대비;      // [81~90]
	int 매수호가;              // [51~60]
	int 매수호가수량;          // [71~80]
	int 매수호가직전대비;      // [91~100]
};

// LP 호가 정보
struct LP호가정보
{
	int LP매도호가수량[10];    // [621~630]
	int LP매수호가수량[10];    // [631~640]
};

// KRX 정보
struct KRX정보
{
	int 매도호가잔량[10];      // [6044~6053]
	int 매수호가잔량[10];      // [6054~6063]
	int 매도호가총잔량;        // [6064]
	int 매수호가총잔량;        // [6065]

	int 중간가매도총잔량증감;   // [6100]
	int 중간가매도총잔량;      // [6101]
	int 중간가;               // [6102]
	int 중간가매수총잔량;      // [6103]
	int 중간가매수총잔량증감;   // [6104]
	int 중간가대비;           // [6110]
	char 중간가대비기호;       // [6111]
	double 중간가대비등락율;   // [6112]
};

// NXT 정보
struct NXT정보
{
	int 매도호가잔량[10];      // [6066~6075]
	int 매수호가잔량[10];      // [6076~6085]
	int 매도호가총잔량;        // [6086]
	int 매수호가총잔량;        // [6087]

	int 중간가매도총잔량증감;   // [6105]
	int 중간가매도총잔량;      // [6106]
	int 중간가;               // [6107]
	int 중간가매수총잔량;      // [6108]
	int 중간가매수총잔량증감;   // [6109]
	int 중간가대비;           // [6113]
	char 중간가대비기호;       // [6114]
	double 중간가대비등락율;   // [6115]
};

// 예상체결 정보
struct 예상체결정보
{
	int 예상체결가;                    // [23]
	int 예상체결수량;                  // [24]
	int 예상체결가전일종가대비;         // [200]
	double 예상체결가전일종가대비등락율; // [201]
	char 예상체결가전일종가대비기호;     // [238]

	int 예상체결가유효;                // [291] (예상체결 시간동안만 유효)
	int 예상체결량;                    // [292]
	char 예상체결가전일대비기호;        // [293]
	int 예상체결가전일대비;            // [294]
	double 예상체결가전일대비등락율;    // [295]
	double 전일거래량대비예상체결률;     // [299]
};

// 메인 호가 구조체
struct _NEW_실시간호가정보
	: public _실시간_패킷_헤더
{
	// === 기본 정보 ===
	wchar_t 호가시간[16];         // [21]
	ULONG 누적거래량;          // [13]
	wchar_t 장운영구분[8];       // [215]
	wchar_t 투자자별ticker[16];   // [216]

	// === 호가 단계별 정보 (1~10단계) ===
	호가단계정보 호가단계[10];

	// === 총잔량 정보 ===
	int 매도호가총잔량;          // [121]
	int 매도호가총잔량직전대비;    // [122]
	int 매수호가총잔량;          // [125]
	int 매수호가총잔량직전대비;    // [126]

	int 순매수잔량;              // [128]
	double 매수비율;              // [129]
	int 순매도잔량;              // [138]
	double 매도비율;              // [139]

	// === 예상체결 정보 ===
	예상체결정보 예상체결;

	// === LP 정보 ===
	LP호가정보 LP정보;

	// === 거래소별 정보 ===
	KRX정보 KRX;
	NXT정보 NXT;

	// === 편의 함수들 ===
	int 최우선매도호가() const { return 호가단계[0].매도호가; }
	int 최우선매수호가() const { return 호가단계[0].매수호가; }
	int 호가스프레드() const { return 최우선매도호가() - 최우선매수호가(); }

	// 총 매도/매수 물량 계산
	int 총매도물량() const {
		int total = 0;
		for (int i = 0; i < 10; ++i) {
			total += 호가단계[i].매도호가수량;
		}
		return total;
	}

	int 총매수물량() const {
		int total = 0;
		for (int i = 0; i < 10; ++i) {
			total += 호가단계[i].매수호가수량;
		}
		return total;
	}

	// 매수/매도 우위 판단
	bool Is매수우위() const { return 매수비율 > 매도비율; }
	bool Is매도우위() const { return 매도비율 > 매수비율; }

	// 호가 강도 계산 (1~5호가 가중 합계)
	double Get매도호가강도() const {
		double 강도 = 0.0;
		double 가중치[] = { 0.5, 0.2, 0.15, 0.1, 0.05 };
		for (int i = 0; i < 5; ++i) {
			강도 += 호가단계[i].매도호가수량 * 가중치[i];
		}
		return 강도;
	}

	double Get매수호가강도() const {
		double 강도 = 0.0;
		double 가중치[] = { 0.5, 0.2, 0.15, 0.1, 0.05 };
		for (int i = 0; i < 5; ++i) {
			강도 += 호가단계[i].매수호가수량 * 가중치[i];
		}
		return 강도;
	}
};

struct _CONV_실시간_주식우선호가
	: public _실시간_패킷_헤더
{
	int 최우선매도호가{ 0 };			// 18105
	int 최우선매수호가{ 0 };			// 18100
};



struct _CONV_실시간_주식예상체결
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	BYTE 거래유형{ 0 };
	int 현재가{ 0 };
	int 전일대비{ 0 };
	double 등락율{ 0 };
	int 거래량{ 0 };			// +는 매수, -는 매도
	int 누적거래량{ 0 };
	int 전일대비기호{ 0 };
};

struct _CONV_실시간_선물시세
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	int 현재가{ 0 };
	int 전일대비{ 0 };
	double 등락율{ 0 };
	int 최우선매도호가{ 0 };
	int 최우선매수호가{ 0 };
	ULONG 체결량{ 0 };
	ULONG 누적거래량{ 0 };
	LONGLONG 누적거래대금{ 0 };
	int 시가{ 0 };
	int 고가{ 0 };
	int 저가{ 0 };
	int 미결제약정{ 0 };
	int 이론가{ 0 };
	int 이론베이시스{ 0 };
	int 시장베이시스{ 0 };
	double 괴리율{ 0 };
	int 미결제약정전일대비{ 0 };
	double 괴리도{ 0 };
	int 전일대비기호{ 0 };
	int KOSPI200{ 0 };
	double 전일거래량대비계약주{ 0 };
	int 시초미결제약정수량{ 0 };
	int 최고미결제약정수량{ 0 };
	int 최저미결제약정수량{ 0 };
	double 전일거래량대비비율{ 0 };
	int 미결제증감{ 0 };
	int 실시간상한가{ 0 };
	int 실시간하한가{ 0 };
	int 협의대량누적체결수량{ 0 };
	int 상한가{ 0 };
	int 하한가{ 0 };
};

struct _CONV_실시간_선물호가잔량
	: public _실시간_패킷_헤더
{
	wchar_t 호가시간[7] = { 0 };
	int 매도호가[5] = { 0 };
	ULONG 매도호가수량[5] = { 0 };
	int 매도호가직전대비[5] = { 0 };
	int 매수호가[5] = { 0 };
	ULONG 매수호가수량[5] = { 0 };
	int 매수호가직전대비[5] = { 0 };
	ULONG 매도호가총잔량{ 0 };
	ULONG 매수호가총잔량{ 0 };
	int 매도호가총잔량직전대비{ 0 };
	int 매수호가총잔량직전대비{ 0 };
	ULONG 매도호가총건수{ 0 };
	ULONG 매수호가총건수{ 0 };
	int 순매수잔량{ 0 };
	int 호가순잔량{ 0 };
	ULONG 누적거래량{ 0 };
};

struct _CONV_실시간_옵션시세
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	int 현재가{ 0 };
	int 전일대비{ 0 };
	double 등락율{ 0 };
	int 최우선매도호가{ 0 };
	int 최우선매수호가{ 0 };
	ULONG 체결량{ 0 };
	ULONG 누적거래량{ 0 };
	LONGLONG 누적거래대금{ 0 };
	int 시가{ 0 };
	int 고가{ 0 };
	int 저가{ 0 };
	int 미결제약정{ 0 };
	int 이론가{ 0 };
	double 괴리율{ 0 };
	double 델타{ 0 };
	double 감마{ 0 };
	double 세타{ 0 };
	double 베가{ 0 };
	double 로{ 0 };
	int 미결제약정전일대비{ 0 };
	int 전일대비기호{ 0 };
	double 전일거래량대비계약주{ 0 };
	int 호가순잔량{ 0 };
	double 내재가치{ 0 };
	int KOSPI200{ 0 };
	int 시초미결제약정수량{ 0 };
	int 최고미결제약정수량{ 0 };
	int 최저미결제약정수량{ 0 };
	int 선물최근월물지수{ 0 };
	int 미결제증감{ 0 };
	double 시간가치{ 0 };
	double 내재변동성{ 0 };
	double 전일거래량대비비율{ 0 };
	double 기준가대비시가등락율{ 0 };
	double 기준가대비고가등락율{ 0 };
	double 기준가대비저가등락율{ 0 };
};

struct _CONV_실시간_옵션호가잔량
	: public _실시간_패킷_헤더
{
	wchar_t 호가시간[7] = { 0 };
	int 매도호가[5] = { 0 };
	ULONG 매도호가수량[5] = { 0 };
	int 매도호가직전대비[5] = { 0 };
	ULONG 매도호가건수[5] = { 0 };
	int 매수호가[5] = { 0 };
	ULONG 매수호가수량[5] = { 0 };
	int 매수호가직전대비[5] = { 0 };
	ULONG 매수호가건수[5] = { 0 };

	ULONG 매도호가총잔량{ 0 };
	int 매도호가총잔량직전대비{ 0 };
	ULONG 매도호가총건수{ 0 };
	ULONG 매수호가총잔량{ 0 };
	int 매수호가총잔량직전대비{ 0 };
	ULONG 매수호가총건수{ 0 };
	int 순매수잔량{ 0 };
	int 호가순잔량{ 0 };
	ULONG 누적거래량{ 0 };
};


struct _CONV_실시간_업종지수
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	double 현재가{ 0 };
	double 전일대비{ 0 };
	double 등락율{ 0 };
	int 거래량{ 0 };
	ULONG 누적거래량{ 0 };
	LONGLONG 누적거래대금{ 0 };
	double 시가{ 0 };
	double 고가{ 0 };
	double 저가{ 0 };
	int 전일대비기호{ 0 };
	double 전일거래량대비_계약_주{ 0 };
};

struct _CONV_실시간_업종등락
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	ULONG 상승종목수{ 0 };
	ULONG 상한종목수{ 0 };
	ULONG 보합종목수{ 0 };
	ULONG 하락종목수{ 0 };
	ULONG 하한종목수{ 0 };
	ULONG 누적거래량{ 0 };
	LONGLONG 누적거래대금{ 0 };
	double 현재가{ 0 };
	double 전일대비{ 0 };
	double 등락율{ 0 };
	ULONG 거래형성종목수{ 0 };
	double 거래형성비율{ 0 };
	int 전일대비기호{ 0 };
};

struct _CONV_실시간_선물이론가
	: public _실시간_패킷_헤더
{
	int 미결제약정{ 0 };
	int 이론가{ 0 };
	int 이론베이시스{ 0 };
	int 시장베이시스{ 0 };
	double 괴리율{ 0 };
	int 미결제약정전일대비{ 0 };
	double 괴리도{ 0 };
	int 시초미결제약정수량{ 0 };
	int 최고미결제약정수량{ 0 };
	int 최저미결제약정수량{ 0 };
};

struct _CONV_실시간_옵션이론가
{
	int 미결제약정{ 0 };
	int 이론가{ 0 };
	double 괴리율{ 0 };
	double 델타{ 0 };
	double 감마{ 0 };
	double 세타{ 0 };
	double 베가{ 0 };
	double 로{ 0 };
	int 미결제약정전일대비{ 0 };
	int 시초미결제약정수량{ 0 };
	int 최고미결제약정수량{ 0 };
	int 최저미결제약정수량{ 0 };
	double 내재가치{ 0 };
	double 시간가치{ 0 };
	double 내재변동성{ 0 };
};

struct _CONV_실시간_ETF_NAV
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	int 현재가{ 0 };
	int 전일대비{ 0 };
	double 등락율{ 0 };
	ULONG 누적거래량{ 0 };
	int NAV{ 0 };
	int NAV전일대비{ 0 };
	double NAV등락율{ 0 };
	double 추적오차율{ 0 };
	int 전일대비기호{ 0 };
	double ELW기어링비율{ 0 };
	double ELW손익분기율{ 0 };
	double ELW자본지지점{ 0 };
	double NAV지수괴리율{ 0 };
	double NAV_ETF괴리율{ 0 };
};

struct _CONV_실시간_ELW_지표
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	int ELW패리티{ 0 };
	int ELW프리미엄{ 0 };
	double ELW기어링비율{ 0 };
	double ELW손익분기율{ 0 };
	double ELW자본지지점{ 0 };
};

struct _CONV_실시간_ELW_이론가
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	int 현재가{ 0 };
	int ELW이론가{ 0 };
	double ELW내재변동성{ 0 };
	double ELW델타{ 0 };
	double ELW감마{ 0 };
	double ELW쎄타{ 0 };
	double ELW베가{ 0 };
	double ELW로{ 0 };
	double LP호가내재변동성{ 0 };
};

struct _CONV_실시간_VI발동해제
	: public _실시간_패킷_헤더
{
	bool bEnable{ false };
	wchar_t 종목명[64] = { 0 };
	ULONG 누적거래량{ 0 };
	LONGLONG 누적거래대금{ 0 };
	int VI발동구분{ 0 };
	int 전체구분{ 0 };
	int 장전구분{ 0 };
	int VI발동가격{ 0 };
	wchar_t 매매체결처리시각[7] = { 0 };
	wchar_t VI해제시각[7] = { 0 };
	int VI적용구분{ 0 };
	int 기준가격정적{ 0 };
	int 기준가격동적{ 0 };
	double 괴리율정적{ 0 };
	double 괴리율동적{ 0 };
	wchar_t ExtraItem1[20] = { 0 };
	wchar_t ExtraItem2[20] = { 0 };
	wchar_t ExtraItem3[20] = { 0 };
	wchar_t ExtraItem4[20] = { 0 };
};

struct _CONV_실시간_종목프로그램매매
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[7] = { 0 };
	int 현재가{ 0 };
	int 전일대비기호{ 0 };
	int 전일대비{ 0 };
	double 등락율{ 0 };
	ULONG 누적거래량{ 0 };
	ULONG 매도수량{ 0 };
	LONGLONG 매도금액{ 0 };
	ULONG 매수수량{ 0 };
	LONGLONG 매수금액{ 0 };
	int 순매수수량{ 0 };
	LONGLONG 순매수금액{ 0 };
	LONGLONG 순매수금액증감{ 0 };

	wchar_t 장시작예상잔여시간[20] = { 0 };
	wchar_t 장운영구분[20] = { 0 };
	wchar_t 투자자별ticker[20] = { 0 };
};

struct _CONV_실시간_주식당일거래원
	: public _실시간_패킷_헤더
{
	wchar_t 매도거래원[5][40] = { 0 };
	ULONG 매도거래원수량[5] = { 0 };
	int 매도거래원별증감[5] = { 0 };
	int 매도거래원코드[5] = { 0 };
	int 매도거래원색깔[5] = { 0 };

	wchar_t 매수거래원[5][40] = { 0 };
	ULONG 매수거래원수량[5] = { 0 };
	int 매수거래원별증감[5] = { 0 };
	int 매수거래원코드[5] = { 0 };
	int 매수거래원색깔[5] = { 0 };

	ULONG 외국계매도추정합{ 0 };
	int 외국계매도추정합변동{ 0 };
	ULONG 외국계매수추정합{ 0 };
	int 외국계매수추정합변동{ 0 };
	ULONG 외국계순매수추정합{ 0 };
	int 외국계순매수변동{ 0 };
	int 거래소구분{ 0 };
};

struct _CONV_실시간_장시작시간
	: public _실시간_패킷_헤더
{
	wchar_t 체결시간[(1 << 5)] = { 0 };				// 091259
	wchar_t 장운영구분[(1 << 5)] = { 0 };
	wchar_t 장시작예상잔여시간[(1 << 5)] = { 0 };
	//wchar_t 현재시간[(1 << 5)] = { 0 };
};

struct _저장용_체결변환
{
	int nSequence{ 0 };		// 받은 순서
	ULONGLONG nTimeStamp{ 0 };	// 받은 시간
	BYTE nDataType{ 0 };
	ULONG 체결시간{ 0 };		// 체결시간
	float 현재가{ 0 };			// 체결가격
	float 전일대비{ 0 };			// 전일대비
	float 등락율{ 0 };			// 등락율
	float 최우선매도호가{ 0 };	// 최우선매도호가
	float 최우선매수호가{ 0 };	// 최우선매수호가
	ULONG 거래량{ 0 };			// 체결량
	ULONG 누적거래량{ 0 };		// 누적거래량
	LONGLONG 누적거래대금{ 0 };	// 누적거래대금
	float 시가{ 0 };				// 시가
	float 고가{ 0 };				// 고가
	float 저가{ 0 };				// 저가
	float 전일대비기호{ 0 };		// 전일대비기호
	float 전일거래량대비_계약주{ 0 };	// 전일거래량대비(계약주)
	LONGLONG 거래대금증감{ 0 };		// 거래대금증감
	float 전일거래량대비_비율{ 0 };	// 전일거래량대비(비율)
	float 거래회전율{ 0 };		// 거래회전율
	float 거래비용{ 0 };			// 거래비용
	float 체결강도{ 0 };			// 체결강도
	float 시가총액{ 0 };			// 시가총액
	float 장구분{ 0 };			// 장구분
	float KO접근도{ 0 };			// KO접근도
	ULONG 상한가발생시간{ 0 };	// 상한가발생시간
	ULONG 하한가발생시간{ 0 };	// 하한가발생시간
};

struct _실시간_체결변환
{
	int nSequence{ 0 };		// 받은 순서
	ULONGLONG nTimeStamp{ 0 };	// 받은 시간
	wchar_t szCode[7] = { 0 };	// "005930"
	BYTE nDataType{ 0 };
	ULONG nTime{ 0 };			// 체결시간
	BYTE nTransType{ 0 };		// 1: 매수, 2: 매도, 3: 단일가매매(동시호가)
	double nPrice{ 0.0 };		// 체결가격
	ULONG nTransVolume{ 0 };	// 체결량
};

struct _주식체결_변환	// 메모리 연산용 
{
	ULONGLONG nSequence{ 0 };			// 받은 순서 ( 키움으로부터 )
	ULONGLONG nTimeStamp{ 0 };			// 받은 시간 ( 키움으로부터 )
	char szCode[7] = { 0 };			// "005930"
	BYTE nTransType{ 0 };			// 0: 단일가, 1: 매수, 2: 매도
	ULONG nTime{ 0 };				// 체결시간, 파일 이름이 11시59분31초, 여기 뒤에 밀리초 3자리 붙인다.
	double nPrice{ 0.0 };				// 체결가격
	ULONG nTransVolume{ 0 };		// 체결량
};

struct _캔들데이터		// 메모리 연산용
{	// 1분봉의 경우 시작과 끝의 날짜 시간이 동일하다.
	ULONG nStartDate{ 0 };						// 이전 데이터 가져와서 박아넣을꺼라 날짜가 필요함.
	ULONG nStartTime{ 0 };						// 0900~1530, 초를 잘라서 이렇게 저장된다.
	ULONG nEndDate{ 0 };						// 분봉 일봉 날짜 다 같을테니 주석한다
	ULONG nEndTime{ 0 };						// 일봉은 1530 이고, 표시하면 될텐데 굳이 필요할까?

	double nOpen{ 0.0 };						// 시작가
	double nHigh{ 0.0 };						// 고가
	double nLow{ 0.0 };							// 저가
	double nClose{ 0.0 };						// 종가

	ULONG nAccrueVolumeTotal{ 0 };				// 누적거래량 (매수매도 + 장시작 단일가 및 장마감 동시호가 포함)
	// custom data
	ULONG nTimeFrame{ 0 };						// 1초봉은 1, 10초봉은 10, 1분봉은 60, 1일봉은 1440
	double nAveragePaymentBuy{ 0.0 };			// 평균 매수 거래가
	double nAveragePaymentSell{ 0.0 };			// 평균 매도 거래가

	ULONG nAccrueVolumeBuy{ 0 };				// 누적매수거래량, 체결 데이터에서 누적 해야함.
	ULONG nAccrueVolumeSell{ 0 };				// 누적매도거래량, 체결 데이터에서 누적 해야함.

	int64_t nAccruePaymentBuy{ 0 };				// 누적 매수거래대금
	int64_t nAccruePaymentSell{ 0 };			// 누적 매도거래대금
	int64_t nAccruePaymentTotal{ 0 };			// 누적 거래대금(매수매도 + 장시작 단일가 및 장마감 동시호가 포함, 천원 미만은 자른다.)

	ULONG nAccrueNumberofTimesBuy{ 0 };			// 누적 매수체결 횟수
	ULONG nAccrueNumberofTimesSell{ 0 };		// 누적 매도체결 횟수
};

struct _UPJONG_INFO_KIWOOM
	//: public _USER_ID
	//, public _CODE
	//, public _STOCK_NAME
{
	dk::WCHART<16> user_id;	// 업종코드
	dk::WCHART<16> code;	// 업종코드
	dk::WCHART<64> stock_name;	// 업종명

	int nMaxStockCount{ 0 };	// 종목총개수
	//int nStockCount{ 0 };		// 한번에 전송되는 총 개수

};

struct _STOCK_INFO_KIWOOM
{
	dk::WCHART<16> user_id;		// 사용자 ID
	dk::WCHART<16> code;		// 종목코드
	dk::WCHART<64> stock_name;	// 종목명

	int nMaxStockCount{ 0 };		// 종목총개수
	int nStockCount{ 0 };			// 한번에 전송되는 총 개수
	bool 거래정지{ false };			// 거래정지
	bool 관리종목{ false };			// 관리종목
	bool 담보대출{ false };			// 담보대출
	bool 신용가능{ false };			// 신용가능
	bool bELW{ false };				// ELW
	bool 뮤추얼펀드{ false };		// 뮤추얼 펀드	( 구려 )
	bool 신주인수권{ false };		// 신주인수권	( 작전주 같음 )
	bool 리츠{ false };				// 리츠			( 좋아 )
	bool bETF{ false };				// ETF			( 코스피 코스닥에 많음 )
	BYTE 감리구분{ 0 };				// [0]: 정상, [1]: 투자주의, [20]: 투자경고, [3]: 투자위험, [4]: 투자주의환기종목
	WORD 증거금{ 0 };				// 증거금
	int nPreClose{ 0 };			// nPreClose		( 모두 있음 )
	ULONG nMarketCap{ 0 };			// 상장주식수
	int nMarketCapTotal{ 0 };		// 시가총액

	bool 하이일드펀드{ false };		// ETF			( 코스피 코스닥에 많음 )
	bool K_OTC{ false };			// ETF			( 코스피 코스닥에 많음 )
	bool 코넥스{ false };			// ETF			( 코스피 코스닥에 많음 )
};

// 주문 결과
struct _ORDER_RESULT_KIWOOM
	: public _TICK_COUNT
{
	dk::WCHART<16> user_id;		// 사용자 ID

	bool bSuccess{ false };			// 주문 성공 여부
	BYTE bRegiScreen{ 0 };			// [0]: 현상태 유지, [1]: 화면번호 등록, [2]: 화면번호 해제
	BYTE bytTrType{ 0 };				// 주문 유형

	wchar_t szScrNo[7] = { 0 };	// 화면번호
	wchar_t szRQName[20] = { 0 };	// 사용자 구분명
	wchar_t szTrCode[32] = { 0 };	//
	wchar_t szMsg[128] = { 0 };		// 주문 결과 메시지
};

struct _REQUEST_TR_OPW00001
{
	wchar_t 계좌번호[20] = { 0 };
	wchar_t 화면번호[5] = { 0 };
	wchar_t 조회구분[2] = { 0 };
};

struct _RESULT_TR_OPW00001
	: public _TICK_COUNT
{
	dk::WCHART<16> user_id;		// 사용자 ID
	wchar_t 예수금[20]{};
	wchar_t 출금가능금액[20]{};
	wchar_t 주문가능금액[20]{};
};

struct _REQUEST_TR_OPW00018
{
	wchar_t 계좌번호[20] = { 0 };
	wchar_t 화면번호[5] = { 0 };
	wchar_t 조회구분[2] = { 0 };
};

struct _RESULT_TR_OPW00018S
	: public _TICK_COUNT
{
	dk::WCHART<16> user_id;		// 사용자 ID
	ULONG64 총매입금액{ 0 };
	ULONG64 총평가금액{ 0 };
	ULONG64 총평가손익금액{ 0 };
	double 총수익률{ 0 };
	ULONG64 추정예탁자산{ 0 };
	ULONG64 매도가능금액{ 0 };
	ULONG64 총대출금{ 0 };
	ULONG64 총융자금액{ 0 };
	ULONG64 총대주금액{ 0 };
	int 조회건수{ 0 };
};

struct _RESULT_TR_OPW00018M
	: public _TICK_COUNT
{
	dk::WCHART<16> user_id;		// 사용자 ID
	wchar_t szCode[8] = { 0 };
	wchar_t szName[128] = { 0 };
	int 보유수량{ 0 };
	int 매매가능수량{ 0 };
	double 매입가{ 0 };
	double 현재가{ 0 };
	double 매입금액{ 0 };
	double 매입수수료{ 0 };
	double 평가금액{ 0 };
	double 평가수수료{ 0 };
	double 세금{ 0 };
	double 수수료합{ 0 };
};


struct _MARKET_TIME
{
	int nStartTime{ 0 };
	int nEndTime{ 0 };
	size_t nCountCreonItems{ 0 };
};

typedef struct _REQUEST_REALTIME_DATA
{
	int nStockCount{ 0 };
	wchar_t szScrNo[(1 << 3)];				// szScrNum
	wchar_t szStocks[(1 << 10)];			// ';'로 구분된 종목코드, 화면당 최대 100개
} REQUEST_REALTIME_DATA, * LPREQUEST_REALTIME_DATA;

struct _SEND_ORDER_KIWOOM
{
	int nOrderType{ 0 };					// 주문유형 1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정
	int nCount{ 0 };						// 주문수량
	int nPrice{ 0 };						// 주문가격
	//int nTradeType{ 0 };					// 주문유형 1: 지정가, 2: 시장가, 3: 조건부지정가, 12: 장전시간외종가, 13: 시간외단일가, 14: 장후시간외종가
	wchar_t szTrType[3] = { 0 };			// 거래구분 "00":지정가, "03":시장가

	wchar_t szOrderName[20] = { 0 };		// 사용자구분명, 임의로 전략명 같은걸 넣어도 됨.
	wchar_t szScrNum[5] = { 0 };				// 화면번호
	wchar_t szAccno[20] = { 0 };			// 계좌번호 (10자리)

	wchar_t szCode[7] = { 0 };				// 종목코드 (6자리)

	// 주문유형은 변환해서 보내야함.

	wchar_t nOriginOrderNo[20] = { 0 };		// 원주문번호 - 신규주문시 공백입력, 정정, 취소주문시 원주문번호 입력
};

//[거래구분]
//00 : 지정가
//03 : 시장가
//05 : 조건부지정가
//06 : 최유리지정가
//07 : 최우선지정가
//10 : 지정가IOC
//13 : 시장가IOC
//16 : 최유리IOC
//20 : 지정가FOK
//23 : 시장가FOK
//26 : 최유리FOK
//61 : 장전시간외종가
//62 : 시간외단일가매매
//81 : 장후시간외종가
//※ 모의투자에서는 지정가 주문과 시장가 주문만 가능합니다.

struct _REQUEST_ORDER_KW
{
	dk::WCHART<16> user_id;		// 사용자 ID
	ULONGLONG nTime{ 0 };				// 주문 발생 시간

	int nOrdType{ 0 };					// 주문유형 1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정
	int nOrdVolume{ 0 };				// 주문수량
	int nPrice{ 0 };					// 주문가격
	//int nTrType{ 0 };				// 거래구분 1: 지정가, 2: 시장가, 3: 조건부지정가, 12: 장전시간외종가, 13: 시간외단일가, 14: 장후시간외종가
	wchar_t szTrType[3] = { 0 };		// 00: 지정가, 03: 시장가, 05: 조건부지정가, 06: 최유리지정가, 07: 최우선지정가, 10: 지정가IOC, 13: 시장가IOC, 16: 최유리IOC, 20: 지정가FOK, 23: 시장가FOK, 26: 최유리FOK, 61: 장전시간외종가, 62: 시간외단일가매매, 81: 장후시간외종가
	wchar_t szScrNo[5] = { 0 };			// 화면번호
	wchar_t szCode[7] = { 0 };			// 종목코드
	wchar_t szAccno[11] = { 0 };		// 계좌번호
	wchar_t szOrdNo[20] = { 0 };		// 주문번호
	wchar_t szOrgOrdNo[20] = { 0 };		// 원주문번호
	wchar_t szRQName[20] = { 0 };		// 사용자구분명

	int nStep{ 0 };					// 0: 주문전, 1: 주문후, 2: 접수, 확인됨, 체결완료시 오더를 삭제한다.
	int nUnsettledVolume{ 0 };			// 미체결수량
	int nVolume{ 0 };					// 체결수량
};


struct _실시간_키움_주문체결통보
{
	dk::WCHART<16> user_id;		// 사용자 ID
	//int nOrdType{ 0 };					// 주문구분: [1]: 매수, [2]: 매도, [3]: 매수정정, [4]: 매도정정, [5]: 매수취소, [6]: 매도취소
	int nOrdStatus{ 0 };				// 주문상태: [1]: 접수, [2]: 확인, [3]: 체결, [4]: 거부, [5]: 접수거부, [6]: 확인거부
	wchar_t szOrdVolume[20]{};			// 주문수량
	wchar_t szTransVolume[20]{};		// 체결수량
	wchar_t szUnitTransVolume[20]{};		// 단위체결수량
	wchar_t szUnsettledVolume[20]{};	// 미체결수량이 0이면 체결완료, 0이 아니면 미체결

	wchar_t szPrice[20]{};				// 주문가격
	wchar_t szTransPrice[20]{};			// 체결가격
	wchar_t szUnitTransPrice[20]{};		// 단위체결가격

	wchar_t szOrdStatus[11] = { 0 };	// 주문상태: [1]: 접수, [2]: 확인, [3]: 체결, [4]: 거부, [5]: 접수거부, [6]: 확인거부
	wchar_t szScrNo[5] = { 0 };		// 화면번호
	wchar_t szCode[7] = { 0 };			// 종목코드
	wchar_t szCheTime[9] = { 0 };		// 체결시간
	wchar_t szOrdType[11] = { 0 };		// 주문상태: 매수, 매도, 매도정정, 매수정정, 매수취소, 매도취소
	//char szAccno[11] = { 0 };		// 계좌번호
	wchar_t szOrdName[11] = { 0 };		// 사용자구분명
	wchar_t szOrdNo[11] = { 0 };		// 주문번호
	wchar_t szOrgOrdNo[11] = { 0 };		// 원주문번호

	double dbFee{ 0.0 };		// 당일매매수수료
	double dbTax{ 0.0 };			// 당일매매세금
};

struct _실시간_키움_잔고통보
{
	 dk::WCHART<16> user_id;		// 사용자 ID
	wchar_t szCode[8]{};				// 종목코드
	wchar_t szAccno[20]{};				// 계좌번호
	wchar_t szVolume[20]{};				// 보유수량
	wchar_t szOrderableVolume[20]{};	// 주문가능수량
	wchar_t szBuyPrice[20]{};			// 매입단가
	wchar_t szTotalBuyPrice[20]{};		// 총매입가
	wchar_t szDeposit[20]{};			// 예수금
	wchar_t szProfitRate[20]{};			// 손익율
};

struct _실시간_키움_특이신호
{
	dk::WCHART<16> user_id;		// 사용자 ID

};

struct _RESULT_CANCEL_ORDER_KW
{
	bool bRegi{ false };				// true: 등록, false: 해제
	wchar_t szScrNo[5] = { 0 };			// 화면번호
};

typedef struct _REQUEST_REALTIME_CONDITION
{
	dk::WCHART<16> user_id;		// 사용자 ID
	int nConditionIndex{ 0 };
	wchar_t szScreenNumber[(1 << 3)] = { 0 };			// 화면번호
	wchar_t szConditionName[(1 << 6)] = { 0 };			// 조건식 이름
} REQUEST_REALTIME_CONDITION, * LPREQUEST_REALTIME_CONDITION;

typedef struct _KIWOOM_REALDATA_HEADER
{
	BYTE nRealType{ 0 };							// 주식시세, 주식체결 등
	wchar_t szCode[(1 << 4)] = { 0 };					// 종목코드
} KIWOOM_REALDATA_HEADER, * LPKIWOOM_REALDATA_HEADER;

typedef struct _KIWOOM_REALDATA_TRANSACTION
	: public _KIWOOM_REALDATA_HEADER
{
	BYTE nTransType{ 0 };							// 1 = 매수, 2 = 매도, 3 = 단일가매매(동시호가)
	BYTE nTransType2{ 0 };							// 1 = 단일가매수, 2 = 단일가매도
	wchar_t szDate[(1 << 5)] = { 0 };					// 230504
	wchar_t szTime[(1 << 5)] = { 0 };				// 091259
	ULONG 체결량{ 0 };								//
	ULONG 누적거래량{ 0 };							//
	int 체결가{ 0 };							//
	int 최우선매도호가{ 0 };					//
	int 최우선매수호가{ 0 };					//
	//wchar_t szOpen[(1 << 4)] = { 0 };				//
	//wchar_t szHigh[(1 << 4)] = { 0 };				//
	//wchar_t szLow[(1 << 4)] = { 0 };					//
	//wchar_t 누적거래대금[(1 << 4)] = { 0 };			// 누적거래대금 9999999999999
	//wchar_t 시가총액[(1 << 4)] = { 0 };
	//wchar_t 체결강도[(1 << 4)] = { 0 };				// 체결강도
	//wchar_t 등락율[(1 << 4)] = { 0 };
	//wchar_t 전일거래량대비[(1 << 4)] = { 0 };		// 전일거래량대비(비율)
	//wchar_t 거래회전율[(1 << 4)] = { 0 };
	//wchar_t 전일동시간거래량비율[(1 << 4)] = { 0 };
} KIWOOM_REALDATA_TRANSACTION, * LPKIWOOM_REALDATA_TRANSACTION;

struct _RECIVE_TR_CONDITION_DATA
{
	int nConditionIndex{ 0 };
	int nCountNextData{ 0 };
	wchar_t szScreenNumber[(1 << 5)] = { 0 };
	wchar_t szConditionName[(1 << 5)] = { 0 };
	wchar_t szCodeList[(1 << 5)] = { 0 };
};

struct _RECIVE_REALTIME_CONDITION_DATA
{
	BYTE bInput{ 0 };
	int nConditionIndex{ 0 };
	wchar_t szStockCode[(1 << 5)] = { 0 };
	wchar_t szConditionName[(1 << 5)] = { 0 };
};

struct _FAST_ORDER_INFO_KW
{
	dk::WCHART<16> user_id;		// 사용자 ID
	dk::WCHART<16> code;		// 종목코드
	int nOrderType{ 0 };				// 주문유형 1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정
	int nOrderVolume{ 0 };				// 주문수량
	wchar_t szTrType[3] = { 0 };		// 거래구분 "00":지정가, "03":시장가
	wchar_t szAccno[20] = { 0 };		// 계좌번호 (10자리)
};

struct _ORDER_INFO_KW
{
	dk::WCHART<16> user_id;		// 사용자 ID
	dk::WCHART<16> code;		// 종목코드
	volatile long nLock{ 0 };					// 0: 락 안됨, 1: 락 됨
	void lock() { ::InterlockedExchange(&nLock, 1); }
	//bool is_lock() { return (::InterlockedCompareExchange(&nLock, 0, 0) == 1); }
	bool is_lock() { return (::InterlockedOr(&nLock, 0) == 1); }
	void unlock() { ::InterlockedExchange(&nLock, 0); }

	wchar_t szOrderName[20] = { 0 };	// 매매법 이름 정도
	wchar_t szScrNo[5] = { 0 };			// 화면번호

	int nBaseBetAmount{ 0 };
	int nOrderAmount[5] = { 0 };	// 회당 베팅 금액

	int nOrderState{ 0 };			// 0: 종료, 1: 거래중

	ULONG nBuyDate{ 0 };
	int nTotalBuyAmount{ 0 };		// 매수 금액

	int nVolume{ 0 };				// 보유량
	int nLineIndex{ 0 };			// 매수 카운트	- 스캔 및 백테용

	//int nRemainBuyVolume{ 0 };	// 미체결 매수량
	//int nRemainSellVolume{ 0 };	// 미체결 매도량
	//int nWaitBuyVolume{ 0 };		// 대기 매수량
	//int nWaitSellVolume{ 0 };	// 대기 매도량
};
#pragma pack(pop)

struct _보유주식
{
	bool bBid{ false };				// 매수 여부
	bool bAskIng{ false };			// 매도중 여부

	ULONGLONG 매수시간{ 0 };		// 매수일자
	ULONGLONG 매도시간{ 0 };		// 매도일자

	wchar_t 종목코드[7] = { 0 };	// 종목코드
	double 매입금액{ 0 };			// 매입금액
	double 평가금액{ 0 };			// 평가금액
	double 총매수비용{ 0 };			// 총매수비용
	int 보유수량{ 0 };				// 보유수량
	int 가능수량{ 0 };				// 가능수량
	double 현재가{ 0.0 };			// 현재가
	double 매입가{ 0 };				// 매입가
	double 매수후고가{ 0.0 };		// 매수후 고가
	double 손익분기{ 0.0 };			// 손익분기
	double 매수수수료{ 0.0 };		// 매수수수료
	double 매도수수료{ 0.0 };		// 예상 매도수수료
	double 세금{ 0.0 };				// 예상 세금
	double 예상수수료총합{ 0.0 };	// 예상 수수료 총합

	double 손익분기본절호가{ 0.0 };	// 스탑라인 가격
	double 손익분기터치호가{ 0.0 };	// 첫번째 스탑터치 가격
	double 스탑라인호가{ 0.0 };		// 스탑라인 가격
	double 손절라인호가{ 0.0 };		// 손절라인 가격
	bool 손절준비{ false };

	_보유주식(LPCWSTR _sCode, double _nPrice, int _nQty, double _매입가, double _매입금액, double _평가금액, double _매수수수료, double _평가수수료, double _세금, int _매매가능수량 = 0)
	{
		::wcscpy_s(this->종목코드, _sCode);
		this->매입금액 = _매입금액;
		this->평가금액 = _평가금액;
		this->보유수량 = _nQty;
		if (0 < _매매가능수량) { this->가능수량 = _매매가능수량; }
		this->현재가 = _nPrice;
		this->매입가 = _매입가;

		this->매수수수료 = _매수수수료;
		this->매도수수료 = _평가수수료;
		this->세금 = _세금;

		// 총매수비용 계산
		this->총매수비용 = (this->매입가 * this->보유수량) + this->매수수수료;
		// 손익분기점은 주식 거래에서 수익과 비용이 일치하는 가격이다.
		this->손익분기 = (총매수비용 + this->매도수수료 + this->세금) / this->보유수량;

		this->손익분기본절호가 = kw::get_hoga_price(this->손익분기, true, 3);
		this->손익분기터치호가 = kw::get_hoga_price(this->손익분기본절호가, true, 5);
		// 매입가보다 4호가 내려가면 손절
		this->손절라인호가 = kw::get_hoga_price(this->매입가, true, -4);
		double 실매도가 = 0.0, 수익금 = 0.0, 수익률 = 0.0;
		this->예상수수료총합 = kw::get_real_profit_kw(실매도가, 수익금, 수익률, this->매입금액, this->평가금액);


		DBGPRINT(L"종목코드: %s, 매입금액: %0.0f, 평가금액: %0.0f, 보유수량: %d, 현재가: %0.0f, 매입가: %0.0f, 매수수수료: %0.0f, 매도수수료: %0.0f, 세금: %0.0f, 총매수비용: %0.0f, 손익분기: %0.0f, 손익분기본절호가: %0.0f, 손익분기터치호가: %0.0f"
			, this->종목코드, this->매입금액, this->평가금액, this->보유수량, this->현재가, this->매입가, this->매수수수료, this->매도수수료, this->세금, this->총매수비용, this->손익분기, this->손익분기본절호가, this->손익분기터치호가
		);
	}

	_보유주식(_실시간_키움_주문체결통보* _pBuf)
	{
		this->bBid = true;
		::wcscpy_s(this->종목코드, _pBuf->szCode);
		this->현재가 = this->매입가 = ::_wtof(_pBuf->szUnitTransPrice);
		this->보유수량 = this->가능수량 = ::_wtoi(_pBuf->szUnitTransVolume);
		this->매입금액 = this->매입가 * this->보유수량;
		this->평가금액 = this->현재가 * this->보유수량;

		double 매수수수료_ = this->매입금액 * kw::_KIWOOM_REAL_FEE_;
		this->매수수수료 = 매수수수료_ - ::fmod(매수수수료_, 10);
		double 매도수수료_ = this->평가금액 * kw::_KIWOOM_REAL_FEE_;
		this->매도수수료 = 매도수수료_ - ::fmod(매도수수료_, 10);
		double 세금_ = this->평가금액 * kw::_KIWOOM_TAX_;
		this->세금 = 세금_ - ::fmod(세금_, 1);

		this->총매수비용 = this->매입금액 + this->매수수수료;
		this->손익분기 = (this->총매수비용 + this->매도수수료 + this->세금) / this->보유수량;

		double 실매도가 = 0.0, 수익금 = 0.0, 수익률 = 0.0;
		this->예상수수료총합 = kw::get_real_profit_kw(실매도가, 수익금, 수익률, this->매입금액, this->평가금액);

		this->손익분기본절호가 = kw::get_hoga_price(this->손익분기, true, 3);
		this->손익분기터치호가 = kw::get_hoga_price(this->손익분기본절호가, true, 5);

		// 매입가보다 4호가 내려가면 손절
		this->손절라인호가 = kw::get_hoga_price(this->매입가, true, -4);

		DBGPRINT(L"종목코드: %s, 보유수량: %d, 현재가: %0.0f, 매입가: %0.0f, 총매수비용: %0.0f, 손익분기: %0.0f, 손익분기본절: %0.0f, 손익분기터치: %0.0f, 손절: %0.0f"
			, this->종목코드, this->보유수량, this->현재가, this->매입가, this->총매수비용, this->손익분기, this->손익분기본절호가, this->손익분기터치호가, this->손절라인호가
		);
	}

	BYTE update(double _현재가)
	{
		BYTE bytResult = 0;
		if (this->현재가 != _현재가)
		{
			this->현재가 = _현재가;
			this->평가금액 = this->현재가 * this->보유수량;

			double 실매도가 = 0.0, 수익금 = 0.0, 수익률 = 0.0;
			this->예상수수료총합 = kw::get_real_profit_kw(실매도가, 수익금, 수익률, this->매입금액, this->평가금액);
			// 만약 스탑터치가격에 도달했으면 스탑터치를 true로 설정

			if (0.0 == this->손익분기터치호가 && this->손익분기 >= this->현재가)	// 스탑터치가격에 도달한 이후 현재가가 손익분기를 위협하면
			{	// 스탑터치가가 없으면 이미 터치를 한거임
				bytResult = 2;	// 매도해야한다.
				DBGPRINT(L"손익분기 후 손익분기 매도 발생");
			}
			else if (this->손익분기터치호가 <= this->현재가)
			{	// 스탑터치가격에 도달했으면 스탑터치가를 초기화.
				this->손익분기터치호가 = 0.0;
				DBGPRINT(L"손익분기 터치함");
			}
			if (this->손익분기 <= this->현재가)
			{
				this->손절준비 = true;
			}
			if (bBid)	// 실시간 매수 건에 대해서만 고가 스탑을 건다.
			{	// 고가갱신
				if (this->매수후고가 < this->현재가)
				{
					this->매수후고가 = this->현재가;
					// 고가 대비 -4호가 아래로 스탑라인호가 설정
					this->스탑라인호가 = kw::get_hoga_price(this->매수후고가, true, -4);
				}
				else if (0.0 == this->손익분기터치호가 && this->스탑라인호가 >= this->현재가)
				{	// 고가 갱신 후 스탑라인가격에 도달하면 매도해야한다.
					bytResult = 2;
					DBGPRINT(L"고가로부터 4틱 아래 매도 발생");
				}
			}
			if (손절준비)
			{
				if (this->손절라인호가 >= this->현재가)
				{
					bytResult = 2;
					DBGPRINT(L"손절라인호가 도달 매도 발생");
				}
				double 손절가 = kw::get_hoga_price(this->손절라인호가, true, -4);
				if (손절가 >= this->현재가)
				{
					bytResult = 2;
					DBGPRINT(L"손절라인호가로부터 4틱 아래 매도 발생");
				}
			}
			// 지정가 매수는 1 리턴, 지정가 매도는 2 리턴, 시장가 매수는 3 리턴, 시장가 매도는 4 리턴 매수취소는 5 리턴, 매도취소는 6 리턴
			// 일단 여기에서는 3, 4만 리턴하도록 한다.
			DBGPRINT(L"up 종목코드: %s, 보유수량: %d, 현재가: %0.0f, 손익분기: %0.0f, 손익분기본절: %0.0f, 손익분기터치: %0.0f, 고가: %0.0f, 스탑라인: %0.0f, 손절: %0.0f"
				, this->종목코드, this->보유수량, this->현재가, this->손익분기, this->손익분기본절호가, this->손익분기터치호가, this->매수후고가, this->스탑라인호가, this->손절라인호가
			);
		}
		return(bytResult);
	}
	//double get_current_profit() const
	//{
	//	return (this->평가금액 - this->총매수비용 - this->매도수수료 - this->세금);
	//}
	double get_current_profit()
	{
		double 실매도가 = 0.0, 수익금 = 0.0, 수익률 = 0.0;
		return kw::get_real_profit_kw(실매도가, 수익금, 수익률, this->매입금액, this->평가금액);
	}
};
