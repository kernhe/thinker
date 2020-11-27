
#include "gui.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"


#define CONSOLE_HEIGHT                  219  // Height in pixels of the UI console
#define DEFAULT_SCROLL_AREA             40
#define DEFAULT_SCROLL_MIN              1
#define DEFAULT_SCROLL_MAX              20
#define DEFAULT_LIST_SCROLL_DELTA       1
#define DEFAULT_MOUSE_OVER_TILE_INFO    1

struct ConsoleState {
    const int ScrollArea = DEFAULT_SCROLL_AREA;
    const int ScrollMin = DEFAULT_SCROLL_MIN;
    const int ScrollMax = DEFAULT_SCROLL_MAX;
    const int ListScrollDelta = DEFAULT_LIST_SCROLL_DELTA;
    bool MouseOverTileInfo = DEFAULT_MOUSE_OVER_TILE_INFO;
    POINT ScreenSize;
    POINT WindowSize;
    bool TimersEnabled = false;
    bool Windowed = false;
    bool Minimised = false;
    bool Scrolling = false;
    bool RightButtonDown = false;
    bool ScrollDragging = false;
    double ScrollOffsetX = 0.0;
    double ScrollOffsetY = 0.0;
    POINT ScrollDragPos = {0, 0};
};

ConsoleState CState;

typedef int(__stdcall *START_F)(HINSTANCE, HINSTANCE, LPSTR, int);
typedef int(__thiscall *CCANVAS_CREATE_F)(CCanvas* pthis);
typedef int(__stdcall *WNDPROC_F)(HWND, int, WPARAM, LPARAM);
typedef int(__thiscall *CMAIN_ZOOMPROCESSING_F)(CMain* pthis);
typedef int(__stdcall *PROC_ZOOM_KEY_F)(int iZoomType, int iZero);
typedef int(__thiscall *CMAIN_TILETOPT_F)(CMain* pthis, int iTileX, int iTileY, long* piX, long* piY);
typedef int(__thiscall *CMAIN_MOVEMAP_F)(CMain *pthis, int iXPos, int iYPos, int a4);
typedef int(__thiscall *CMAIN_REDRAWMAP_F)(CMain *pthis, int a2);
typedef int(__thiscall *CMAIN_DRAWMAP_F)(CMain* This, int iOwner, int fUnitsOnly);
typedef int(__thiscall *CMAIN_PTTOTILE_F)(CMain* This, POINT p, long* piTileX, long* piTileY);
typedef int(__thiscall *CINFOWIN_DRAWTILEINFO_F)(CInfoWin* This);
typedef int(__cdecl *PAINTHANDLER_F)(RECT *prRect, int a2);
typedef int(__cdecl *PAINTMAIN_F)(RECT *pRect);
typedef int(__thiscall *CSPRITE_FROMCANVASRECTTRANS_F)(CSprite *This, CCanvas *poCanvas,
    int iTransparentIndex, int iLeft, int iTop, int iWidth, int iHeight, int a8);
typedef int(__thiscall *CCANVAS_DESTROY4_F)(CCanvas *This);
typedef int (__thiscall *CSPRITE_STRETCHCOPYTOCANVAS_F)
    (CSprite *This, CCanvas *poCanvasDest, int cTransparentIndex, int iLeft, int iTop);
typedef int(__thiscall *CSPRITE_STRETCHCOPYTOCANVAS1_F)
    (CSprite *This, CCanvas *poCanvasDest, int cTransparentIndex, int iLeft, int iTop, int iDestScale, int iSourceScale);
typedef int (__thiscall *CSPRITE_STRETCHDRAWTOCANVAS2_F)
    (CSprite *This, CCanvas *poCanvas, int a1, int a2, int a3, int a4, int a7, int a8);
typedef int(__thiscall *CWINBASE_ISVISIBLE_F)(CWinBase *This);
typedef int(__thiscall *CTIMER_STARTTIMER_F)(CTimer *This, int a2, int a3, int iDelay, int iElapse, int uResolution);
typedef int(__thiscall *CTIMER_STOPTIMER_F)(CTimer *This);
typedef int(__thiscall *DRAWCITYMAP_F)(CWinBase *This, int a2);
typedef int(__cdecl *GETFOODCOUNT_F)(int iForFaction, int a2, int iTileX, int iTileY, bool fWithFarm);
typedef int(__cdecl *GETPRODCOUNT_F)(int iForFaction, int a2, int iTileX, int iTileY, bool fWithMine);
typedef int(__cdecl *GETENERGYCOUNT_F)(int iForFaction, int a2, int iTileX, int iTileY, bool fWithSolar);
typedef int(__thiscall *IMAGEFROMCANVAS_F)(CImage *This, CCanvas *poCanvasSource, int iLeft, int iTop, int iWidth, int iHeight, int a7);
typedef int(__cdecl *GETELEVATION_F)(int iTileX, int iTileY);
typedef int(__thiscall *CIMAGE_COPYTOCANVAS2_F)(CImage *This, CCanvas *poCanvasDest, int x, int y, int a5, int a6, int a7);
typedef int(__thiscall *CMAINMENU_ADDSUBMENU_F)(CMainMenu* This, int iMenuID, int iMenuItemID, char *lpString);
typedef int(__thiscall *CMAINMENU_ADDBASEMENU_F)(CMainMenu *This, int iMenuItemID, const char *pszCaption, int a4);
typedef int(__thiscall *CMAINMENU_ADDSEPARATOR_F)(CMainMenu *This, int iMenuItemID, int iSubMenuItemID);
typedef int(__thiscall *CMAINMENU_UPDATEVISIBLE_F)(CMainMenu *This, int a2);
typedef int(__thiscall *CMAINMENU_RENAMEMENUITEM_F)(CMainMenu *This, int iMenuItemID, int iSubMenuItemID, const char *pszCaption);
typedef long(__thiscall *CMAP_GETCORNERYOFFSET_F)(CMap *This, int iTileX, int iTileY, int iCorner);

