# Author: 
#  Henrique de Carvalho <henriquecarvalho@usp.br>

###################################
######         FLAGS         ######
###################################

cflags := -Wall -pedantic #-Werror

###################################
######      DIRECTORIES      ######
###################################

src_dir := ../src
inc_dir := ../include
bin_dir := ../bin
obj_dir := ../obj

test_src_dir := t_src
test_bin_dir := t_bin
test_inc_dir := t_include

###################################
######      FILES            ######
###################################

prefix := test_

test_src_files := $(wildcard $(test_src_dir)/*.c) 
test_targets     := $(patsubst $(test_src_dir)/$(prefix)%.c,%,$(test_src_files))
test_inc_targets := $(patsubst $(test_inc_dir)/$(prefix)%.c,%,$(test_src_files))

src_files := $(wildcard $(src_dir)/*.c)
obj_files := $(wildcard $(obj_dir)/*.o)
inc_files := $(wildcard $(inc_dir)/*.h)

###################################
######       COMMANDS        ######
###################################

cc    := gcc
rmdir := rm -rf

###################################
######      COMPILATION      ######
###################################

all: dirs $(test_inc_targets)

#$(test_targets): $(test_bin_dir)/$(prefix)%: $(test_src_dir)/$(prefix)%.c
#	$(cc) -I $(inc_dir) $(cflags) $< $(test_src_dir)/$(prefix)$@.c -o $(test_bin_dir)/$(prefix)$@ $(obj_dir)/$@.o # tests for src files

$(test_inc_targets): $(test_bin_dir)/$(prefix)%: $(test_inc_dir)/$(prefix)%.c
	$(cc) -I $(inc_dir) $(cflags) $(test_inc_dir)/$(prefix)$@.c -o $(test_bin_dir)/$(prefix)$@ 				  # tests for include files

dirs:
	mkdir -p $(test_bin_dir)

clean:
	rm -f $(obj_dir)/broker.o
	$(rmdir) $(test_bin_dir)
