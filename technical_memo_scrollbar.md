# CVtListCtrlEx 스크롤바(CSCScrollbar) 작업 메모

작성 2026-06-14. 다음 세션에서 이어서 작업하기 위한 기술 메모.
대상 파일: `D:\1.Projects_C++\Common\CListCtrl\CVtListCtrlEx\VtListCtrlEx.{h,cpp}`

---

## 0. 한 줄 요약

세로/가로 자체 스크롤바(`CSCScrollbar`)를 **대칭 구조(둘 다 NC 예약 + dialog child)** 로 재작성했다.
대부분 정상 동작하나 **"가로 끝까지 스크롤해도 마지막 컬럼 우측 구분자가 v-bar 밑으로 ~5px 가린다"** 한 가지가 미해결.

---

## 1. 현재 아키텍처 (이번 세션에 B 안으로 재작성)

- 세로바 `m_scrollbar`, 가로바 `m_scrollbar_h` **둘 다 부모 dialog 의 child** (이전엔 세로=listctrl child, 가로=dialog child 비대칭이었음).
- `OnNcCalcSize` 가 **세로바 보이면 우측 `gw`(=`get_width()`), 가로바 보이면 하단 `gw`** 를 NC 로 예약 → native content 영역 = 실제 가시 영역.
  - 의도: native 가 컬럼을 content 폭까지만 그리고, native 스크롤 한계·divider hit-test·count-per-page 가 자동으로 가시영역과 일치 → overlay-vs-native 불일치 제거.
- 두 바는 NC 예약된 우측/하단 띠(=client 밖)에 위치하므로 listctrl child 면 클리핑됨 → **dialog child + `set_message_target(this)`**.
- 상태 플래그: `m_v_visible_state`, `m_h_visible_state` (OnNcCalcSize 가 읽음). framechange `SWP_FRAMECHANGED` 로 NC 재적용. 재진입 가드 `m_syncing`.

### 핵심 함수 위치 (VtListCtrlEx.cpp)
- `setup_scrollbar()` — 두 바를 dialog child 로 생성.
- `OnNcCalcSize()` — 우측/하단 gw NC 예약.
- `sync_scrollbar()` — need_v/need_h 판정(수렴 루프), framechange, 두 바 배치/모델 설정. **여기가 핵심.**
- `OnNcPaint()` — 가로바 출현 시 하단 NC 띠를 `cr_back` 으로 채움(코너 = listctrl 배경색).
- `OnStyleChanging()` — native 가 다시 붙이려는 `WS_VSCROLL|WS_HSCROLL` strip.
- `on_message_CSCScrollbar()` — 바 드래그 → `Scroll()` (세로=항목·픽셀, 가로=픽셀 `m_h_scroll_pos` 자체 추적).

### 회귀 방지 단일 출처
`sync_scrollbar` 의 `content_view_w = rc.Width()` (NC 가 이미 우측 gw 를 뺀 값) 하나를 need_h 판정·가로바 길이·max scroll·page·range 가 **모두** 사용. (이전 회귀 원인 = gw 차감이 여러 곳에 흩어져 한 곳만 고치면 desync.)

---

## 2. 이번 세션에 해결 완료 (사용자 GUI 검증됨)

1. **죽은 코드 제거** — `m_full_height`(기록만 하고 미사용), `m_nc_reserve`(진단에서만 읽음) 삭제.
2. **가로바 출현 시점** — 컬럼 우단이 세로바 *left* 를 지나는 순간 출현(이전엔 세로바 *right* 를 지나야 출현). `need_h` 가 `content_view_w` 기준.
3. **가로/세로바 교차 코너** — listctrl 배경색으로 채워짐(`OnNcPaint`).
4. **세로 thumb 끝까지 도달** — page(`visible`)가 가시 행수와 일치.

---

## 3. 미해결 문제 (다음 세션 시작점)

**증상:** 오른쪽 listctrl 에서 마지막 컬럼을 넓혀 가로바를 띄우고 **가로 끝까지 스크롤해도 마지막 컬럼 우측 구분자(헤더의 컬럼 resize 분리자)가 보이지 않는다** — v-bar 밑으로 약 5px 가림.

**근본 원인 (logWrite 측정으로 확정):**
- native listctrl 의 **가로 스크롤 viewport = 헤더 윈도우 폭**이다.
- 그런데 **헤더 윈도우 폭이 그리기 client(`GetClientRect().Width()`)보다 항상 정확히 `native_margin`(측정값 5px) 넓다.** (창 크기·컬럼폭과 무관하게 상수 5.)
- 그래서 native 는 마지막 컬럼 우측 끝을 "헤더 우측"(= client 우측 + 5px = v-bar NC 띠 안쪽 5px 지점)에 정렬시켜 멈춘다 → 구분자가 v-bar 밑 5px 에 가려 그리기 client 밖(클리핑)에 위치.