START_F                        pfncWinMain =                    (START_F                       )0x45F950;
HDC*                           phDC =                           (HDC*                          )0x9B7B2C;
HWND*                          phWnd =                          (HWND*                         )0x9B7B28;
HPALETTE*                      phPallete =                      (HPALETTE*                     )0x9B8178;
HINSTANCE*                     phInstance =                     (HINSTANCE*                    )0x9B7B14;
WNDPROC_F                      pfncWinProc =                    (WNDPROC_F                     )0x5F0650;
CMAIN_ZOOMPROCESSING_F         pfncZoomProcessing =             (CMAIN_ZOOMPROCESSING_F        )0x462980;
CMain*                         pMain =                          (CMain*                        )0x9156B0;
int*                           piMaxTileX =                     (int*                          )0x949870;
int*                           piMaxTileY =                     (int*                          )0x949874;
PROC_ZOOM_KEY_F                pfncProcZoomKey =                (PROC_ZOOM_KEY_F               )0x5150D0;
CMAIN_TILETOPT_F               pfncTileToPoint =                (CMAIN_TILETOPT_F              )0x462F00;
RECT*                          prVisibleTiles =                 (RECT*                         )0x7D3C28;
int*                           piMapFlags =                     (int*                          )0x94988C;
CMAIN_MOVEMAP_F                pfncMoveMap =                    (CMAIN_MOVEMAP_F               )0x46B1F0;
CMAIN_REDRAWMAP_F              pfncRedrawMap =                  (CMAIN_REDRAWMAP_F             )0x46A550;
CMAIN_DRAWMAP_F                pfncDrawMap =                    (CMAIN_DRAWMAP_F               )0x469CA0;
CMAIN_PTTOTILE_F               pfncPtToTile =                   (CMAIN_PTTOTILE_F              )0x463040;
CInfoWin*                      pInfoWin =                       (CInfoWin*                     )0x8C5568;
CINFOWIN_DRAWTILEINFO_F        pfncDrawTileInfo =               (CINFOWIN_DRAWTILEINFO_F       )0x4B8890; // Fixed
CMain**                        ppMain =                         (CMain**                       )0x7D3C3C;
PAINTHANDLER_F                 pfncPaintHandler =               (PAINTHANDLER_F                )0x5F7320;
PAINTMAIN_F                    pfncPaintMain =                  (PAINTMAIN_F                   )0x5EFD20;
CSPRITE_FROMCANVASRECTTRANS_F  pfncSpriteFromCanvasRectTrans =  (CSPRITE_FROMCANVASRECTTRANS_F )0x5E39A0;
CCanvas*                       poLoadingCanvas =                (CCanvas*                      )0x798668;
CCANVAS_DESTROY4_F             pfncCanvasDestroy4 =             (CCANVAS_DESTROY4_F            )0x5D7470;
CSPRITE_STRETCHCOPYTOCANVAS_F  pfncSpriteStretchCopyToCanvas =  (CSPRITE_STRETCHCOPYTOCANVAS_F )0x5E4B9A;
CSPRITE_STRETCHCOPYTOCANVAS1_F pfncSpriteStretchCopyToCanvas1 = (CSPRITE_STRETCHCOPYTOCANVAS1_F)0x5E4B4A;
CSPRITE_STRETCHDRAWTOCANVAS2_F pfncSpriteStretchDrawToCanvas2 = (CSPRITE_STRETCHDRAWTOCANVAS2_F)0x5E3E00;
CSprite*                       pSprResourceIcons =              (CSprite*                      )0x7A72A0;
CWinBase*                      pCityWindow =                    (CWinBase*                     )0x6A7628;
CWinBase*                      pAnotherWindow =                 (CWinBase*                     )0x8A6270;
CWinBase*                      pAnotherWindow2 =                (CWinBase*                     )0x8C6E68;
int*                           pfGameNotStarted =               (int*                          )0x68F21C;
CWINBASE_ISVISIBLE_F           pfncWinIsVisible =               (CWINBASE_ISVISIBLE_F          )0x5F7E90;
CTIMER_STARTTIMER_F            pfncStartTimer =                 (CTIMER_STARTTIMER_F           )0x616350;
CTIMER_STOPTIMER_F             pfncStopTimer =                  (CTIMER_STOPTIMER_F            )0x616780;
DRAWCITYMAP_F                  pfncDrawCityMap =                (DRAWCITYMAP_F                 )0x40F0F0;
int*                           piZoomNum =                      (int*                          )0x691E6C;
int*                           piZoomDenom =                    (int*                          )0x691E70;
int*                           piSourceScale =                  (int*                          )0x696D1C;
int*                           piDestScale =                    (int*                          )0x696D18;
int*                           piResourceExtra =                (int*                          )0x90E998;
int*                           piTilesPerRow =                  (int*                          )0x68FAF0;
CTile**                        paTiles =                        (CTile**                       )0x94A30C;
GETFOODCOUNT_F                 pfncGetFoodCount =               (GETFOODCOUNT_F                )0x4E6E50;
GETPRODCOUNT_F                 pfncGetProdCount =               (GETPRODCOUNT_F                )0x4E7310;
GETENERGYCOUNT_F               pfncGetEnergyCount =             (GETENERGYCOUNT_F              )0x4E7750;
IMAGEFROMCANVAS_F              pfncImageFromCanvas =            (IMAGEFROMCANVAS_F             )0x619710;
GETELEVATION_F                 pfncGetElevation =               (GETELEVATION_F                )0x5919C0;
CIMAGE_COPYTOCANVAS2_F         pfncImageCopytoCanvas2 =         (CIMAGE_COPYTOCANVAS2_F        )0x6233C0;
CMAINMENU_ADDSUBMENU_F         pfncMainMenuAddSubMenu =         (CMAINMENU_ADDSUBMENU_F        )0x5FB100;
CMAINMENU_ADDBASEMENU_F        pfncMainMenuAddBaseMenu =        (CMAINMENU_ADDBASEMENU_F       )0x5FAEF0;
CMAINMENU_ADDSEPARATOR_F       pfncMainMenuAddSeparator =       (CMAINMENU_ADDSEPARATOR_F      )0x5FB160;
CMAINMENU_UPDATEVISIBLE_F      pfncMainMenuUpdateVisible =      (CMAINMENU_UPDATEVISIBLE_F     )0x460DD0;
CMAINMENU_RENAMEMENUITEM_F     pfncMainMenuRenameMenuItem =     (CMAINMENU_RENAMEMENUITEM_F    )0x5FB700;
CMAP_GETCORNERYOFFSET_F        pfncMapGetCornerYOffset =        (CMAP_GETCORNERYOFFSET_F       )0x46FE70;

