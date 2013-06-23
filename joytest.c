// SpiceWare sample source for the reading of joysticks.
// by Darrell Spice Jr.         January 18, 1997

#define INCL_DOSFILEMGR         // include needed for DosOpen call
#define INCL_DOSDEVICES         // include needed for DosDevIOCtl call
#define INCL_DOSDEVIOCTL        // include needed for DosDevIOCtl call
#include <os2.h>
#include <stdio.h>              // included needed for printf support

#include "joyos2.h"

main()
{
   HFILE hGame;     // game port file handle
   ULONG action;    // return value from DosOpen
   APIRET rc;       // return code
   GAME_STATUS_STRUCT gameStatus; // joystick readings
   ULONG dataLen;                 // length of gameStatus

   // open up the game port for access.
   if ((rc = DosOpen(GAMEPDDNAME, &hGame, &action, 0, FILE_READONLY, FILE_OPEN,
        OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL)) != 0)
   {
     printf("Unable to open game port, rc: %d\n", rc);
     return 4;
   }

   for (;;)     // loop until user presses control-c to cancel
   {
      // read the joystick values
      dataLen = sizeof(gameStatus);
      rc = DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS, NULL, 0, NULL, &gameStatus, dataLen, &dataLen);
      if (rc != 0)
     {
         printf("Game Status return code of %d\n",rc);
         break;
     }

     // display the joystick values
     printf("joy1 X: %3d Y: %3d A: %2x B: %2X    joy2 X: %3d Y: %3d A: %2x B: %2x\n",
             gameStatus.curdata.A.x,                       // joystick A x position
             gameStatus.curdata.A.y,                       //            y position
             ((gameStatus.curdata.butMask & 0x10) / 0x10), //            fire button A
             ((gameStatus.curdata.butMask & 0x20) / 0x20), //            fire button B

             gameStatus.curdata.B.x,                       // joystick B x position
             gameStatus.curdata.B.y,                       //            y position
             ((gameStatus.curdata.butMask & 0x40) / 0x40), //            fire button A
             ((gameStatus.curdata.butMask & 0x80) / 0x80));//            fire button B
   }
   return 0;
}
