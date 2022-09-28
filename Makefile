# Author:
#  Henrique de Carvalho <henriquecarvalho@usp.br>

###################################
######         FLAGS         ######
###################################

cflags := -Wall 

###################################
######      DIRECTORIES      ######
###################################

src_dir := src
inc_dir := include
bin_dir := bin
obj_dir := obj

###################################
######      FILES            ######
###################################

target    := $(bin_dir)/broker

src_files := $(wildcard $(src_dir)/*.c)
inc_files := $(wildcard $(inc_dir)/*.h)
obj_files := $(patsubst $(src_dir)/%.c,$(obj_dir)/%.o,$(src_files))

###################################
######       COMMANDS        ######
###################################

cc     := gcc
remove := rm -rf

###################################
######      COMPILATION      ######
###################################

all: dirs $(target)

$(target): $(obj_files)
	$(cc) -I $(inc_dir) $(cflags) -o $(target) $(obj_files)  # @$ is the name of the target

$(obj_files): $(obj_dir)/%.o : $(src_dir)/%.c
	$(cc) -I $(inc_dir) -c $< -o $@

dirs:
	mkdir -p $(obj_dir)
	mkdir -p $(bin_dir)

clean:
	$(remove) $(obj_dir)
	$(remove) $(bin_dir)