typedef int(__thiscall *FMapWin_pixel_to_tile)(CMain* This, int x, int y, long* px, long* py);
typedef int(__thiscall *FMapWin_tile_to_pixel)(CMain* This, int x, int y, long* px, long* py);
typedef int(__thiscall *FMapWin_set_center)(CMain* This, int x, int y, int v1);
typedef int(__thiscall *FMapWin_calculate_dim)(CMain* This);
typedef int(__thiscall *FWin_is_visible)(CWinBase* This);
typedef int(__thiscall *FTutWin_draw_arrow)(CWinBase* This);
typedef int(__thiscall *FPlanWin_blink)(CWinBase* This);
typedef int(__thiscall *FStringBox_clip_ids)(CWinBase* This, int len);
typedef int(__thiscall *FStatusWin_on_redraw)(CInfoWin* This);
typedef int(__thiscall *FMapWin_gen_map)(CMain* This, int owner, int units_only);
typedef int(__thiscall *FMapWin_draw_map)(CMain* This, int v1);
typedef int(__stdcall *FWinProc)(HWND, int, WPARAM, LPARAM);
typedef int(__stdcall *FConsole_zoom)(int zoom_type, int v1);
typedef int(__cdecl *FWin_update_screen)(RECT *prRect, int v1);
typedef int(__cdecl *FWin_flip)(RECT *pRect);

FMapWin_pixel_to_tile MapWin_pixel_to_tile = (FMapWin_pixel_to_tile)0x463040;
FMapWin_tile_to_pixel MapWin_tile_to_pixel = (FMapWin_tile_to_pixel)0x462F00;
FMapWin_set_center    MapWin_set_center    = (FMapWin_set_center   )0x46B1F0;
FMapWin_calculate_dim MapWin_calculate_dim = (FMapWin_calculate_dim)0x462980;
FWin_is_visible       Win_is_visible       = (FWin_is_visible      )0x5F7E90;
FTutWin_draw_arrow    TutWin_draw_arrow    = (FTutWin_draw_arrow   )0x4BDEA0;
FPlanWin_blink        PlanWin_blink        = (FPlanWin_blink       )0x48BC20;
FStringBox_clip_ids   StringBox_clip_ids   = (FStringBox_clip_ids  )0x629A70;
FStatusWin_on_redraw  StatusWin_on_redraw  = (FStatusWin_on_redraw )0x4B8890;
FMapWin_gen_map       MapWin_gen_map       = (FMapWin_gen_map      )0x469CA0;
FMapWin_draw_map      MapWin_draw_map      = (FMapWin_draw_map     )0x46A550;
FWinProc              WinProc              = (FWinProc             )0x5F0650;
FConsole_zoom         Console_zoom         = (FConsole_zoom        )0x5150D0;
FWin_update_screen    Win_update_screen    = (FWin_update_screen   )0x5F7320;
FWin_flip             Win_flip             = (FWin_flip            )0x5EFD20;


