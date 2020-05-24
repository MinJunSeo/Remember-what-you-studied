# Run level
  
Linux의 부팅 순서는 우선 다음과 같다.  
  
1) BIOS (Basic Input Output System)  
    소프트웨어를 돌리기 적절한 환경인지 확인한다. (메모리, 그래픽 카드 등...)  
  
2) MBR (Master Boot Record)  
    S/W 로드를 위해 디스크에 예약되어 있는 공간을 말한다.  
    요즘은 OS의 다중 설치가 많아져 OS 선택기인 LILO나 GRUB가 자리를 차지한다.  
  
3) Kernal  
    선택된 OS의 커널이 로드하면서 초기화 과정을 거친다.  
    그 과정에서 process number 1(PID=1)이 된다.  
    그 이후로는 초기화 과정에 필요한 프로그램들이 로딩 된다.
  
이후 Linux는 런 레벨을 검사하여 적절한 조치를 취한다. Run level(런 레벨)이란 시스템 관리의 용이함을 위해 서비스의 실행을 단계별로 구분하여 실행하는 것을 말한다. 총 0 ~ 6까지의 level이 있다.  
  
기본적으로 프로그램이 돌아가거나 시작될 때 run level을 확인하고 컴퓨터가 적절히 시도하지만 프로그래머가 원한다면 직접 run level을 바로 적용시킬 수도 있다. 그때 필요한 명령은 다음과 같다.  
  
	sudo init run_level
  
run_level에 적절한 숫자를 전달하면 해당 숫자에 맞는 run level이 실행된다.  
  
각 run level의 의미는 다음과 같다.  
  
number | name | mean
-------|------|-------
0 | halt | 시스템 종료
1 | Single user mode | 시스템 복원 모드라고도 불린다. 기본적으로 관리자 권한의 쉘을 얻는다.
2 | Multiuser mode, without NFS | NFS(Network File System)을 지원하지 않는 다중 사용자 모드
3 | Full multiuser mode | 일반적인 셀 기반의 인터페이스를 가진 다중 사용자 모드
4 | unused | 쓰이지 않는다. 임의로 정해서 사용할 수 있는 레벨
5 | X11 | 기본적으로 run level 3과 동일하지만 **그래픽 유저 모드**라는 차이가 있다.
6 | reboot | 시스템 재부팅
  
