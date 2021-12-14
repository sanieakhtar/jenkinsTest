################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../28004x_cla_flash_lnk.cmd \
../28004x_dcsm_lnk.cmd \
../f28004x_headers_nonbios.cmd 

CLA_SRCS += \
../inv_cla.cla 

LIB_SRCS += \
../f28004x_driverlib/driverlib/f28004x/driverlib/ccs/Debug/driverlib.lib 

C_SRCS += \
../f28004x_globalvariabledefs.c \
../fullbridge.c \
../main.c 

CLA_DEPS += \
./inv_cla.d 

C_DEPS += \
./f28004x_globalvariabledefs.d \
./fullbridge.d \
./main.d 

OBJS += \
./f28004x_globalvariabledefs.obj \
./fullbridge.obj \
./inv_cla.obj \
./main.obj 

OBJS__QUOTED += \
"f28004x_globalvariabledefs.obj" \
"fullbridge.obj" \
"inv_cla.obj" \
"main.obj" 

C_DEPS__QUOTED += \
"f28004x_globalvariabledefs.d" \
"fullbridge.d" \
"main.d" 

CLA_DEPS__QUOTED += \
"inv_cla.d" 

C_SRCS__QUOTED += \
"../f28004x_globalvariabledefs.c" \
"../fullbridge.c" \
"../main.c" 