CMain* MapWin = (CMain*)0x9156B0; // ConsoleParent
CWinBase* TutWin = (CWinBase*)0x8C6E68;
CWinBase* BaseWin = (CWinBase*)0x6A7628;
CWinBase* PlanWin = (CWinBase*)0x834D70;
CWinBase* WorldWin = (CWinBase*)0x8E9F60;
CWinBase* SocialWin = (CWinBase*)0x8A6270;
CWinBase* StringBox = (CWinBase*)0x7CD2EC;
CWinBase* StatusWin = (CWinBase*)0x8C5568;

int* dword_68F21C = (int*)0x68F21C;
int* dword_915620 = (int*)0x915620;
int* dword_939298 = (int*)0x939298;
int* dword_9B2068 = (int*)0x9B2068;
int* dword_9392AC = (int*)0x9392AC;
int* dword_939294 = (int*)0x939294;
int* dword_9392A8 = (int*)0x9392A8;
int* dword_939430 = (int*)0x939430;
int* dword_939434 = (int*)0x939434;
int* dword_939438 = (int*)0x939438;
int* dword_93943C = (int*)0x93943C;
int* dword_9B7AE4 = (int*)0x9B7AE4;


bool base_is_visible(void) {
    return CState.TimersEnabled
        && !*game_not_started
        && Win_is_visible(BaseWin);
}

bool map_is_visible(void) {
    return CState.TimersEnabled
        && !*game_not_started
        && !base_is_visible()
        && !Win_is_visible(SocialWin)
        && !Win_is_visible(TutWin);
}

/*
This maps points from the Client (Game window) coordinate system to the Backbuffer
(Buffer which gets rendered to screen)
*/
void ClientToBackbuffer(POINT* pPt) {
    RECT r;
    if (CState.Windowed && *phWnd) {
        GetClientRect(*phWnd, &r);
        if (r.left < r.right && r.top < r.bottom) {
            pPt->x = (pPt->x - r.left) * CState.ScreenSize.x / (r.right - r.left);
            pPt->y = (pPt->y - r.top) * CState.ScreenSize.y / (r.bottom - r.top);
        }
    }
}

BOOL WINAPI ModGetCursorPos(LPPOINT p) {
    RECT r;
    BOOL fRet;
    fRet = GetCursorPos(p); // Fixed
    if (CState.Windowed) {
        // Have to map the coordinate to the backbuffer if we're windowed.
        GetClientRect(*phWnd, &r);
        ScreenToClient(*phWnd, p);
        fRet = PtInRect(&r, *p);
        ClientToBackbuffer(p);
    }
    return fRet;
}

void mouse_over_tile(POINT* p) {
    static POINT ptLastTile = {0, 0};
    POINT ptTile;

    if (CState.MouseOverTileInfo
    && !pMain->fUnitNotViewMode
    && p->x >= 0 && p->x < CState.ScreenSize.x
    && p->y >= 0 && p->y < (CState.ScreenSize.y - CONSOLE_HEIGHT)
    && MapWin_pixel_to_tile(pMain, p->x, p->y, &ptTile.x, &ptTile.y) == 0
    && memcmp(&ptTile, &ptLastTile, sizeof(POINT)) != 0) {

        pInfoWin->iTileX = ptTile.x;
        pInfoWin->iTileY = ptTile.y;
        StatusWin_on_redraw(pInfoWin);
        memcpy(&ptLastTile, &ptTile, sizeof(POINT));
    }
}

ULONGLONG get_ms_count(void) {
    static LONGLONG llFrequency = 0;
    static ULONGLONG ullLast = 0;
    static ULONGLONG ullHigh = 0;
    ULONGLONG ullRet;
    if (llFrequency == 0 && !QueryPerformanceFrequency((LARGE_INTEGER*)&llFrequency)) {
        llFrequency = -1LL;
    }
    if (llFrequency > 0) {
        QueryPerformanceCounter((LARGE_INTEGER*)&ullRet);
        ullRet *= 1000;
        ullRet /= (ULONGLONG)llFrequency;
    } else if (llFrequency < 0) {
        ullRet = GetTickCount();
        if (ullRet < ullLast) {
            ullHigh += 0x100000000ULL;
        }
        ullLast = ullRet;
        ullRet += ullHigh;
    }
    return ullRet;
}

