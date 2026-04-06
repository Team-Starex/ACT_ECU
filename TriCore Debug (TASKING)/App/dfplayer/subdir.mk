################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../App/dfplayer/App_DfPlayer.c" 

COMPILED_SRCS += \
"App/dfplayer/App_DfPlayer.src" 

C_DEPS += \
"./App/dfplayer/App_DfPlayer.d" 

OBJS += \
"App/dfplayer/App_DfPlayer.o" 


# Each subdirectory must supply rules for building sources it contributes
"App/dfplayer/App_DfPlayer.src":"../App/dfplayer/App_DfPlayer.c" "App/dfplayer/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_tb/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"App/dfplayer/App_DfPlayer.o":"App/dfplayer/App_DfPlayer.src" "App/dfplayer/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-App-2f-dfplayer

clean-App-2f-dfplayer:
	-$(RM) ./App/dfplayer/App_DfPlayer.d ./App/dfplayer/App_DfPlayer.o ./App/dfplayer/App_DfPlayer.src

.PHONY: clean-App-2f-dfplayer

