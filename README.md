# ACT_ECU - Actuator Control Unit

ACT_ECU는 Infineon TriCore TC275 마이크로컨트롤러를 기반으로 하는 **액추에이터 제어 유닛(ECU: Electronic Control Unit)** 프로젝트입니다. 이 프로젝트는 다양한 액추에이터와 센서를 제어하기 위한 계층화된 소프트웨어 아키텍처를 제공합니다.

## 📋 프로젝트 개요

- **타겟 MCU**: Infineon AURIX TriCore TC275
- **컴파일러**: TASKING
- **아키텍처**: 다중 코어 (CPU0, CPU1, CPU2)
- **라이센스**: Boost Software License v1.0 (Infineon iLLD)

## 🏗️ 프로젝트 구조

```
ACT_ECU/
├── App/                        # 애플리케이션 계층
│   ├── buzzer/                # 버저 제어
│   ├── dfplayer/              # MP3 플레이어 제어
│   ├── led/                   # LED 제어
│   ├── scheduler/             # 태스크 스케줄러
│   └── servo/                 # 서보 모터 제어
│
├── Driver/                     # 드라이버 계층
│   ├── buzzer/               # 버저 드라이버
│   ├── can/                  # CAN 통신 드라이버
│   ├── dfplayer/             # DFPlayer 드라이버
│   ├── led/                  # LED 드라이버
│   ├── servo/                # 서보 드라이버
│   └── stm/                  # System Timer 드라이버
│
├── Common/                     # 공통 설정 및 타입
│   ├── ActEcu_Cfg.h          # 하드웨어 핀 및 설정
│   ├── ActEcu_Enum.h         # 열거형 및 상태 정의
│   ├── ActEcu_Params.h       # 파라미터 정의
│   └── ActEcu_Types.h        # 데이터 타입 정의
│
├── Configurations/            # 시스템 설정
│   ├── Ifx_Cfg.h             # Infineon 라이브러리 설정
│   └── Debug/                # 디버그 설정
│
├── Libraries/                # 외부 라이브러리
│   ├── iLLD/                 # Infineon Low-Level Driver
│   └── Infra/                # 인프라 라이브러리
│
├── Cpu0_Main.c               # CPU0 메인 함수
├── Cpu1_Main.c               # CPU1 메인 함수
├── Cpu2_Main.c               # CPU2 메인 함수
├── Virtual_Input.h/c         # 가상 입력 제어
│
└── TriCore Debug (TASKING)/  # 빌드 산출물
```

## 🎯 주요 기능

### 액추에이터 제어

- **LED 제어**: 상태 지시 LED 및 외부 조명 제어 (브레이크 램프, 도어락 등)
- **버저**: 경고 및 알림 신호음
- **서보 모터**: PWM 기반 서보 모터 컨트롤
- **DFPlayer**: MP3 오디오 재생 지원

### 통신

- **CAN 버스**: 차량 내 네트워크 통신

### 시스템 관리

- **태스크 스케줄러**: 주기적 작업 실행 관리
- **STM 드라이버**: 시스템 타이머 기반 시간 측정

## 🔧 아키텍처

ACT_ECU는 **3계층 아키텍처**를 따릅니다:

```
┌─────────────────────────────┐
│   Application Layer (App/)  │  - 비즈니스 로직
├─────────────────────────────┤
│   Driver Layer (Driver/)    │  - 하드웨어 추상화
├─────────────────────────────┤
│   HAL (iLLD / Infra)        │  - 저수준 하드웨어 접근
└─────────────────────────────┘
```

### 계층 설명

- **Application**: 상위 수준의 기능 로직 (e.g., LED 패턴 제어)
- **Driver**: 주변장치 제어 인터페이스 (e.g., LED 점등/소등)
- **HAL**: Infineon iLLD를 통한 직접적인 레지스터 제어

## 🚀 빌드 및 실행

### 빌드 환경

- **IDE**: TASKING VX-toolchain (또는 호환 환경)
- **프로젝트 파일**: `TC275_ACT_tb TriCore Debug (TASKING).launch`

### 빌드 방법

```bash
# TASKING IDE에서 프로젝트 빌드
# 또는 터미널에서 Makefile 실행
make -C "TriCore Debug (TASKING)"
```

### 디버그 설정

- 디버그 구성 파일: `TC275_ACT_tb TriCore Debug (TASKING).launch`
- 하드웨어 디버거: TASKING debugger (JTAG)

## 📁 핵심 파일 설명

| 파일                | 설명                               |
| ------------------- | ---------------------------------- |
| `Cpu0_Main.c`       | CPU 0 (메인 코어) 메인 함수 진입점 |
| `Cpu1_Main.c`       | CPU 1 (보조 코어) 메인 함수 진입점 |
| `Cpu2_Main.c`       | CPU 2 (보조 코어) 메인 함수 진입점 |
| `ActEcu_Cfg.h`      | 하드웨어 핀 매핑 및 설정 정의      |
| `ActEcu_Enum.h`     | 상태 열거형 (안전 상태 등)         |
| `App_Scheduler.c/h` | 주기적 태스크 관리                 |
| `Virtual_Input.c/h` | 입력 신호 시뮬레이션/가상화        |

## 🔌 하드웨어 구성

### 핀 매핑 (ActEcu_Cfg.h)

```c
LED1:        IfxPort_P02_6          // 상태 표시 LED
LED2_1-4:    IfxPort_P10_1, P10_3, P10_5, P02_7  // 브레이크 램프
LED3:        IfxPort_P02_0          // 도어락 상태 LED
// 추가 핀 설정은 ActEcu_Cfg.h 참조
```

## 📦 의존성

### Infineon 라이브러리

- **iLLD (Infineon Low-Level Driver)**: TC27D 마이크로컨트롤러 저수준 드라이버
- **Infra**: 플랫폼 인프라 지원

### 컴파일러

- **TASKING VX-toolchain**: TriCore 아키텍처 전용 컴파일러

## 🛠️ 개발 가이드

### 새로운 액추에이터 추가

1. `Driver/` 디렉토리에 드라이버 구현
2. `App/` 디렉토리에 애플리케이션 로직 구현
3. `Common/ActEcu_Cfg.h`에 핀 설정 추가
4. 스케줄러에 주기적 작업 등록 (필요시)

### 핀 설정 수정

- `Common/ActEcu_Cfg.h`: 모든 핀 매핑 정의
- `Libraries/pinmapper.pincfg`: 핀 매핑 시각화 및 검증

## 📝 라이센스

이 프로젝트는 다음 라이센스를 따릅니다:

- **Boost Software License v1.0** (Infineon iLLD 라이브러리)
- **프로젝트 코드**: [프로젝트별 라이센스 정의]

## 📞 참고 자료

- [Infineon AURIX TriCore TC275](https://www.infineon.com/)
- [iLLD Documentation](https://www.infineon.com/)
- [TASKING VX-toolchain](https://www.tasking.com/)

## ✅ 체크리스트

- [✅] 하드웨어 연결 확인
- [✅] 프로젝트 빌드 확인
- [✅] 디버그 세션 테스트
- [✅] 각 액추에이터 기능 테스트

## 최근 업데이트

- LED, 버저, 서보 모터 드라이버 통합
- CAN 통신 모듈 추가