bool do_scroll(double x, double y) {
    bool fScrolled = false;
    int mx = *map_axis_x;
    int my = *map_axis_y;
    int i;
    int d;
    if (x && pMain->oMap.iMapTilesEvenX + pMain->oMap.iMapTilesOddX < mx) {
        if (x < 0 && (!(*map_toggle_flat) || pMain->oMap.iMapTileLeft > 0)) {
            i = (int)CState.ScrollOffsetX;
            CState.ScrollOffsetX -= x;
            fScrolled = fScrolled || (i != (int)CState.ScrollOffsetX);
            while (CState.ScrollOffsetX >= pMain->oMap.iPixelsPerTileX) {
                CState.ScrollOffsetX -= pMain->oMap.iPixelsPerTileX;
                pMain->oMap.iTileX -= 2;
                if (pMain->oMap.iTileX < 0) {
                    if (*map_toggle_flat) {
                        pMain->oMap.iTileX = 0;
                        pMain->oMap.iTileY &= ~1;
                        CState.ScrollOffsetX = 0;
                    } else {
                        pMain->oMap.iTileX += mx;
                    }
                }
            }
        } else if (x < 0 && (*map_toggle_flat)) {
            fScrolled = true;
            CState.ScrollOffsetX = 0;
        }
        if (x > 0 &&
                (!(*map_toggle_flat) ||
                 pMain->oMap.iMapTileLeft +
                 pMain->oMap.iMapTilesEvenX +
                 pMain->oMap.iMapTilesOddX <= mx)) {
            i = (int)CState.ScrollOffsetX;
            CState.ScrollOffsetX -= x;
            fScrolled = fScrolled || (i != (int)CState.ScrollOffsetX);
            while (CState.ScrollOffsetX <= -pMain->oMap.iPixelsPerTileX) {
                CState.ScrollOffsetX += pMain->oMap.iPixelsPerTileX;
                pMain->oMap.iTileX += 2;
                if (pMain->oMap.iTileX > mx) {
                    if (*map_toggle_flat) {
                        pMain->oMap.iTileX = mx;
                        pMain->oMap.iTileY &= ~1;
                        CState.ScrollOffsetX = 0;
                    } else {
                        pMain->oMap.iTileX -= mx;
                    }
                }
            }
        } else if (x > 0 && (*map_toggle_flat)) {
            fScrolled = true;
            CState.ScrollOffsetX = 0;
        }
    }
    if (y && pMain->oMap.iMapTilesEvenY + pMain->oMap.iMapTilesOddY < my) {
        int iMinTileY = pMain->oMap.iMapTilesOddY - 2;
        int iMaxTileY = my + 4 - pMain->oMap.iMapTilesOddY;
        while (pMain->oMap.iTileY < iMinTileY) {
            pMain->oMap.iTileY += 2;
        }
        while (pMain->oMap.iTileY > iMaxTileY) {
            pMain->oMap.iTileY -= 2;
        }
        d = (pMain->oMap.iTileY - iMinTileY) * pMain->oMap.iPixelsPerHalfTileY - (int)CState.ScrollOffsetY;
        if (y < 0 && d > 0 ) {
            if (y < -d)
                y = -d;
            i = (int)CState.ScrollOffsetY;
            CState.ScrollOffsetY -= y;
            fScrolled = fScrolled || (i != (int)CState.ScrollOffsetY);
            while (CState.ScrollOffsetY >= pMain->oMap.iPixelsPerTileY && pMain->oMap.iTileY - 2 >= iMinTileY) {
                CState.ScrollOffsetY -= pMain->oMap.iPixelsPerTileY;
                pMain->oMap.iTileY -= 2;
            }
        }
        d = (iMaxTileY - pMain->oMap.iTileY + 1) * pMain->oMap.iPixelsPerHalfTileY + (int)CState.ScrollOffsetY;
        if (y > 0 && d > 0) {
            if (y > d)
                y = d;
            i = (int)CState.ScrollOffsetY;
            CState.ScrollOffsetY -= y;
            fScrolled = fScrolled || (i != (int)CState.ScrollOffsetY);
            while (CState.ScrollOffsetY <= -pMain->oMap.iPixelsPerTileY && pMain->oMap.iTileY + 2 <= iMaxTileY) {
                CState.ScrollOffsetY += pMain->oMap.iPixelsPerTileY;
                pMain->oMap.iTileY += 2;
            }
        }
    }
    if (fScrolled) {
        MapWin_draw_map(pMain, 0);
        Win_update_screen(NULL, 0);
        Win_flip(NULL);
        ValidateRect(*phWnd, NULL);
    }
    return fScrolled;
}

