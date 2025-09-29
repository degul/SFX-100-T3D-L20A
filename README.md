# SimFeedback-T3D-L20A
SFX-100 AC Servo Motor 80AST-A1C02430




## Servo Motor wiring diagram

<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/servo_1.png" alt="" width="700">

` L1 / L2 = main power input terminal 220v  `<br>
` U / V / W / PE = power cable  `<br>




## SimFeedback + Servo 80AST Pins

![](https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/pins_1.png)


## Parameters

` P-006 ; 25 `<br>
` P-007 ; 30 `<br>
` P-019 ; 60 `<br>
` P-021 ; 20 `<br>
` P-029 ; 16 = 100mm, 32 = 200mm stroke limit `<br>
` P-040 ; 30 `<br>
` P-098 ; 1 (Force Enable) (비상버튼 사용시; 0)`<br>

E-set -> done

<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/parameter_1.png" alt="" width="600">
<!-- <img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/parameter_2.png" alt="" width="600"> -->


## SFX-100 

<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/sfx-100.png" alt="" height="5uu00">


## Assembly parts

| Part | Type | EA | link | 
| --- | --- | --- | --- |
| Servo Motor | HLTNC T3D-L20A-RABN 750W 2.4N | 4 | https://www.aliexpress.com/item/1005004869497167.html |
| Coupling | 40X50-10X19 | 4 | |
| FK12 |  | 4 | |
| Rubber Ring | OD30mm CS4mm | 4 | |
| SFU 1605 | 250mm | 4 | |
| Hollow Shaft | OD30mm, ID20mm, 300mm | 4 | https://www.aliexpress.com/item/1005003847058846.html |
| LMEK30UU |  | 4 | https://www.aliexpress.com/item/1005003773456962.html |
| Profile 100x100 | | | https://www.aliexpress.com/item/1005002770599016.html |
| Grub Screws M8 | | | https://www.aliexpress.com/item/1005002797059381.html | 

| Bolt | Length | EA |
| --- | --- | --- |
| M8 | 40mm | 32 |
| M6 | 110mm | 16 |
| M6 | 45mm | 16 |
| M5 | 30mm | 24 |
| M4 | 25mm | 16 |


| Spring Washer | EA |
| --- | --- |
| M8 | 32 |
| M6 | 16 |
| M5 | 24 |
| M4 | 16 | 


| Nut | EA |
| --- | --- |  
| M6 | 16 |





## 3D Printing

bump stop / slider 0.4mm 노즐 출력 (정밀성)

SFX-100 부품을 100시간 이내로 출력하는 방법
0.6mm 노즐 출력 세팅
| 설정 항목           | 권장 값                   | 비고                 |
| --------------- | ---------------------- | ------------------ |
| 노즐 직경           | **0.6mm**              | 전체 프로필 변경 필수       |
| 레이어 높이          | **0.4mm**              | 표준 출력 속도 대비 2배 두꺼움 |
| 최소 레이어 높이       | 0.2mm                  | 가변 레이어 적용 시 사용     |
| 첫 레이어 높이        | **0.2mm**              | 접착력 향상             |
| Perimeter(외벽 수) | **5개**                 | 충분한 강도 확보          |
| 상/하단 레이어        | 8개 *(가변 레이어 사용 시 12개)* | 표면 품질 유지           |
| 인필 밀도           | **25%**, Grid 패턴       | 강도 ↑               |
| 20층마다 솔리드 인필    | 활성화                    | 구조 안정성 강화          |
| Perimeter 시작점   | Random                 | Z-Seam 숨김          |
| 브림              | **5mm**, 1층            | 뒤틀림 방지             |
| 
가변 레이어 높이       | 상단 3mm → **0.2mm**     | 표면 품질 개선(선택 사항)    |


참고 - https://www.xsimulator.net/community/threads/diablo2112s-4-axis-sfx-100-build.13571/page-3#post-185076



## Wiring

<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/ac_line.png" alt="">



## Surge

<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/surge_HGW20CA.png" alt="">
<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/HGW20CC_DIM.png" alt="">

<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/20250925_132918.png" alt="">


-----------------------------------------

<!-- 
## monitor

<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/monitor_cockpit.png" alt="">

-->

## 참고 링크

https://opensfx.com/

https://github.com/SimFeedback/SimFeedback-AC-Servo

https://github.com/SHWotever/SimHubMotionPresets

https://opensfx.com/2019/04/09/sfx-100-shield/

https://github.com/Pyronious/SFX-100-Breakout-Board/tree/master/Group%20Buy%20Edition/Gerber%20Files

https://forum.virtualracing.org/threads/3dof-motion-fuer-1000eur-bauen-geht-das.144073/



## 참고 문서

https://cnc-tehnologi.ru/files/t3d_servo_ENpdf.pdf

https://www.hlt-cnc.com/uploads/38006/files/T3D-Full-manual-V2.3_-English-version.pdf


<img src="https://github.com/degul/SimFeedback-T3D-L20A/raw/main/images/mm.png" alt="">

