// stdafx.h: dołącz plik do standardowych systemowych plików dołączanych,
// lub specyficzne dla projektu pliki dołączane, które są często wykorzystywane, ale
// są rzadko zmieniane
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: W tym miejscu odwołaj się do dodatkowych nagłówków wymaganych przez program
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
