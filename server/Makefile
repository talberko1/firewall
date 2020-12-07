#Makefile template for project creation - created by talberko1

TARGET	:=	app

SRC_DIR	:=	src
INC_DIR	:=	include

OBJ_DIR	:=	build
DEP_DIR	:=	dep
BIN_DIR	:=	bin

OBJECT_EXT	:=	o
DEPENDENCY_EXT	:=	d
SOURCE_EXT	:=	cpp

CC	:=	g++
COMPILE	:=	-c
OUTPUT	:=	-o

WFLAGS	:=	-Wall -Werror

include /usr/local/etc/PcapPlusPlus.mk

MONGO_INCLUDES = -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0

BSON_INCLUDES = -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0



CFLAGS	:=	$(WFLAGS) $(PCAPPP_INCLUDES) $(MONGO_INCLUDES) $(BSON_INCLUDES) -I$(INC_DIR) $(COMPILE)

LDFLAGS	:=	$(WFLAGS) $(PCAPPP_LIBS_DIR) -L/usr/local/lib

#---LIBRARIES---

LIBS	:=	$(PCAPPP_LIBS) -lmongocxx -lbsoncxx

#==============DO=NOT=EDIT=BELOW=THIS=LINE==============#

SRCS	:=	$(wildcard $(SRC_DIR)/*.$(SOURCE_EXT))
OBJS	=	$(addprefix $(OBJ_DIR)/,$(patsubst $(SRC_DIR)/%.$(SOURCE_EXT),%.$(OBJECT_EXT),$(SRCS)))
GENERATED_DIRS	:=	$(OBJ_DIR)	$(DEP_DIR)	$(BIN_DIR)

#Make target application
all:	$(SRCS)	$(GENERATED_DIRS)	$(TARGET)

#Make the needed directories
$(GENERATED_DIRS):
	@mkdir $@

#Make target application
$(TARGET):	$(OBJS)
	@echo "Building target: $(BIN_DIR)/$@"
	@$(CC) $(LDFLAGS) $^ $(OUTPUT) $(BIN_DIR)/$@ $(LIBS)
	@echo "Done!"

#Make object files and put them in the 'obj' directory
$(OBJ_DIR)/%.$(OBJECT_EXT):	$(SRC_DIR)/%.$(SOURCE_EXT)
	@echo "Building file: $<"
	@$(CC) $(CFLAGS) $< $(OUTPUT) $@	$(DEPFLAGS)

#Clean target application
clean:
	@echo "Cleaning.."
	$(foreach dir,$(GENERATED_DIRS),@rm -rf $(dir))
	@echo "Done!"
