
AGBINC	=	$(AGBDIR)/include
AGBLIB	=	$(AGBDIR)/lib

.AFILES		=	$(addprefix lib,$(addsuffix .a,$(ARCDIRS)))
.SFILES		=	crt0.s
.CFILES		=	main.c hard_init.c
.OFILES		=	$(.SFILES:.s=.o) $(.CFILES:.c=.o)

ASFLAGS		=	-I$(AGBINC) -mthumb-interwork
CFLAGS		=	-g -O2  -I$(AGBINC) -mthumb-interwork -nostdlib -DNDEBUG
LDFLAGS		+=  -Map $(MAPFILE) -nostartfiles \
				-Tbss 0x03000000 -Ttext 0x08000000 \
				-L$(AGBLIB) -lagbsyscall -lisagbprn \
				-L. $(addprefix -l,$(ARCDIRS))

DEPENDFILE	=	Makedepend
MAPFILE		=	sample.map
TARGET_ELF	=	sample.elf
TARGET_BIN	=	sample.bin


default:
	@$(foreach ARCDIR_TMP, $(ARCDIRS), make -C $(ARCDIR_TMP);)
	@$(MAKE) $(TARGET_BIN)

$(TARGET_BIN): $(TARGET_ELF)
	objcopy -v -O binary $< $@

$(TARGET_ELF): $(.OFILES) Makefile $(DEPENDFILE) $(.AFILES)
	@echo > $(MAPFILE)
	$(CC) -g -o $@ $(.OFILES) -Wl,$(LDFLAGS)


.PHONY: all clean depend relink rmbin libdepend mydepend


all:	clean default


clean:
	-rm $(.OFILES) $(DEPENDFILE) $(MAPFILE) $(TARGET_ELF) $(TARGET_BIN)
	@$(foreach ARCDIR_TMP, $(ARCDIRS), make -C $(ARCDIR_TMP) clean;)

relink: rmbin $(TARGET_BIN)

rmbin:
	-rm $(TARGET_ELF) $(TARGET_BIN)


depend: libdepend mydepend

libdepend:
	@$(foreach ARCDIR_TMP, $(ARCDIRS), make -C $(ARCDIR_TMP) depend;)

mydepend:
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)

$(DEPENDFILE): 
	$(CC) $(CFLAGS) -M $(.CFILES) > $(DEPENDFILE)


include Gasdepend
include $(DEPENDFILE)
