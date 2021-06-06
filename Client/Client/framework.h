// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once
#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>

using namespace std;

// 너가 정의한 헤더
#include "Define.h"
#include "Enum.h"
#include "Function.h"
#include "Struct.h"

// 맨날 쓸 매니저만 (빌드 개느려짐)
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitmapMgr.h"
#include "RenderMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"