/* File:   main.c
 * Author: Bryan
 * Created on January 21, 2016, 10:21 PM
 * Description: Main source file for LabB1
 * LabB1: Flashing an LED
 */

/* Includes */
#include "main.h"
#include "common.h"
#include "chip8.h"
#include "rom.h"
#include "eeprom.h"

uint16 g_RomOffset;    
Chip8Rom romFont;
Chip8Rom romChip8;
Chip8Rom romScTest;
Chip8Rom romDemoMaze;

Chip8Rom SetRom(char * name, uint16 size)
{
    Chip8Rom r;
    r.name = name;
    r.offset = g_RomOffset;
    r.size = size;
    g_RomOffset += size;
    return r;
}

/* Main program entry point */
int main(void) 
{
    g_RomOffset = 0;
    romFont   = SetRom( "Font",    80  );
    romChip8  = SetRom( "Chip8",   164 );
    romScTest = SetRom( "SC Test", 673 );
    romDemoMaze = SetRom( "Maze",  35);
    
    #if defined(GLCD)
        glcd_init();
        GLCD_TEXT_INIT();
        glcd_clear_buffer();
    #endif
   
    DEBUG_WRITE("Chip8 Start");
    
    Ch8Init();
    
    /* Copy FONT into Chip8 Memory */
    Ch8LoadRom(&romFont, CH8MEM_SYSRESERVED);

    /* Load test rom */
    Ch8LoadRom(&romDemoMaze, CH8MEM_ENTRYPOINT);
    
    delay_routine();
    delay_routine();
    
    Ch8Run();
    
    return 0;
}