void check_scroll() {
    POINT p;
    if (CState.Scrolling || (!ModGetCursorPos(&p) && !(CState.ScrollDragging && CState.RightButtonDown))) {
        return;
    }
    CState.Scrolling = true;
    int w = CState.ScreenSize.x;
    int h = CState.ScreenSize.y;
    static ULONGLONG ullDeactiveTimer = 0;
    ULONGLONG ullOldTickCount = 0;
    ULONGLONG ullNewTickCount = 0;
    BOOL fScrolled;
    BOOL fScrolledAtAll = false;
    BOOL fLeftButtonDown = (GetAsyncKeyState(VK_LBUTTON) < 0);
    int iScrollArea = CState.ScrollArea * CState.ScreenSize.x / 1024;

    if (CState.RightButtonDown && GetAsyncKeyState(VK_RBUTTON) < 0) {
        if (labs((long)hypot((double)(p.x-CState.ScrollDragPos.x), (double)(p.y-CState.ScrollDragPos.y))) > 2.5) {
            CState.ScrollDragging = true;
            SetCursor(LoadCursor(0, IDC_HAND));
        }
    }
    CState.ScrollOffsetX = pMain->oMap.iMapPixelLeft;
    CState.ScrollOffsetY = pMain->oMap.iMapPixelTop;
    ullNewTickCount = get_ms_count();
    ullOldTickCount = ullNewTickCount;
    debug("scroll_check %d %d %d\n", CState.Scrolling, (int)CState.ScrollDragPos.x, (int)CState.ScrollDragPos.y);
    do {
        double dTPS = -1;
        double dx = 0;
        double dy = 0;
        fScrolled = false;
        if (CState.ScrollDragging && CState.RightButtonDown) {
            fScrolled = true;
            dx = CState.ScrollDragPos.x - p.x;
            dy = CState.ScrollDragPos.y - p.y;
            memcpy(&CState.ScrollDragPos, &p, sizeof(POINT));

        } else if (ullNewTickCount - ullDeactiveTimer > 100 && !CState.ScrollDragging) {
            double dMin = (double)CState.ScrollMin;
            double dMax = (double)CState.ScrollMax;
            double dArea = (double)iScrollArea;
            if (p.x <= iScrollArea && p.x >= 0) {
                fScrolled = true;
                dTPS = dMin + (dArea - (double)p.x) / dArea * (dMax - dMin);
                dx = (double)(ullNewTickCount - ullOldTickCount) * dTPS * (double)pMain->oMap.iPixelsPerTileX / -1000.0;

            } else if ((w - p.x) <= iScrollArea && w >= p.x) {
                fScrolled = true;
                dTPS = dMin + (dArea - (double)(w - p.x)) / dArea * (dMax - dMin);
                dx = (double)(ullNewTickCount - ullOldTickCount) * dTPS * (double)pMain->oMap.iPixelsPerTileX / 1000.0;
            }
            if (p.y <= iScrollArea && p.y >= 0) {
                fScrolled = true;
                dTPS = dMin + (dArea - (double)p.y) / dArea * (dMax - dMin);
                dy = (double)(ullNewTickCount - ullOldTickCount) * dTPS * (double)pMain->oMap.iPixelsPerTileY / -1000.0;

            } else if (h - p.y <= iScrollArea && h >= p.y &&
                       (p.x <= (CState.ScreenSize.x - 1024) / 2 ||
                        p.x >= (CState.ScreenSize.x - 1024) / 2 + 1024 ||
                        h - p.y < (CState.Windowed ? 8 : 5) * CState.ScreenSize.y / 756)) {
                fScrolled = true;
                dTPS = dMin + (dArea - (double)(h - p.y)) / dArea * (dMax - dMin);
                dy = (double)(ullNewTickCount - ullOldTickCount) * dTPS * (double)pMain->oMap.iPixelsPerTileY / 1000.0;
            }
        }
        if (fScrolled) {
            ullOldTickCount = ullNewTickCount;
            if (do_scroll(dx, dy)) {
                fScrolledAtAll = true;
                Sleep(5);
            } else {
                Sleep(5);
            }
            ullNewTickCount = get_ms_count();
            if (CState.RightButtonDown) {
                CState.RightButtonDown = (GetAsyncKeyState(VK_RBUTTON) < 0);
            }
            debug("scroll_move  x=%d y=%d scx=%.4f scy=%.4f dx=%.4f dy=%.4f dTPS=%.4f\n",
                (int)p.x, (int)p.y, CState.ScrollOffsetX, CState.ScrollOffsetY, dx, dy, dTPS);
        }

    } while (fScrolled && (ModGetCursorPos(&p) || (CState.ScrollDragging && CState.RightButtonDown)));

    // TODO: determine the purpose of this code
    if (fScrolledAtAll) {
        pMain->oMap.field_21A44 = 1;
        MapWin_set_center(pMain, pMain->oMap.iTileX, pMain->oMap.iTileY, 1);
        pMain->oMap.field_21A44 = 0;
        for (int i = 1; i < 8; i++) {
            if (ppMain[i] && ppMain[i]->oMap.field_1DD74 &&
                    (!fLeftButtonDown || ppMain[i]->oMap.field_1DD80) &&
                    ppMain[i]->oMap.iMapTilesOddX + ppMain[i]->oMap.iMapTilesEvenX < *map_axis_x) {
                MapWin_set_center(ppMain[i], pMain->oMap.iTileX, pMain->oMap.iTileY, 1);
            }
        }
        if (CState.ScrollDragging) {
            ullDeactiveTimer = ullNewTickCount;
        }
    }
    mouse_over_tile(&p);
    CState.Scrolling = false;
    fflush(debug_log);
}

