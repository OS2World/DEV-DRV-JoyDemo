# makefile
# Created by IBM WorkFrame/2 MakeMake at 20:03:37 on 17 Jan 1997
#
# The actions included in this make file are:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES: .c .obj 

.all: \
    E:\C_Projects\Joystick_Source\joystick.exe

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Tdp /Ti /Fo"%|dpfF.obj" /C %s

E:\C_Projects\Joystick_Source\joystick.exe: \
    E:\C_Projects\Joystick_Source\joytest.obj
    @echo " Link::Linker "
    icc.exe @<<
     /B" /de"
     /FeE:\C_Projects\Joystick_Source\joystick.exe 
     E:\C_Projects\Joystick_Source\joytest.obj
<<

E:\C_Projects\Joystick_Source\joytest.obj: \
    E:\C_Projects\Joystick_Source\joytest.c \
    {E:\C_Projects\Joystick_Source;$(INCLUDE);}joyos2.h
