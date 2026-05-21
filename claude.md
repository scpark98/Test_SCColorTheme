@../../Common/claude.md

# Test_SCColorTheme

`D:\1.Projects_C++\Common` 의 SC* 시리즈 커스텀 컨트롤들이 각 color theme (default / white / gray / dark_gray / dark / linkmemine / linkmemine_se / anysupport / helpu / pcanypro) 에서 *시각적으로 어떻게 렌더링되는지* 확인하기 위한 테스트 다이얼로그.

## 용도

- 새 color theme 추가 또는 기존 theme 색상 조정 시 — 모든 SC* 컨트롤이 해당 theme 에서 자연스럽게 보이는지 한 화면에서 확인.
- 컨트롤 자체 (`set_color_theme(int)` / `set_color_theme(const CSCColorTheme&)`) 의 theme 적용 로직 회귀 검증.
- `CSCColorTheme::copy_colors_from` 전파 + default theme 재진입 (control kind 기반 cr_back 분기) 같은 *theme 전파 메커니즘* 의 시각적 점검.

## 핵심 동작 원칙 — 컨트롤별 색 *지정 없음*

이 dlg 의 모든 컨트롤은 **개별 색을 지정하지 않는다**. 오직 `m_theme` 객체 하나를 자식들에 전파하는 것만으로 모든 컨트롤이 theme 에 맞게 자동 채색되는 것이 *정상* 동작.

- `m_btn_ok.set_text_color(blue)` / `set_back_color(...)` 같은 per-control color 호출은 **이 프로젝트에서는 절대 추가하지 말 것**.
- theme 가 *바뀌었는데 어떤 컨트롤만 색이 어긋난다* 면 — 그 컨트롤의 `set_color_theme(const CSCColorTheme&)` 구현 (Common 쪽) 이 버그. 본 프로젝트에서 개별 색 override 로 회피하지 말고 *Common 컨트롤을 고친다*.
- 즉 본 dlg 는 "theme 만 갈아끼우면 끝" 이라는 사용자 의도된 *unstyled* 호출 패턴을 강제 보여주는 reference dlg. 새 컨트롤을 추가할 때도 `set_color_theme(m_theme)` 한 줄만 추가.

## 배치된 컨트롤

dlg 안에서 한눈에 비교되도록 다음 컨트롤이 모두 배치되어 있다:
- `CSCThemeDlg` (자기 자신 — borderless + sys buttons + titlebar 색)
- `CSCSystemButtons` (min/max/close)
- `CSCComboBox` (theme 선택 + 동작 확인)
- `CSCEdit`, `CSCStaticEdit` (편집 컨트롤)
- `CSCListBox`, `CSCTreeCtrl`, `CVtListCtrlEx` (목록/트리/리포트)
- `CGdiButton` (확인/취소 — Win11 face 산출)
- `CPathCtrl` (탐색기 주소표시줄 스타일)
- `CSCMessageBox` (modeless — 태그 텍스트 포함)

## 작업 흐름

테마 컬러 / 컨트롤 렌더링을 손볼 때:
1. **Common 쪽 변경 (실제 fix)** — `D:\1.Projects_C++\Common` 의 해당 컨트롤·`colors.cpp` 직접 편집.
2. **본 프로젝트로 빌드 후 GUI 확인** — 콤보로 theme 전환하며 시각 검증 (§5B: log 만으로 단정 금지).
3. **테스트용 추가 컨트롤·시연 코드** 가 필요하면 `Test_SCColorThemeDlg.cpp` 만 수정. Common 은 건들지 말 것.

## 관련 메모

- m_msgbox 는 modeless 로 `OnInitDialog` 에서 한 번 생성·표시 — 콤보 변경 시 자동으로 `set_color_theme(m_theme, true)` 동기화.
- `CSCColorTheme` 전파 시 `copy_colors_from` 이 default 인 경우 receiver 의 `m_parent` 기준으로 `set_color_theme(default)` 재호출 — List/Tree/Edit 류는 COLOR_WINDOW, 그 외는 COLOR_BTNFACE. 본 프로젝트에서 이 메커니즘 검증 가능.
- `m_msgbox.set_color_theme(m_theme)` 의 직접 호출 결과와 dialog → control 전파 결과가 같은 톤으로 보이는지 확인하는 게 본 dlg 의 주요 회귀 포인트.
