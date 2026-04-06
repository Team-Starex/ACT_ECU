################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Driver/Driver_Buzzer.c" \
"../Driver/Driver_Can.c" \
"../Driver/Driver_DfPlayer.c" \
"../Driver/Driver_Led.c" \
"../Driver/Driver_Servo.c" \
"../Driver/Driver_Stm.c" 

COMPILED_SRCS += \
"Driver/Driver_Buzzer.src" \
"Driver/Driver_Can.src" \
"Driver/Driver_DfPlayer.src" \
"Driver/Driver_Led.src" \
"Driver/Driver_Servo.src" \
"Driver/Driver_Stm.src" 

C_DEPS += \
"./Driver/Driver_Buzzer.d" \
"./Driver/Driver_Can.d" \
"./Driver/Driver_DfPlayer.d" \
"./Driver/Driver_Led.d" \
"./Driver/Driver_Servo.d" \
"./Driver/Driver_Stm.d" 

OBJS += \
"Driver/Driver_Buzzer.o" \
"Driver/Driver_Can.o" \
"Driver/Driver_DfPlayer.o" \
"Driver/Driver_Led.o" \
"Driver/Driver_Servo.o" \
"Driver/Driver_Stm.o" 


# Each subdirectory must supply rules for building sources it contributes
"Driver/Driver_Buzzer.src":"../Driver/Driver_Buzzer.c" "Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Driver/Driver_Buzzer.o":"Driver/Driver_Buzzer.src" "Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Driver/Driver_Can.src":"../Driver/Driver_Can.c" "Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Driver/Driver_Can.o":"Driver/Driver_Can.src" "Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Driver/Driver_DfPlayer.src":"../Driver/Driver_DfPlayer.c" "Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Driver/Driver_DfPlayer.o":"Driver/Driver_DfPlayer.src" "Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Driver/Driver_Led.src":"../Driver/Driver_Led.c" "Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Driver/Driver_Led.o":"Driver/Driver_Led.src" "Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Driver/Driver_Servo.src":"../Driver/Driver_Servo.c" "Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Driver/Driver_Servo.o":"Driver/Driver_Servo.src" "Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Driver/Driver_Stm.src":"../Driver/Driver_Stm.c" "Driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.28-workspace/TC275_ACT_ECU/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Driver/Driver_Stm.o":"Driver/Driver_Stm.src" "Driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Driver

clean-Driver:
	-$(RM) ./Driver/Driver_Buzzer.d ./Driver/Driver_Buzzer.o ./Driver/Driver_Buzzer.src ./Driver/Driver_Can.d ./Driver/Driver_Can.o ./Driver/Driver_Can.src ./Driver/Driver_DfPlayer.d ./Driver/Driver_DfPlayer.o ./Driver/Driver_DfPlayer.src ./Driver/Driver_Led.d ./Driver/Driver_Led.o ./Driver/Driver_Led.src ./Driver/Driver_Servo.d ./Driver/Driver_Servo.o ./Driver/Driver_Servo.src ./Driver/Driver_Stm.d ./Driver/Driver_Stm.o ./Driver/Driver_Stm.src

.PHONY: clean-Driver

