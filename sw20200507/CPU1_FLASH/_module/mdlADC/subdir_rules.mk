################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
_module/mdlADC/%.obj: ../_module/mdlADC/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/home/cicdserver/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -O2 --opt_for_speed=1 --fp_reassoc=off --include_path="/home/cicdserver/software/ipt-rail/inverter/sw20200507" --include_path="/home/cicdserver/software/ipt-rail/inverter/sw20200507/device" --include_path="/home/cicdserver/software/ipt-rail/inverter/sw20200507/digitalControllerLibrary" --include_path="/home/cicdserver/software/ipt-rail/inverter/sw20200507/f28004x_driverlib/driverlib/f28004x/driverlib" --include_path="/home/cicdserver/software/ipt-rail/inverter/sw20200507/f28004x_device_support/device_support/f28004x/common/include" --include_path="/home/cicdserver/software/ipt-rail/inverter/sw20200507/f28004x_device_support/device_support/f28004x/headers/include" --include_path="/home/cicdserver/ti/ccs1040/ccs/tools/compiler/ti-cgt-c2000_20.2.5.LTS/include" --advice:performance=all --define=CPU1 --define=_FLASH --define=_91_S230_0181a --define=DEBUG --undefine=_LAUNCHXL_F280049C --undefine=__cplusplus --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --misra_required=warning --preproc_with_compile --preproc_dependency="_module/mdlADC/$(basename $(<F)).d_raw" --obj_directory="_module/mdlADC" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


