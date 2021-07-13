VERBOSE ?= 

ifdef VERBOSE
Q = 
else
Q = @
endif

vecho = @echo

TOOLS_HOME ?= $(if $(filter Windows_NT,$(OS)),/c/msys32,)/opt/xtensa-lx106-elf
SDK_HOME ?= /git/ESP8266_NONOS_SDK

CC = $(TOOLS_HOME)/bin/xtensa-lx106-elf-gcc
AR = $(TOOLS_HOME)/bin/xtensa-lx106-elf-ar
LD = $(TOOLS_HOME)/bin/xtensa-lx106-elf-gcc
OBJCOPY = $(TOOLS_HOME)/bin/xtensa-lx106-elf-objcopy
OBJDUMP = $(TOOLS_HOME)/bin/xtensa-lx106-elf-objdump

PYTHON27 = $(if $(filter Windows_NT,$(OS)),/c/msys32/mingw32/bin/python2.7,python2.7)

MEM_ANALYZER = $(if $(filter Windows_NT,$(OS)),$(SDK_HOME)/tools/MemAnalyzer,)

export COMPILE = gcc
GEN_APPBIN = $(SDK_HOME)/tools/gen_appbin.py

GEN_APPBIN_BOOT_MODE = 2
GEN_APPBIN_FLASH_MODE = 0
GEN_APPBIN_FLASH_CLK_DIV = 0
GEN_APPBIN_FLASH_SIZE_MAP = 2

ESPTOOL = $(if $(filter Windows_NT,$(OS)),/c/msys32/mingw32/bin/,$(PYTHON27) )esptool.py
ESPTOOL_COM_PORT ?= NONE
ESPTOOL_BAUDRATE ?= 115200
ESPTOOL_FLASH_OPTIONS = --flash_freq 40m --flash_mode qio --flash_size 8m
ESPTOOL_BINARY_OPTIONS = 0x00000 $(SDK_BINDIR)/boot_v1.7.bin 0x01000 $(BINODIR)/$(BINARY)1.bin 0xF8000 $(BINODIR)/esp_$(BINARY)_caCerts.bin 0xF9000 $(BINODIR)/esp_$(BINARY)_clientCert.bin 0xFB000 $(SDK_BINDIR)/blank.bin 0xFC000 $(SDK_BINDIR)/esp_init_data_default_v08.bin 0xFE000 $(SDK_BINDIR)/blank.bin

MAKE_CACERT ?= $(SDK_HOME)/tools/make_cacert.py

BUILDROOT ?= 
OROOT ?= $(if $(BUILDROOT),$(BUILDROOT)/com/fotahub/devicesdks/plainc/examples/singlechip/esp8266/huzzah/thingshadow,build)
OBJODIR ?= $(OROOT)/obj
LIBODIR ?= $(OROOT)/lib
IMAGEODIR ?= $(OROOT)/elf
BINODIR ?= $(OROOT)/bin

SDK_INCDIRS = $(SDK_HOME)/include $(SDK_HOME)/driver_lib/include
SDK_INCDIR_FLAGS = $(addprefix -I,$(SDK_INCDIRS))
SDK_LIBDIR = $(SDK_HOME)/lib
SDK_LIBDIR_FLAGS = $(addprefix -L,$(SDK_LIBDIR))
SDK_LIBS = c gcc hal phy pp net80211 lwip wpa main crypto upgrade mbedtls
SDK_LIB_FLAGS = $(addprefix -l,$(SDK_LIBS))
SDK_LDDIR = $(SDK_HOME)/ld
SDK_BINDIR = $(SDK_HOME)/bin

# Add toolchain binaries path to PATH environment variable to enable tool invocations from Python-based utilities
export PATH := $(TOOLS_HOME)/bin:$(PATH)

export PREFIX ?= $(abspath $(dir $(firstword $(MAKEFILE_LIST))))/../../..
export FOTAHUB_INCDIR ?= $(PREFIX)/include
export FOTAHUB_SRCDIR ?=
export FOTAHUB_LIBDIR ?= $(PREFIX)/lib