**측정 데이터 예 (큰 overflow):**
```
cli_w=443  hdr_w=448(=cli+5)  native_view=448  col_total=1309  need=870  lv_limit=870
```
→ `hdr_w = cli_w + 5`, `native_view(=col_total-lv_limit) = hdr_w`. 항상 +5.

---

## 4. 시도했으나 실패/보류한 접근

1. **컬럼 padding (마지막 컬럼을 deficit 만큼 보이지 않게 넓힘)** — ❌ **근본적으로 틀림.**
   padding 이 마지막 컬럼을 넓히면 *구분자 자체가 padding 과 함께 우측으로 이동* → 아무리 스크롤해도 구분자는 늘 끝.
   (2×native_margin 까지 시도했으나 동일.) 코드 전부 제거함.

2. **헤더 폭을 client 폭으로 강제 (`GetHeaderCtrl()->MoveWindow(... content_view_w ...)`)** — 🔶 **유력하나 미검증.**
   측정상 헤더 윈도우 폭이 콘텐츠 폭(col_total)이 아니라 `cli+5` 로 viewport 크기다. 즉 native 가 헤더를 내부 스크롤하므로, 헤더 윈도우를 client 폭으로 좁히면 native viewport 가 일치할 가능성. **단 native 가 스크롤/레이아웃 중 헤더를 재배치하므로 잘못 건드리면 가로 스크롤이 깨질 위험** → 코드 작성했다가 빌드·검증 전이라 push 전에 revert 함. **다음 세션 1순위로 측정하며 시도.**

---

## 5. 다음 세션 진행 가이드

1. `sync_scrollbar()` 의 `else`(need_h) 블록에 있는 `TODO(미해결)` 주석이 시작점.
2. **헤더 폭 강제(접근 2)** 를 다시 시도하되 measure-first:
   - 진단 logWrite 재투입 (아래 §6). `cli`, `hdr_w`, `native_view`, `lv_limit`, `col_total`, `pos`.
   - 헤더 `MoveWindow` 후 `native_view` 가 `cli` 와 같아지는지, 가로 스크롤이 안 깨지는지 확인.
   - 헤더를 좁힌 뒤에도 구분자가 가장자리에서 1px 클리핑되면(예상), native 가 마지막 컬럼 우단을 client 우측에 정렬하는 특성 때문 → "구분자를 v-bar 경계에 딱 붙여 보이게" 까지가 현실적 목표(탐색기 외관과 동일).
3. 대안: native 가로 스크롤을 안 쓰고 트레일링 **더미 컬럼**(폭 = 2×margin)으로 스크롤 여유를 주는 방법 — 단 빈 헤더 셀/빈 열이 보이는 단점.

---

## 6. 측정(logWrite) 재투입 방법

> 규칙: 일반 컨트롤(VtListCtrlEx 포함)은 **logWrite/SCLog 를 포함한 채 push 금지.** 디버깅 중에만 넣고 push 직전 제거.

1. `VtListCtrlEx.cpp` 상단 include 추가:
   `#include "../../log/SCLog/SCLog.h"`
2. `sync_scrollbar()` 의 need_h(else) 블록에서:
   ```cpp
   int lv_limit  = GetScrollLimit(SB_HORZ);
   int native_view = total_col_width - lv_limit;
   int hdr_w = -1;
   if (CHeaderCtrl* hdr = GetHeaderCtrl()) { CRect rh; hdr->GetWindowRect(&rh); hdr_w = rh.Width(); }
   logWrite(_T("[vtl/hbar] cli=%d hdr_w=%d native_view=%d col_total=%d need=%d lv_limit=%d pos=%d"),
       content_view_w, hdr_w, native_view, total_col_width, max(0,total_col_width-content_view_w), lv_limit, m_h_scroll_pos);
   ```
3. 로그 위치: `<exe>\Log\Test_SCColorTheme_YYYYMMDD_HHMMSS.log` (실행마다 새 파일, mtime 최신이 현재 세션).

---

## 7. 현재 코드 상태 (이 메모 작성 시점)

- 위 §1~§2 반영 완료, §3 미해결.
- **모든 진단 logWrite + SCLog include + 폐기된 padding 멤버(`m_h_pad`/`m_applying_h_pad`) + 미검증 헤더강제 실험 제거 완료.** → 빌드 clean, push 가능 상태.
- 일반 컨트롤 중 logWrite 사용은 VtListCtrlEx 뿐이었고 정리됨. `Functions.cpp` 는 주석 처리된 `//gLog.write` 한 줄뿐(무해). 그 외 매칭은 전부 멀티미디어(directx/ffmpeg/subtitle)+log 인프라(규칙상 유지).

---

## 8. 동작 원리 참고 (왜 이렇게 어려운가)

native listctrl(report view)은 자체 가로/세로 스크롤·헤더 레이아웃을 강하게 관리하며, 우리가 NC 로 client 를 줄여도 **헤더는 client+5px 로 잡혀** native 스크롤 viewport 가 그 헤더 기준이 된다. overlay 스크롤바(색 커스텀 위해 native 스크롤바를 버림)와 native 의 content 레이아웃이 이 5px 에서 어긋나는 것이 마지막 난점.

