[listctrl]
- 윈도우탐색기와 폰트가 다른 이유는?
- 헤더의 컬럼 너비 조정 시 최소 너비 유지

1.렌더링, 세로 스크롤 정상
2.가로휠, shift+세로휠로도 가로스크롤 정상
3.클릭, 선택 잘 동작되지만 active, inactive 버그 존재
  리스트항목 선택 후 다른 창으로 focus를 옮기면 inactive로 표시되는데 이 때 가로스크롤로 이동해보면 반은 회색, 반은 선택색상.
  정확히 재현 시나리오를 확인하려 했으나 아직 재현 안됨
4.마퀴(rubber-band) 선택 ? 많아도 느리지 않음.
5.키보드 네비게이션 : 많을 때 여전히 느림.
  Ctrl+이동은 포커스만 이동 잘됨.
6.헤더 정렬 잘됨. 너비를 조정할 때 가로스크롤도 동기화 잘됨. 아주 간혹 분리자를 더블클릭했을때 자동 너비조정이 아무 반응 없음.
  헤더의 컬럼 너비 조정 시 최소 너비 지정 필요. 60픽셀?
7.체크박스 정상.
8.트리에서는 주요 보호 폴더 rename이 금지되지만 리스트에서는 주요 파일들임에도 rename이 가능한 버그 있음.
  트리/리스트에서 드라이브 루트는 레이블 변경이 허용되야 함. 드라이브 문자를 변경하는것은 물론 안됨.
9.드래그 시 좌우 스크롤은 아직도 불안. 어떨때는 left, right를 지나가야 스크롤되고
  어떨때는 근처만 가도 잘 스크롤됨.
  드래그해서 세로스크롤이 발생하면 리스트가 제대로 갱신되지 않고 세로스크롤바의 썸도 움직이지 않음.
10.pregress 컬럼 정상 렌더됨. 테마 잘 적용됨. 빈 리스트 / 1행만 / 리사이즈 엣지: 크래시·잔상 없음.
  히스토리 기능 정상.

- shelllist 일 경우 마우스 back button or backspace키로 이전 폴더로 이동

[수정된 내용]
- 항목이 많을 때 드래그 선택 느림

[반영된 클래스]
- CSCStatic
- CSCCombo
- CSCEdit
- CSCListBox
- CSCTreeCtrl
- CVtListCtrEx
- CSCScrollbar
- CSCThemeDlg
- CPathCtrl
- CSCSliderCtrl
- CGdiButton (Push, Check, Radio)

[반영 예정 클래스]
- CMacProgress?
- CRichEditCtrlEx