#  
# Begin DemoProduct executable
#  

BINARY ?= DemoProduct

LIBS_DemoProduct = fotahub
LIBDIRS_DemoProduct = $(FOTAHUB_LIBDIR)
EXT_LIBS_DemoProduct = 
EXT_LIBDIRS_DemoProduct = 
ALL_LIBS_DemoProduct = 
ALL_LIB_FLAGS_DemoProduct = $(addprefix -l,$(LIBS_DemoProduct)) $(addprefix -l,$(EXT_LIBS_DemoProduct))
ALL_LIBDIR_FLAGS_DemoProduct = $(addprefix -L,$(LIBDIRS_DemoProduct)) $(addprefix -L,$(EXT_LIBDIRS_DemoProduct))

LIB_INCDIRS_DemoProduct = $(FOTAHUB_INCDIR)
EXT_INCDIRS_DemoProduct = $(PREFIX)/third-party/paho.mqtt.embedded-c/include $(PREFIX)/third-party/se.sics.contiki.json/include
ALL_INCDIR_FLAGS_DemoProduct = $(addprefix -I,.) $(addprefix -I,$(LIB_INCDIRS_DemoProduct)) $(addprefix -I,$(EXT_INCDIRS_DemoProduct))
ALL_INCS_DemoProduct = $(wildcard ./*.h) $(foreach lidir,$(LIB_INCDIRS_DemoProduct),$(wildcard $(lidir)/*.h)) $(foreach eidir,$(EXT_INCDIRS_DemoProduct),$(wildcard $(eidir)/*.h))

EXT_SRCDIR_DemoProduct_0 = $(SDK_HOME)/driver_lib/driver
EXT_SRCDIR_DemoProduct_1 = $(PREFIX)/third-party/paho.mqtt.embedded-c
EXT_SRCDIR_DemoProduct_2 = $(PREFIX)/third-party/se.sics.contiki.json
ALL_SRCS_DemoProduct = $(wildcard ./*.c) $(wildcard $(EXT_SRCDIR_DemoProduct_0)/uart.c) $(wildcard $(EXT_SRCDIR_DemoProduct_1)/*.c) $(wildcard $(EXT_SRCDIR_DemoProduct_2)/*.c)

ALL_OBJS_DemoProduct = $(patsubst %.c,$(OBJODIR)/%.o,$(notdir $(ALL_SRCS_DemoProduct)))

#  
# End DemoProduct executable
#  

CFLAGS = -std=gnu99 -Os -O2 -g0 -Wpointer-arith -Wundef -Werror -Wl,-EL -fno-inline-functions -nostdlib -mlongcalls -mtext-section-literals -ffunction-sections -fdata-sections -fno-builtin-printf

DEFINE_FLAGS = -DESP8266 -D__ets__ -DICACHE_FLASH

ARFLAGS = rcu

LDFLAGS = -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static -Wl,-Map=$(LIBODIR)/$(BINARY).map

LD_SCRIPT_USER1 = eagle.app.v6.1024.app1.ld
LD_SCRIPT_USER2 = eagle.app.v6.1024.app2.ld

LD_SCRIPT_FLAGS_USER1 := $(addprefix -L,$(SDK_HOME)) $(addprefix -T./,$(LD_SCRIPT_USER1))
LD_SCRIPT_FLAGS_USER2 := $(addprefix -L,$(SDK_HOME)) $(addprefix -T./,$(LD_SCRIPT_USER2))

.PHONY: all clean flash rebuild erase certs

all: allDependencies $(BINODIR)/$(BINARY)1.bin $(BINODIR)/$(BINARY)2.bin certs genFlashCmds

allDependencies: 
	$(if $(wildcard $(FOTAHUB_SRCDIR)/Makefile),$(Q) $(MAKE) -C $(FOTAHUB_SRCDIR) BUILDROOT=$(BUILDROOT) PREFIX=$(PREFIX),)

clean: 
	$(if $(wildcard $(OROOT)),$(vecho) "RM $(notdir $(OROOT)"),)
	$(Q) $(RM) -r $(OROOT)
	$(if $(wildcard eagle.app.sym),$(vecho) "RM eagle.app.sym",)
	$(Q) $(RM) -f eagle.app.sym
	$(if $(wildcard caCerts),$(vecho) "RM caCerts",)
	$(Q) $(RM) -r caCerts

cleanDependencies: 
	$(if $(wildcard $(FOTAHUB_SRCDIR)/Makefile),$(Q) $(MAKE) -C $(FOTAHUB_SRCDIR) clean BUILDROOT=$(BUILDROOT) PREFIX=$(PREFIX),)

cleanAll: clean cleanDependencies

rebuild: clean all

certs: $(BINODIR)/esp_$(BINARY)_caCerts.bin $(BINODIR)/esp_$(BINARY)_clientCert.bin | $(BINODIR)

flash: all
	$(vecho) "Flashing $(BINARY)..."
	$(Q) $(ESPTOOL) -p $(ESPTOOL_COM_PORT) -b $(ESPTOOL_BAUDRATE) write_flash $(ESPTOOL_FLASH_OPTIONS) $(ESPTOOL_BINARY_OPTIONS)
	$(vecho) "Done."

erase: 
	$(vecho) "Erasing flash memory..."
	$(Q) $(ESPTOOL) -p $(ESPTOOL_COM_PORT) -b $(ESPTOOL_BAUDRATE) erase_flash
	$(vecho) "Done."

genFlashCmds: Makefile
	$(if $(wildcard $(SDK_HOME)/tools/gen_flash_cmds.sh),$(Q) $(SDK_HOME)/tools/gen_flash_cmds.sh $(if $(HOST),$(HOST),Linux) $(ESPTOOL_BAUDRATE) "$(ESPTOOL_FLASH_OPTIONS)" "$(ESPTOOL_BINARY_OPTIONS)",)

$(OBJODIR): 
	$(Q) mkdir -p $@

define CompileSources
$$(patsubst %.c,$$(OBJODIR)/%.o,$$(notdir $(1))): $(1) $$(ALL_INCS_DemoProduct) Makefile | $$(OBJODIR)
	$$(vecho) "CC $$<"
	$$(Q) $$(CC) $$(CFLAGS) $$(DEFINE_FLAGS) $$(ALL_INCDIR_FLAGS_DemoProduct) $$(SDK_INCDIR_FLAGS) -c -o $$@ $$<
endef
$(foreach asrc,$(sort $(ALL_SRCS_DemoProduct)), $(eval $(call CompileSources,$(asrc))))

$(LIBODIR): 
	$(Q) mkdir -p $@

$(LIBODIR)/lib$(BINARY).a: $(ALL_OBJS_DemoProduct) | $(LIBODIR)
	$(vecho) "AR $(notdir $@)"
	$(Q) $(AR) $(ARFLAGS) $@ $(filter %.o,$?)

$(IMAGEODIR): 
	$(Q) mkdir -p $@

define MakeImage
$$(IMAGEODIR)/$$(BINARY)$(2).elf: $$(LIBODIR)/lib$$(BINARY).a $$(ALL_LIBS_DemoProduct) | $$(IMAGEODIR)
	$$(vecho) "LD $$(notdir $$@)"
	$$(Q) $$(LD) $(1) $$(LDFLAGS) -o $$@ $$(ALL_LIBDIR_FLAGS_DemoProduct) $$(SDK_LIBDIR_FLAGS) -Wl,--start-group $$(ALL_LIB_FLAGS_DemoProduct) $$(SDK_LIB_FLAGS) $$< -Wl,--end-group
	$$(vecho) "------------------------------------------------------------------------------"
	$$(vecho) "Memory Usage:"
	$$(if $$(filter Windows_NT,$$(OS)),$$(if $$(wildcard $$(MEM_ANALYZER)),$$(Q) $$(MEM_ANALYZER) $$(OBJDUMP).exe $$@ | tee $$(subst .elf,.dmp,$$@),$$(vecho) "Warning: $$(notdir $$(MEM_ANALYZER)) not found - please clone https://github.com/Sermus/ESP8266_memory_analyzer, build it, and copy resulting executable to $$(MEM_ANALYZER)."),)
	$$(vecho) "------------------------------------------------------------------------------"
	$$(Q) $$(OBJDUMP) -t -j .text $$@ > $$(subst .elf,_iram.dmp,$$@)
	$$(Q) $$(OBJDUMP) -t -j .irom0.text $$@ > $$(subst .elf,_spi.dmp,$$@)
	$$(Q) $$(OBJDUMP) -t -j .data -j .rodata -j .bss $$@ > $$(subst .elf,_ram.dmp,$$@)
	$$(vecho) "See *.dmp files in $$(IMAGEODIR) folder for detailed memory usage information."
	$$(vecho) "------------------------------------------------------------------------------"
endef
$(eval $(call MakeImage,$(LD_SCRIPT_FLAGS_USER1),1))
$(eval $(call MakeImage,$(LD_SCRIPT_FLAGS_USER2),2))

$(BINODIR): 
	$(Q) mkdir -p $@

define MakeBinary
$$(BINODIR)/$$(BINARY)$(1).bin: $$(IMAGEODIR)/$$(BINARY)$(1).elf | $$(BINODIR)
	$$(vecho) "FW $$(notdir $$@)"
	$$(Q) $$(OBJCOPY) --only-section .text -O binary $$< eagle.app.v6.text.bin
	$$(Q) $$(OBJCOPY) --only-section .data -O binary $$< eagle.app.v6.data.bin
	$$(Q) $$(OBJCOPY) --only-section .rodata -O binary $$< eagle.app.v6.rodata.bin
	$$(Q) $$(OBJCOPY) --only-section .irom0.text -O binary $$< eagle.app.v6.irom0text.bin
	$$(Q) $$(PYTHON27) $$(GEN_APPBIN) $$< $$(GEN_APPBIN_BOOT_MODE) $$(GEN_APPBIN_FLASH_MODE) $$(GEN_APPBIN_FLASH_CLK_DIV) $$(GEN_APPBIN_FLASH_SIZE_MAP) $(if $(1),$(1),0)
	$$(Q) mv eagle.app.flash.bin $$@
	$$(Q) $$(RM) eagle.app.v6.*.bin
	$(if $(subst 2,,$(1)),,$$(vecho) "Done.")
endef
$(eval $(call MakeBinary,1))
$(eval $(call MakeBinary,2))

define CreateCertDir
$(1): 
	$$(Q) mkdir -p $$@
endef
$(eval $(call CreateCertDir,caCerts))

define DownloadCert
$(2)/$(3): | $(2)
	$$(vecho) "DL $$(notdir $$@)"
	$$(Q) wget $$(if $$(V),,-q )-O $$@ $(1)
endef
$(eval $(call DownloadCert,https://letsencrypt.org/certs/isrgrootx1.pem,caCerts,isrgrootx1.cer))
$(eval $(call DownloadCert,https://www.amazontrust.com/repository/AmazonRootCA1.pem,caCerts,AmazonRootCA1.cer))

define MakeCertBinary
$$(BINODIR)/esp_$$(BINARY)_$(1).bin: $$(patsubst %,$(1)/%,$(2)) Makefile | $$(BINODIR)
	$$(vecho) "FW $$(notdir $$@)"
	$$(Q) cd $$(dir $$<) && $$(PYTHON27) $$(MAKE_CACERT) && cd $$(abspath $$(dir $$(firstword $$(MAKEFILE_LIST))))
	$$(Q) mv $$(dir $$<)esp_ca_cert.bin $$@
	$$(vecho) "Done."
endef
$(eval $(call MakeCertBinary,caCerts,isrgrootx1.cer AmazonRootCA1.cer))
$(eval $(call MakeCertBinary,clientCert,certificate.cer private_key.cer))