---

## 9. 2026-06-16 작업 진행 (집에서 이어서 — 어디까지 했는지)

### 9-1. 이번 세션에 **해결 완료** (Common/CVtListCtrlEx)

1. **세로 끝 항목 잘림 + thumb 튐** — native nPage 가 partial row 포함 ceil 이라 max scroll 1 부족. **OnNcCalcSize 에서 세로바 시 하단 remainder 를 NC 추가 예약(`m_bottom_reserve`)** → itemArea=itemH 배수(ceil==floor) → 마지막 항목 완전 표시. v-bar 높이 +reserve, h-bar 위치 +reserve, OnNcPaint 하단 띠 fill 확장, thumb pin. **검증 OK.**
2. **리사이즈 시 스크롤바 지연** — reserve 로 client 가 itemH 단위로만 변해 sub-row 성장 시 WM_SIZE 미발생 → **`OnWindowPosChanged` 에서 sync 호출**. **OK.**
3. **선택 행 크기/날짜 컬럼 가독성** — 폴더 dim 회색을 `listctrlex_dim_color` sentinel 로(비선택 cr_text_dim / 선택 cr_text_selected). **OK.**
4. **코너 좌상단 흰 사각형(#30)** — OnPaint 의 rcCornerBottom 제거. **OK.**
5. **★리사이즈 중 스크롤바 자체가 안 그려지던 회귀(Endorphin2)★** — 원인: e114ad3 이후 overlay 바가 **부모 dialog 의 child**인데, `CSCThemeDlg::OnSize→Invalidate()`(SCThemeDlg.cpp:670)가 리사이즈마다 dialog 전체를 repaint 해 **바 child 위를 덮음**(WS_CLIPCHILDREN 없으면). **fix: `setup_scrollbar` 에서 `pParent->ModifyStyle(0, WS_CLIPCHILDREN)`**. **검증 OK.**

§9-1 의 1~4 는 commit `5f90861`. 5 + 아래 진단은 이번 미push 분.

### 9-2. **미해결 — 집에서 이어서**

**증상:** Endorphin2 자막편집창(CSubtitleDlg, CSCThemeDlg 파생)에서 **top(1번) 항목이 헤더 바로 아래에 안 붙고 몇 px gap/overlap**. 클릭/스크롤하면 gap↔flush↔overlap 으로 바뀜. 예전부터 있던 재발 버그.

**배제된 가설(반증 완료 — 다시 추측 말 것):**
- header≠line(24/28)? → 아님. Test 를 24/28 로 맞춰도 재현 안 됨.
- layered 창? → 아님. `parentLayered=0` 확인.
- word-wrap/가변 행? → 아님. 단일 라인(사용자 명시).
- → Endorphin2 고유 요소. Test 미재현, Endorphin2 몇 번 만에 재현.

**확인된 사실:** 항목은 native 가 `DefWindowProc(WM_PAINT, memDC)`(OnPaint 1855/1875)로 그림 → gap 은 **native 내부 세로 scroll offset** 이 결정, `GetItemRect` 로만 관측.

**시도했으나 실패:** `OnLvnEndScroll` top 항목 헤더 스냅(`dy=item.top-header`, `m_snapping` 가드). gap 이 스크롤 없이(클릭만)도 나와 LVN_ENDSCROLL 미발화 추정 → 무효.

**다음 단계(측정부터, 추측 금지):** OnPaint 에 `[gap]` 로그 심어둠 — top 항목이 헤더와 어긋날 때 `topIdx/itemTop/itemBot/itemH/header_get/header_native/item0Top/item0H/lineH` 출력. **Endorphin2 에서 gap 재현 → `[gap]` 한 줄 확보 → 숫자로 (a)native scroll offset (b)헤더높이 불일치 (c)항목높이 중 무엇인지 확정 후 수정.**

### 9-3. 현재 남은 진단 로그 (사용자 지시로 **유지** — 최종 정리 시 제거)

- `VtListCtrlEx.cpp` 상단 `#include "../../log/SCLog/SCLog.h"`.
- `[sync]`(sync_scrollbar), `[gap]`(OnPaint).
- `m_snapping` 멤버 + OnLvnEndScroll 스냅(무효였지만 유지).
- **주의:** 일반 컨트롤은 원래 logWrite 포함 push 금지지만, 이번엔 사용자 명시 지시로 진단 로그를 남긴 채 push(집↔회사 연속 디버깅). 버그 확정·수정 후 `[sync]`/`[gap]`/`SCLog include`/`m_snapping`+스냅 모두 제거하고 재push 할 것.

### 9-4. 폐기한 dead-end (재시도 금지)

- layered 가드 barfix / 무조건 barfix(부모 RDW_ALLCHILDREN|UPDATENOW): Test 에 동일 증상 유발 → 제거.
- deferred-first-paint sync(초기 표시 보정): 초기 표시는 원래 정상이라 무의미 → 제거.