LRESULT __stdcall ModWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static int iDeltaAccum = 0;
    bool fHasFocus = (GetFocus() == *phWnd);
    POINT p;

    if (msg == WM_MOUSEWHEEL && fHasFocus) {
        debug("WM_MOUSEWHEEL %d\n", pMain->oMap.iZoomFactor);
        int iDelta = GET_WHEEL_DELTA_WPARAM(wParam) + iDeltaAccum;
        iDeltaAccum = iDelta % WHEEL_DELTA;
        iDelta /= WHEEL_DELTA;
        bool zoom_in = (iDelta >= 0);
        iDelta = labs(iDelta);

        if (map_is_visible() && *map_axis_x) {
            int iZoomType = (zoom_in ? 515 : 516);
            for (int i = 0; i < iDelta; i++) {
                if (pMain->oMap.iZoomFactor > -8 || zoom_in) {
                    Console_zoom(iZoomType, 0);
                }
            }
        } else {
            int iKey = (zoom_in ? VK_UP : VK_DOWN);
            iDelta *= CState.ListScrollDelta;
            for (int i = 0; i < iDelta; i++) {
                PostMessage(hwnd, WM_KEYDOWN, iKey, 0);
                PostMessage(hwnd, WM_KEYUP, iKey, 0);
            }
            return 0;
        }

    } else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
        if (!map_is_visible() || !fHasFocus) {
            CState.RightButtonDown = false;
            CState.ScrollDragging = false;
            WinProc(hwnd, msg, wParam, lParam);

        } else if (msg == WM_RBUTTONDOWN) {
            CState.RightButtonDown = true;
            ModGetCursorPos(&p);
            memcpy(&CState.ScrollDragPos, &p, sizeof(POINT));

        } else if (msg == WM_RBUTTONUP) {
            CState.RightButtonDown = false;
            if (CState.ScrollDragging) {
                CState.ScrollDragging = false;
                SetCursor(LoadCursor(0, IDC_ARROW));
            } else {
                WinProc(hwnd, WM_RBUTTONDOWN, wParam | MK_RBUTTON, lParam);
                WinProc(hwnd, WM_RBUTTONUP, wParam, lParam);
            }
        } else if (CState.RightButtonDown) {
            check_scroll();
        } else {
            WinProc(hwnd, msg, wParam, lParam);
        }
        
    } else if (msg == WM_CHAR && wParam == 'r' && GetAsyncKeyState(VK_MENU) < 0) {
        debug("WM_CHAR alt+r\n");
        CState.MouseOverTileInfo = !CState.MouseOverTileInfo;
    } else if (DEBUG && msg == WM_CHAR && wParam == 'd' && GetAsyncKeyState(VK_MENU) < 0) {
        debug("WM_CHAR alt+d\n");
        conf.debug_mode = !conf.debug_mode;
        if (conf.debug_mode) {
            *game_state |= STATE_DEBUG_MODE;
        } else {
            *game_state &= ~STATE_DEBUG_MODE;
        }
        MapWin_draw_map(pMain, 0);
        InvalidateRect(hwnd, NULL, false);
    } else {
        return WinProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

ATOM WINAPI ModRegisterClassA(WNDCLASS* pstWndClass) {
    pstWndClass->lpfnWndProc = ModWinProc;
    return RegisterClassA(pstWndClass);
}

int __thiscall draw_map(CMain* This, int iOwner, int fUnitsOnly) {

    if (This == pMain) {
        debug("draw_map %d %.4f %.4f\n", CState.Scrolling, CState.ScrollOffsetX, CState.ScrollOffsetY);
        // Save these values to restore them later
        int iMapPixelLeft = This->oMap.iMapPixelLeft;
        int iMapPixelTop = This->oMap.iMapPixelTop;
        int iMapTileLeft = This->oMap.iMapTileLeft;
        int iMapTileTop = This->oMap.iMapTileTop;
        int iMapTilesOddX = This->oMap.iMapTilesOddX;
        int iMapTilesOddY = This->oMap.iMapTilesOddY;
        int iMapTilesEvenX = This->oMap.iMapTilesEvenX;
        int iMapTilesEvenY = This->oMap.iMapTilesEvenY;
        // These are just aliased to save typing and are not modified
        int mx = *map_axis_x;
        int my = *map_axis_y;

        if (iMapTilesOddX + iMapTilesEvenX < mx && !(*map_toggle_flat)) {
            if (iMapPixelLeft > 0) {
                This->oMap.iMapPixelLeft -= This->oMap.iPixelsPerTileX;
                This->oMap.iMapTileLeft -= 2;
                This->oMap.iMapTilesEvenX++;
                This->oMap.iMapTilesOddX++;
                if (This->oMap.iMapTileLeft < 0)
                    This->oMap.iMapTileLeft += mx;
            } else if (iMapPixelLeft < 0 ) {
                This->oMap.iMapTilesEvenX++;
                This->oMap.iMapTilesOddX++;
            }
        }
        if (iMapTilesOddY + iMapTilesEvenY < my) {
            if (iMapPixelTop > 0) {
                This->oMap.iMapPixelTop -= This->oMap.iPixelsPerTileY;
                This->oMap.iMapTileTop -= 2;
                This->oMap.iMapTilesEvenY++;
                This->oMap.iMapTilesOddY++;
            } else if (iMapPixelTop < 0) {
                This->oMap.iMapTilesEvenY++;
                This->oMap.iMapTilesOddY++;
            }
        }
        MapWin_gen_map(This, iOwner, fUnitsOnly);
        // Restore This's original values
        This->oMap.iMapPixelLeft = iMapPixelLeft;
        This->oMap.iMapPixelTop = iMapPixelTop;
        This->oMap.iMapTileLeft = iMapTileLeft;
        This->oMap.iMapTileTop = iMapTileTop;
        This->oMap.iMapTilesOddX = iMapTilesOddX;
        This->oMap.iMapTilesOddY = iMapTilesOddY;
        This->oMap.iMapTilesEvenX = iMapTilesEvenX;
        This->oMap.iMapTilesEvenY = iMapTilesEvenY;
    } else {
        MapWin_gen_map(This, iOwner, fUnitsOnly);
    }
    return 0;
}

int __thiscall zoom_process(CMain* This) {
    static POINT ptOldTile = {-1, -1};
    POINT ptOldCenter;
    POINT ptNewCenter;
    POINT ptNewTile;
    POINT ptScale;
    int iOldZoom;
    int dx, dy;
    bool fx, fy;
//    int w = ((CWinBuffed*)((int)This + (int)This->oMap.vtbl->iOffsetofoClass2))->oCanvas.stBitMapInfo.bmiHeader.biWidth;
//    int h = -((CWinBuffed*)((int)This + (int)This->oMap.vtbl->iOffsetofoClass2))->oCanvas.stBitMapInfo.bmiHeader.biHeight;

    if (This == pMain) {
        debug("zoom_process %d %.4f %.4f\n",  CState.Scrolling, CState.ScrollOffsetX, CState.ScrollOffsetY);
        iOldZoom = This->oMap.iLastZoomFactor;
        ptNewTile.x = This->oMap.iTileX;
        ptNewTile.y = This->oMap.iTileY;
        fx = (ptNewTile.x == ptOldTile.x);
        fy = (ptNewTile.y == ptOldTile.y);
        memcpy(&ptOldTile, &ptNewTile, sizeof(POINT));
        MapWin_tile_to_pixel(This, ptNewTile.x, ptNewTile.y, &ptOldCenter.x, &ptOldCenter.y);
        MapWin_calculate_dim(This);

        if (CState.Scrolling) {
            This->oMap.iMapPixelLeft = (int)CState.ScrollOffsetX;
            This->oMap.iMapPixelTop = (int)CState.ScrollOffsetY;
        } else if (iOldZoom != -9999) {
            ptScale.x = This->oMap.iPixelsPerTileX;
            ptScale.y = This->oMap.iPixelsPerTileY;
            MapWin_tile_to_pixel(This, ptNewTile.x, ptNewTile.y, &ptNewCenter.x, &ptNewCenter.y);
            dx = ptOldCenter.x - ptNewCenter.x;
            dy = ptOldCenter.y - ptNewCenter.y;
            if (!This->oMap.iMapPixelLeft && fx && dx > -ptScale.x * 2 && dx < ptScale.x * 2) {
                This->oMap.iMapPixelLeft = dx;
            }
            if (!This->oMap.iMapPixelTop && fy && dy > -ptScale.y * 2 && dy < ptScale.y * 2
            && (dy + *screen_height) / ptScale.y < (*map_axis_y - This->oMap.iMapTileTop) / 2) {
                This->oMap.iMapPixelTop = dy;
            }
        }
    } else {
        MapWin_calculate_dim(This);
    }
    return 0;
}

int __cdecl blink_timer() {
    if (!*dword_68F21C) {
        if (!*dword_915620) {
            if (Win_is_visible(BaseWin)) {
                return TutWin_draw_arrow(TutWin);
            }
            if (Win_is_visible(SocialWin)) {
                return TutWin_draw_arrow(TutWin);
            }
            PlanWin_blink(PlanWin);
            StringBox_clip_ids(StringBox, 150);

            if ((!*dword_939298 && (!*multiplayer_active || !(*game_state & STATE_UNK_2))) || *dword_9B2068) {
                *dword_9392AC = 0;
                return 0;
            }
            if (*dword_939294 || (*multiplayer_active && *game_state & STATE_UNK_2)) {
                *dword_9392A8 = !*dword_9392A8;
                draw_cursor();
                bool mouse_btn_down = GetAsyncKeyState(VK_LBUTTON) < 0;

                if ((int)*phInstance == GetWindowLongA(GetFocus(), GWL_HINSTANCE) && !Win_is_visible(TutWin)) {
                    if (*dword_939430 != -1 && *dword_939434 != -1 && *dword_939438 != -1 && *dword_93943C != -1) {
                        if (*game_settings & 0x1000 || mouse_btn_down || *dword_9B7AE4 != 0) {

                            CState.ScreenSize.x = *screen_width;
                            CState.ScreenSize.y = *screen_height;
                            CState.TimersEnabled = true;
                            check_scroll();
                        }
                    }
                }
            }
        }
    }
    return 0;
}


#pragma GCC diagnostic pop
