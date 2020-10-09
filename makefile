# ----------------------------
# Program Options
# ----------------------------

NAME         ?= STONKS
#ICON         ?= icon.png
DESCRIPTION  ?= "CE C SDK Demo"
MAIN_ARGS    ?= NO
COMPRESSED   ?= NO
ARCHIVED     ?= YES

# ----------------------------
# Compile Options
# ----------------------------

OPT_MODE     ?= -Oz
EXTRA_CFLAGS ?= -Wall -Wextra

# ----------------------------
# Debug Options
# ----------------------------

OUTPUT_MAP   ?= NO

#enable float
USE_FLASH_FUNCTIONS := NO


include $(CEDEV)/include/.makefile
